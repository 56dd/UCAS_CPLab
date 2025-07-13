#include "Function.h"
#include "IR/IRFunction.h"
#include "Module.h"
#include "BasicBlock.h"
#include "BinaryOperator.h"
#include "Value.h"
#include "utils/Register.h"
#include "StoreInst.h"
#include "IR/iMemory.h"
#include "LiInst.h"
#include "LoadInst.h"

namespace RISCV {
    Function::Function(IRFunction *irFunc, Module *parent) : section(TEXT), align(1), parent(parent),
                                                             irFunction(irFunc) {
        name = irFunc->getName();
        entryBlock = new BasicBlock(nullptr, nullptr);
        for (auto irBB: irFunc->getBasicBlockList()) {
            new BasicBlock(irBB, this);
        }
        generateEntryBlock();
        for (auto BB: BasicBlockList) {
            BB->generate();
        }
        if (parent)
            parent->addFunction(this);
    }

    void Function::print(std::ostream &O) {
        O << "\t.text" << std::endl;
        O << "\t.align\t" << align << std::endl;
        O << "\t.globl\t" << name << std::endl;
        O << "\t.type\t" << name << ", @function" << std::endl;
        O << name << ":" << std::endl;
        for (auto inst: entryBlock->getInstList()) {
            O << "\t";
            inst->print(O);
        }
        for (auto BB: BasicBlockList) {
            BB->print(O);
        }
        O << "\t.size\t" << name << ", .-" << name << std::endl;
        O << std::endl;
    }

    Module *Function::getParent() const {
        return parent;
    }

    void Function::addBasicBlock(BasicBlock *BB) {
        BasicBlockList.push_back(BB);
        BasicBlockSet[BB->getIrBb()] = BB;
    }

    void Function::generateEntryBlock() {
        entryBlock = new BasicBlock(nullptr, nullptr);
        // 统计 callee 寄存器的栈帧大小
        auto calleeRegList = irFunction->getCalleeSavedRegList();
        int regSize = alignSize(8 * calleeRegList.size() + 8);
        // 统计 alloc 栈帧大小
        std::vector<IRAllocaInst *> allocList;
        std::vector<int> sizeList;
        for (auto inst: irFunction->getEntryBlock()->getInstList()) {
            auto alloc = dynamic_cast<IRAllocaInst *>(inst);
            if (alloc) {
                allocList.push_back(alloc);
            }
        }
        for (auto alloc: allocList) {
            auto ty = alloc->getType()->getElementType();
            if (ty->getPrimitiveID() == IRType::ArrayTyID) {
                auto arrayTy = dynamic_cast<const IRArrayType *>(ty);
                sizeList.push_back(
                        alignSize(arrayTy->getNumElements() * arrayTy->getElementType()->getPrimitiveSize()));
            } else if (ty->isPrimitiveType() && ty != IRType::VoidTy && ty != IRType::LabelTy && ty != IRType::TypeTy) {
                sizeList.push_back(alignSize(ty->getPrimitiveSize()));
            } else if (ty->getPrimitiveID() == IRType::PointerTyID) {
                // 在栈上存指针
                sizeList.push_back(alignSize(8));
            } else {
                assert(0 && "Error type");
            }
        }
        allocSize = regSize;
        for (auto sz: sizeList)
            allocSize += sz;
        if (allocSize == 0)
            return;
        // 申请栈空间
        new BinaryOperator(Instruction::Addi, IRType::IntTy, new Value(CalleeSavedRegister::sp),
                           new Value(CalleeSavedRegister::sp),
                           new Value(-allocSize), entryBlock);
        int index = 0;
        for (unsigned i = 0, E = allocList.size(); i < E; ++i) {
            allocPtrMap[allocList[i]] = new Pointer(index);
            index += sizeList[i];
        }
        // 存储callee寄存器
        regPtrMap[CallerSavedRegister::ra] = new Pointer(index);
        new StoreInst(new Value(CallerSavedRegister::ra), regPtrMap[CallerSavedRegister::ra],
                      entryBlock);
        index += 8;
        for (auto reg: calleeRegList) {
            regPtrMap[reg] = new Pointer(index);
            if (reg->getRegty() == Register::FloatCalleeSaved)
                new StoreInst(new Value(reg), new Pointer(index), entryBlock, IRType::DoubleTy);
            else
                new StoreInst(new Value(reg), new Pointer(index), entryBlock);
            index += 8;
        }

        // 将放入常数寄存器中
        for (auto [constant, reg] : irFunction->getConstRegMap()) {
            if (constant == IRConstant::getNullValue(IRType::IntTy))
                continue;
            auto ty = constant->getType();
            if (ty == IRType::IntTy) {
                new LiInst(new Value(reg), dynamic_cast<IRConstantInt *>(constant)->getRawValue(), entryBlock);
            } else if (ty == IRType::BoolTy) {
                new LiInst(new Value(reg), dynamic_cast<IRConstantBool *>(constant)->getRawValue(), entryBlock);
            } else if (ty == IRType::FloatTy || ty == IRType::DoubleTy) {
                auto immGV = new GlobalVariable(constant, parent);
                new LoadInst(new Value(reg), new Pointer(immGV), entryBlock, ty, new Value(CallerSavedRegister::ra));
            } else {
                assert(0 && "Error Type");
            }
        }
    }

    BasicBlock *Function::findBasicBlock(IRBasicBlock *irBasicBlock) {
        return BasicBlockSet[irBasicBlock];
    }

    const std::string &Function::getName() const {
        return name;
    }

    int Function::alignSize(unsigned long i) {
        if (i % 16) {
            i = i + 16 - (i % 16);
        }
        return i;
    }

    Pointer *Function::getPointer(IRAllocaInst *alloc) {
        return allocPtrMap[alloc];
    }

    Pointer *Function::getPointer(Register *reg) {
        return regPtrMap[reg];
    }

    IRFunction *Function::getIrFunction() const {
        return irFunction;
    }

    unsigned int Function::getAllocSize() const {
        return allocSize;
    }

    BasicBlock *Function::getNextBlock(BasicBlock *block) {
        auto it = std::find(BasicBlockList.begin(), BasicBlockList.end(), block);
        it++;
        if (it == BasicBlockList.end())
            return nullptr;
        return *it;
    }

    Function::Function(std::string name)
            : name(name), irFunction(nullptr), parent(nullptr), section(), align(0), entryBlock(nullptr) {
    }
} // RISCV