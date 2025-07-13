#include "BasicBlock.h"
#include "IR/IRBasicBlock.h"
#include "IR/iTerminators.h"
#include "IR/IRConstant.h"
#include "IR/iOperators.h"
#include "IR/iMemory.h"
#include "IR/IRGlobalVariable.h"
#include "IR/iOther.h"
#include "Function.h"
#include "Module.h"
#include "Instruction.h"
#include "ReturnInst.h"
#include "LoadInst.h"
#include "BinaryOperator.h"
#include "BranchInst.h"
#include "JInst.h"
#include "MoveInst.h"
#include "LiInst.h"
#include "SetCondInst.h"
#include "StoreInst.h"
#include "CallInst.h"

namespace RISCV {
    void BasicBlock::print(std::ostream &O) {
        if (!name.empty())
            O << name << ":" << std::endl;
        for (auto inst: InstList) {
            O << "\t";
            inst->print(O);
        }
    }

    BasicBlock::BasicBlock(IRBasicBlock *irBasicBlock, Function *parent) : irBasicBlock(irBasicBlock), parent(parent) {
        if (irBasicBlock && parent)
            name = ".L" + irBasicBlock->getName() + "_" + std::to_string(parent->getParent()->getLabelCount());
        if (parent) {
            parent->addBasicBlock(this);
        }
    }

    void BasicBlock::addInstruction(Instruction *inst) {
        InstList.push_back(inst);
    }

    IRBasicBlock *BasicBlock::getIrBb() const {
        return irBasicBlock;
    }

    void BasicBlock::generate() {
        auto constMap = parent->getIrFunction()->getConstRegMap();
        for (auto irInst: irBasicBlock->getInstList()) {
            switch (irInst->getOpcode()) {
                case IRInstruction::Ret: {
                    auto retInst = dynamic_cast<IRReturnInst *>(irInst);
                    auto retVal = retInst->getReturnValue();
                    // 设置返回值
                    if (retVal) {
                        if (IRConstant::classof(retVal) &&
                            !constMap[dynamic_cast<IRConstant *>(retVal)]) { // 返回值是常数并且没有被分配寄存器
                            if (retVal->getType() == IRType::IntTy) {
                                new LiInst(new Value(RegisterFactory::getReg("a0")),
                                           dynamic_cast<IRConstantInt *>(retVal)->getRawValue(), this);
                            } else if (retVal->getType() == IRType::FloatTy || retVal->getType() == IRType::DoubleTy) {
                                auto immGV = new GlobalVariable(dynamic_cast<IRConstant *>(retVal),
                                                                parent->getParent());
                                new LoadInst(new Value(RegisterFactory::getReg("fa0")), new Pointer(immGV), this,
                                             retVal->getType(), new Value(CallerSavedRegister::ra));
                            } else if (retVal->getType() == IRType::BoolTy) {
                                new LiInst(new Value(RegisterFactory::getReg("a0")),
                                           dynamic_cast<IRConstantBool *>(retVal)->getRawValue(), this);
                            } else {
                                assert(0 && "Error retVal Type");
                            }
                        } else {
                            Register *destReg = nullptr, *srcReg = nullptr;
                            if (retVal->getType() == IRType::IntTy || retVal->getType() == IRType::BoolTy) {
                                destReg = RegisterFactory::getReg("a0");
                            } else if (retVal->getType() == IRType::FloatTy || retVal->getType() == IRType::DoubleTy) {
                                destReg = RegisterFactory::getReg("fa0");
                            } else {
                                assert(0 && "Error retVal Type");
                            }
                            srcReg = retVal->getReg();
                            if (IRConstant::classof(retVal)) { // 返回值是常数并且被分配了寄存器
                                srcReg = constMap[dynamic_cast<IRConstant *>(retVal)];
                            }
                            if (srcReg != destReg) {
                                new MoveInst(retVal->getType(), new Value(destReg), new Value(srcReg), this);
                            }
                        }
                    }
                    // 恢复 callee 寄存器
                    auto calleeRegList = parent->getIrFunction()->getCalleeSavedRegList();
                    new LoadInst(new Value(CallerSavedRegister::ra),
                                 parent->getPointer(CallerSavedRegister::ra), this);
                    for (auto reg: calleeRegList) {
                        if (reg->getRegty() == Register::FloatCalleeSaved)
                            new LoadInst(new Value(reg), parent->getPointer(reg), this, IRType::DoubleTy);
                        else
                            new LoadInst(new Value(reg), parent->getPointer(reg), this);
                    }
                    new BinaryOperator(Instruction::Addi, IRType::IntTy, new Value(CalleeSavedRegister::sp),
                                       new Value(CalleeSavedRegister::sp), new Value(parent->getAllocSize()), this);
                    new ReturnInst(this);
                    break;
                }
                case IRInstruction::Br: {
                    auto brInst = dynamic_cast<IRBranchInst *>(irInst);
                    auto nextBlock = parent->getNextBlock(this);
                    if (brInst->isUnconditional()) {
                        // 无条件跳转
                        if (nextBlock->irBasicBlock != brInst->getSuccessor(0)) {
                            new JInst(parent->findBasicBlock(brInst->getSuccessor(0)), this);
                        }
                    } else {
                        // 条件跳转
                        bool needTwoJump = false;
                        auto cond = dynamic_cast<IRSetCondInst *>(brInst->getCondition());
                        if (cond) {
                            auto ty = cond->getOperand(0)->getType();
                            if (ty == IRType::IntTy || ty == IRType::BoolTy) {
                                // 整数跳转
                                Value *value0 = nullptr;
                                Value *value1 = nullptr;
                                if (IRConstant::classof(cond->getOperand(0)) &&
                                    !constMap[dynamic_cast<IRConstant *>(cond->getOperand(0))]) {
                                    if (ty == IRType::IntTy) {
                                        if (dynamic_cast<IRConstantInt *>(cond->getOperand(0))->getRawValue() == 0)
                                            value0 = new Value(ZeroRegister::zero);
                                        else
                                            new LiInst(value0 = new Value(CallerSavedRegister::ra),
                                                       dynamic_cast<IRConstantInt *>(cond->getOperand(
                                                               0))->getRawValue(),
                                                       this);
                                    } else if (ty == IRType::BoolTy) {
                                        if (!dynamic_cast<IRConstantBool *>(cond->getOperand(0))->getRawValue())
                                            value0 = new Value(ZeroRegister::zero);
                                        else
                                            new LiInst(value0 = new Value(CallerSavedRegister::ra), 1, this);
                                    } else {
                                        assert(0 && "Error Type");
                                    }
                                } else {
                                    if (IRConstant::classof(cond->getOperand(0))) {
                                        value0 = new Value(constMap[dynamic_cast<IRConstant *>(cond->getOperand(0))]);
                                    } else {
                                        value0 = new Value(cond->getOperand(0)->getReg());
                                    }
                                }

                                if (IRConstant::classof(cond->getOperand(1)) &&
                                    !constMap[dynamic_cast<IRConstant *>(cond->getOperand(1))]) {
                                    if (ty == IRType::IntTy) {
                                        if (dynamic_cast<IRConstantInt *>(cond->getOperand(1))->getRawValue() == 0)
                                            value1 = new Value(ZeroRegister::zero);
                                        else
                                            new LiInst(value1 = new Value(CallerSavedRegister::ra),
                                                       dynamic_cast<IRConstantInt *>(cond->getOperand(
                                                               1))->getRawValue(),
                                                       this);
                                    } else if (ty == IRType::BoolTy) {
                                        if (!dynamic_cast<IRConstantBool *>(cond->getOperand(1))->getRawValue())
                                            value1 = new Value(ZeroRegister::zero);
                                        else
                                            new LiInst(value1 = new Value(CallerSavedRegister::ra), 1, this);
                                    }
                                } else {
                                    if (IRConstant::classof(cond->getOperand(1))) {
                                        value1 = new Value(constMap[dynamic_cast<IRConstant *>(cond->getOperand(1))]);
                                    } else {
                                        value1 = new Value(cond->getOperand(1)->getReg());
                                    }
                                }
                                Instruction::TermOps iType;
                                auto irTrueBB = brInst->getSuccessor(0);
                                auto irFalseBB = brInst->getSuccessor(1);
                                if (nextBlock->irBasicBlock != irTrueBB && nextBlock->irBasicBlock != irFalseBB)
                                    needTwoJump = true;
                                auto jumpBlock = parent->findBasicBlock(irTrueBB);
                                unsigned irIType = cond->getOpcode();
                                if (nextBlock->irBasicBlock == irTrueBB) {
                                    jumpBlock = parent->findBasicBlock(irFalseBB);
                                    irIType = cond->getInverseCondition();
                                }
                                switch (irIType) {
                                    case IRInstruction::SetEQ:
                                        iType = Instruction::Beq;
                                        break;
                                    case IRInstruction::SetNE:
                                        iType = Instruction::Bne;
                                        break;
                                    case IRInstruction::SetLE:
                                        iType = Instruction::Ble;
                                        break;
                                    case IRInstruction::SetGE:
                                        iType = Instruction::Bge;
                                        break;
                                    case IRInstruction::SetLT:
                                        iType = Instruction::Blt;
                                        break;
                                    case IRInstruction::SetGT:
                                        iType = Instruction::Bgt;
                                        break;
                                    default:
                                        assert(0 && "error irIType");
                                }
                                new BranchInst(iType, jumpBlock, value0, value1, this);
                                if (needTwoJump) {
                                    if (jumpBlock->getIrBb() == irTrueBB)
                                        new JInst(parent->findBasicBlock(irFalseBB), this);
                                    else
                                        new JInst(parent->findBasicBlock(irTrueBB), this);
                                }
                            } else {
                                // 浮点跳转
                                Instruction::TermOps iType = Instruction::Bnez;
                                auto irTrueBB = brInst->getSuccessor(0);
                                auto irFalseBB = brInst->getSuccessor(1);
                                // 因为没有 fne，所以取反
                                if (cond->getOpcode() == IRInstruction::SetNE) {
                                    auto temp = irTrueBB;
                                    irTrueBB = irFalseBB;
                                    irFalseBB = temp;
                                }
                                if (nextBlock->irBasicBlock != irTrueBB && nextBlock->irBasicBlock != irFalseBB)
                                    needTwoJump = true;
                                auto jumpBlock = parent->findBasicBlock(irTrueBB);
                                if (nextBlock->irBasicBlock == irTrueBB) {
                                    jumpBlock = parent->findBasicBlock(irFalseBB);
                                    iType = Instruction::Beqz;
                                }
                                new BranchInst(iType, jumpBlock, new Value(brInst->getCondition()), nullptr, this);
                                if (needTwoJump) {
                                    if (jumpBlock->getIrBb() == irTrueBB)
                                        new JInst(parent->findBasicBlock(irFalseBB), this);
                                    else
                                        new JInst(parent->findBasicBlock(irTrueBB), this);
                                }
                            }
                        } else {
                            Instruction::TermOps iType = Instruction::Bnez;
                            auto irTrueBB = brInst->getSuccessor(0);
                            auto irFalseBB = brInst->getSuccessor(1);
                            if (nextBlock->irBasicBlock != irTrueBB && nextBlock->irBasicBlock != irFalseBB)
                                needTwoJump = true;
                            auto jumpBlock = parent->findBasicBlock(irTrueBB);
                            if (nextBlock->irBasicBlock == irTrueBB) {
                                jumpBlock = parent->findBasicBlock(irFalseBB);
                                iType = Instruction::Beqz;
                            }
                            new BranchInst(iType, jumpBlock, new Value(brInst->getCondition()), nullptr, this);
                            if (needTwoJump) {
                                if (jumpBlock->getIrBb() == irTrueBB)
                                    new JInst(parent->findBasicBlock(irFalseBB), this);
                                else
                                    new JInst(parent->findBasicBlock(irTrueBB), this);
                            }
                        }
                    }
                    break;
                }
                case IRInstruction::Add: {
                    auto addInst = dynamic_cast<IRBinaryOperator *>(irInst);
                    auto op1 = addInst->getOperand(0);
                    auto op2 = addInst->getOperand(1);
                    auto ty = irInst->getType();
                    bool needRestore = false;
                    if (IRConstant::classof(op1)) {
                        auto temp = op2;
                        op1 = op2;
                        op2 = temp;
                    }
                    auto imm = dynamic_cast<IRConstant *>(op2);
                    if (dynamic_cast<IRArrayType *>(ty) || dynamic_cast<IRPointerType *>(ty)) {
                        ty = IRType::IntTy;
                    }
                    if (imm) {
                        // 第二个操作数是立即数
                        auto immInt = dynamic_cast<IRConstantInt *>(imm);
                        if (immInt && -2048 <= immInt->getRawValue() && immInt->getRawValue() < 2048) {
                            // 可以翻译为addi
                            int val = immInt->getRawValue();
                            new BinaryOperator(Instruction::Addi, ty, new Value(irInst), new Value(op1), new Value(val),
                                               this);
                        } else if (ty == IRType::IntTy) {
                            Value *val2 = nullptr;
                            if (constMap[imm]) {
                                val2 = new Value(constMap[imm]);
                            } else {
                                int val = immInt->getRawValue();
                                new LiInst(val2 = new Value(CallerSavedRegister::ra), val, this);
                            }
                            new BinaryOperator(Instruction::Addi, ty, new Value(irInst), new Value(op1), val2, this);
                        } else if (ty == IRType::FloatTy || ty == IRType::DoubleTy) {
                            // 浮点
                            Value *val2 = nullptr;
                            if (constMap[imm]) {
                                val2 = new Value(constMap[imm]);
                            } else {
                                auto immGV = new GlobalVariable(dynamic_cast<IRConstant *>(op2), parent->getParent());
                                // 寻找空闲寄存器
                                auto tempReg = const_cast<Register *>(irInst->getFreeFloatCallerSavedReg());
                                if (tempReg == nullptr) {
                                    // 找不到使用fa0/fa1，将fa0/fa1存储在栈上，运算完之后restore
                                    needRestore = true;
                                    if (op1->getReg() == RegisterFactory::getReg("fa0"))
                                        val2 = new Value(RegisterFactory::getReg("fa1"));
                                    else
                                        val2 = new Value(RegisterFactory::getReg("fa0"));
                                    new StoreInst(val2, new Pointer(-8), this, IRType::DoubleTy);
                                } else {
                                    val2 = new Value(tempReg);
                                }
                                // 将立即数的值load到寄存器中
                                new LoadInst(val2, new Pointer(immGV), this, ty, new Value(CallerSavedRegister::ra));
                            }

                            new BinaryOperator(Instruction::Add, ty, new Value(irInst), new Value(op1), val2,
                                               this);

                            if (needRestore)
                                new LoadInst(val2, new Pointer(-8), this, IRType::DoubleTy);
                        } else {
                            assert(0 && "Error Type");
                        }
                    } else {
                        // 两个操作数都是reg
                        new BinaryOperator(Instruction::Add, ty, new Value(irInst), new Value(op1), new Value(op2),
                                           this);
                    }
                    break;
                }
                case IRInstruction::Sub: {
                    auto addInst = dynamic_cast<IRBinaryOperator *>(irInst);
                    auto op1 = addInst->getOperand(0);
                    auto op2 = addInst->getOperand(1);
                    auto ty = irInst->getType();
                    bool needRestore = false;
                    if (dynamic_cast<IRArrayType *>(ty) || dynamic_cast<IRPointerType *>(ty)) {
                        ty = IRType::IntTy;
                    }
                    auto imm = dynamic_cast<IRConstantInt *>(op2);
                    if (imm && -2048 <= -imm->getRawValue() && -imm->getRawValue() < 2048) {
                        // 可以翻译为addi
                        new BinaryOperator(Instruction::Addi, ty, new Value(irInst), new Value(op1),
                                           new Value(-imm->getRawValue()),
                                           this);

                    } else if (ty == IRType::IntTy) {
                        auto imm1 = dynamic_cast<IRConstantInt *>(op1);
                        auto imm2 = dynamic_cast<IRConstantInt *>(op2);
                        Value *value1 = nullptr;
                        Value *value2 = nullptr;
                        if (imm1) {
                            if (constMap[imm1]) {
                                value1 = new Value(constMap[imm1]);
                            } else {
                                new LiInst(value1 = new Value(CallerSavedRegister::ra), imm1->getRawValue(), this);
                            }
                        } else {
                            value1 = new Value(op1);
                        }
                        if (imm2) {
                            if (constMap[imm2]) {
                                value2 = new Value(constMap[imm2]);
                            } else {
                                new LiInst(value2 = new Value(CallerSavedRegister::ra), imm2->getRawValue(), this);
                            }
                        } else {
                            value2 = new Value(op2);
                        }
                        new BinaryOperator(Instruction::Sub, ty, new Value(irInst), value1, value2,
                                           this);
                    } else if (ty == IRType::FloatTy || ty == IRType::DoubleTy) {
                        // 浮点
                        Value *val1 = nullptr, *val2 = nullptr;
                        // 如果op1是浮点常数
                        if (dynamic_cast<IRConstant *>(op1)) {
                            if (constMap[dynamic_cast<IRConstant *>(op1)]) {
                                val1 = new Value(constMap[dynamic_cast<IRConstant *>(op1)]);
                            } else {
                                // 将常数申明为全局变量
                                auto immGV = new GlobalVariable(dynamic_cast<IRConstant *>(op1), parent->getParent());
                                // 寻找空闲寄存器
                                auto tempReg = const_cast<Register *>(irInst->getFreeFloatCallerSavedReg());
                                if (tempReg == nullptr) {
                                    // 找不到使用fa0/fa1，将fa0/fa1存储在栈上，运算完之后restore
                                    needRestore = true;
                                    if (op2->getReg() == RegisterFactory::getReg("fa0"))
                                        val1 = new Value(RegisterFactory::getReg("fa1"));
                                    else
                                        val1 = new Value(RegisterFactory::getReg("fa0"));
                                    new StoreInst(val1, new Pointer(-8), this, IRType::DoubleTy);
                                } else {
                                    val1 = new Value(tempReg);
                                }
                                // 将立即数的值load到寄存器中
                                new LoadInst(val1, new Pointer(immGV), this, ty, new Value(CallerSavedRegister::ra));
                            }
                        } else
                            val1 = new Value(op1);
                        // 如果op2是浮点常数
                        if (dynamic_cast<IRConstant *>(op2)) {
                            if (constMap[dynamic_cast<IRConstant *>(op2)]) {
                                val2 = new Value(dynamic_cast<IRConstant *>(op2));
                            } else {
                                // 将常数申明为全局变量
                                auto immGV = new GlobalVariable(dynamic_cast<IRConstant *>(op2), parent->getParent());
                                // 寻找空闲寄存器
                                auto tempReg = const_cast<Register *>(irInst->getFreeFloatCallerSavedReg());
                                if (tempReg == nullptr) {
                                    // 找不到使用fa0，将fa0存储在栈上，运算完之后restore
                                    needRestore = true;
                                    if (op1->getReg() == RegisterFactory::getReg("fa0"))
                                        val2 = new Value(RegisterFactory::getReg("fa1"));
                                    else
                                        val2 = new Value(RegisterFactory::getReg("fa0"));
                                    new StoreInst(val2, new Pointer(-8), this, IRType::DoubleTy);
                                } else {
                                    val2 = new Value(tempReg);
                                }
                                // 将立即数的值load到寄存器中
                                new LoadInst(val2, new Pointer(immGV), this, ty, new Value(CallerSavedRegister::ra));
                            }
                        } else
                            val2 = new Value(op2);
                        new BinaryOperator(Instruction::Sub, ty, new Value(irInst), val1, val2,
                                           this);
                        if (needRestore) {
                            if (dynamic_cast<IRConstant *>(op1))
                                new LoadInst(val1, new Pointer(-8), this, IRType::DoubleTy);
                            if (dynamic_cast<IRConstant *>(op2))
                                new LoadInst(val2, new Pointer(-8), this, IRType::DoubleTy);
                        }
                    } else {
                        assert(0 && "Error Type");
                    }
                    break;
                }
                case IRInstruction::Mul:
                case IRInstruction::Div:
                case IRInstruction::Rem: {
                    auto addInst = dynamic_cast<IRBinaryOperator *>(irInst);
                    auto op1 = addInst->getOperand(0);
                    auto op2 = addInst->getOperand(1);
                    auto ty = irInst->getType();
                    unsigned iType;
                    switch (addInst->getOpcode()) {
                        case IRInstruction::Mul:
                            iType = Instruction::Mul;
                            break;
                        case IRInstruction::Div:
                            iType = Instruction::Div;
                            break;
                        case IRInstruction::Rem:
                            iType = Instruction::Rem;
                            break;
                        default:
                            assert(0 && "wtf");
                    }
                    if (dynamic_cast<IRArrayType *>(ty) || dynamic_cast<IRPointerType *>(ty)) {
                        ty = IRType::IntTy;
                    }
                    if (ty == IRType::IntTy) {
                        auto imm1 = dynamic_cast<IRConstantInt *>(op1);
                        auto imm2 = dynamic_cast<IRConstantInt *>(op2);
                        Value *value1 = nullptr;
                        Value *value2 = nullptr;
                        if (imm1) {
                            if (constMap[imm1]) {
                                value1 = new Value(constMap[imm1]);
                            } else {
                                new LiInst(value1 = new Value(CallerSavedRegister::ra), imm1->getRawValue(), this);
                            }
                        } else {
                            value1 = new Value(op1);
                        }
                        if (imm2) {
                            if (constMap[imm2]) {
                                value2 = new Value(constMap[imm2]);
                            } else {
                                new LiInst(value2 = new Value(CallerSavedRegister::ra), imm2->getRawValue(), this);
                            }
                        } else {
                            value2 = new Value(op2);
                        }
                        new BinaryOperator(iType, ty, new Value(irInst), value1, value2,
                                           this);
                    } else if (ty == IRType::FloatTy || ty == IRType::DoubleTy) {
                        bool needRestore = false;
                        // 浮点
                        Value *val1 = nullptr, *val2 = nullptr;
                        // 如果op1是浮点常数
                        if (dynamic_cast<IRConstant *>(op1)) {
                            if (constMap[dynamic_cast<IRConstant *>(op1)]) {
                                val1 = new Value(constMap[dynamic_cast<IRConstant *>(op1)]);
                            } else {
                                // 将常数申明为全局变量
                                auto immGV = new GlobalVariable(dynamic_cast<IRConstant *>(op1), parent->getParent());
                                // 寻找空闲寄存器
                                auto tempReg = const_cast<Register *>(irInst->getFreeFloatCallerSavedReg());
                                if (tempReg == nullptr) {
                                    // 找不到使用fa0/fa1，将fa0/fa1存储在栈上，运算完之后restore
                                    needRestore = true;
                                    if (op2->getReg() == RegisterFactory::getReg("fa0"))
                                        val1 = new Value(RegisterFactory::getReg("fa1"));
                                    else
                                        val1 = new Value(RegisterFactory::getReg("fa0"));
                                    new StoreInst(val1, new Pointer(-8), this, IRType::DoubleTy);
                                } else {
                                    val1 = new Value(tempReg);
                                }
                                // 将立即数的值load到寄存器中
                                new LoadInst(val1, new Pointer(immGV), this, ty, new Value(CallerSavedRegister::ra));
                            }
                        } else
                            val1 = new Value(op1);
                        // 如果op2是浮点常数
                        if (dynamic_cast<IRConstant *>(op2)) {
                            if (constMap[dynamic_cast<IRConstant *>(op2)]) {
                                val2 = new Value(constMap[dynamic_cast<IRConstant *>(op2)]);
                            } else {
                                // 将常数申明为全局变量
                                auto immGV = new GlobalVariable(dynamic_cast<IRConstant *>(op2), parent->getParent());
                                // 寻找空闲寄存器
                                auto tempReg = const_cast<Register *>(irInst->getFreeFloatCallerSavedReg());
                                if (tempReg == nullptr) {
                                    // 找不到使用fa0/fa1，将fa0/fa1存储在栈上，运算完之后restore
                                    needRestore = true;
                                    if (op1->getReg() == RegisterFactory::getReg("fa0"))
                                        val2 = new Value(RegisterFactory::getReg("fa1"));
                                    else
                                        val2 = new Value(RegisterFactory::getReg("fa0"));
                                    new StoreInst(val2, new Pointer(-8), this, IRType::DoubleTy);
                                } else {
                                    val2 = new Value(tempReg);
                                }
                                // 将立即数的值load到寄存器中
                                new LoadInst(val2, new Pointer(immGV), this, ty, new Value(CallerSavedRegister::ra));
                            }
                        } else
                            val2 = new Value(op2);

                        new BinaryOperator(iType, ty, new Value(irInst), val1, val2, this);

                        if (needRestore) {
                            if (dynamic_cast<IRConstant *>(op1))
                                new LoadInst(val1, new Pointer(-8), this, IRType::DoubleTy);
                            if (dynamic_cast<IRConstant *>(op2))
                                new LoadInst(val2, new Pointer(-8), this, IRType::DoubleTy);
                        }
                    } else {
                        assert(0 && "Error type");
                    }
                    break;
                }
                case IRInstruction::SetEQ:
                case IRInstruction::SetNE:
                case IRInstruction::SetLE:
                case IRInstruction::SetGE:
                case IRInstruction::SetLT:
                case IRInstruction::SetGT: {
                    auto setInst = dynamic_cast<IRSetCondInst *>(irInst);
                    auto op1 = setInst->getOperand(0);
                    auto op2 = setInst->getOperand(1);
                    auto ty = op1->getType();
                    // 浮点比较才生成
                    if (ty == IRType::DoubleTy || ty == IRType::FloatTy) {
                        Value *val1 = nullptr, *val2 = nullptr;
                        bool needRestore = false;
                        // 如果op1是浮点常数
                        if (dynamic_cast<IRConstant *>(op1)) {
                            if (constMap[dynamic_cast<IRConstant *>(op1)]) {
                                val1 = new Value(constMap[dynamic_cast<IRConstant *>(op1)]);
                            } else {
                                // 将常数申明为全局变量
                                auto immGV = new GlobalVariable(dynamic_cast<IRConstant *>(op1), parent->getParent());
                                // 寻找空闲寄存器
                                auto tempReg = const_cast<Register *>(irInst->getFreeFloatCallerSavedReg());
                                if (tempReg == nullptr) {
                                    // 找不到使用fa0/fa1，将fa0/fa1存储在栈上，运算完之后restore
                                    needRestore = true;
                                    if (op2->getReg() == RegisterFactory::getReg("fa0"))
                                        val1 = new Value(RegisterFactory::getReg("fa1"));
                                    else
                                        val1 = new Value(RegisterFactory::getReg("fa0"));
                                    new StoreInst(val1, new Pointer(-8), this, IRType::DoubleTy);
                                } else {
                                    val1 = new Value(tempReg);
                                }
                                // 将立即数的值load到寄存器中
                                new LoadInst(val1, new Pointer(immGV), this, ty, new Value(CallerSavedRegister::ra));
                            }
                        } else
                            val1 = new Value(op1);
                        // 如果op2是浮点常数
                        if (dynamic_cast<IRConstant *>(op2)) {
                            if (constMap[dynamic_cast<IRConstant *>(op2)]) {
                                val2 = new Value(constMap[dynamic_cast<IRConstant *>(op2)]);
                            } else {
                                // 将常数申明为全局变量
                                auto immGV = new GlobalVariable(dynamic_cast<IRConstant *>(op2), parent->getParent());
                                // 寻找空闲寄存器
                                auto tempReg = const_cast<Register *>(irInst->getFreeFloatCallerSavedReg());
                                if (tempReg == nullptr) {
                                    // 找不到使用fa0，将fa0存储在栈上，运算完之后restore
                                    needRestore = true;
                                    if (op1->getReg() == RegisterFactory::getReg("fa0"))
                                        val2 = new Value(RegisterFactory::getReg("fa1"));
                                    else
                                        val2 = new Value(RegisterFactory::getReg("fa0"));
                                    new StoreInst(val2, new Pointer(-8), this, IRType::DoubleTy);
                                } else {
                                    val2 = new Value(tempReg);
                                }
                                // 将立即数的值load到寄存器中
                                new LoadInst(val2, new Pointer(immGV), this, ty, new Value(CallerSavedRegister::ra));
                            }
                        } else
                            val2 = new Value(op2);

                        switch (setInst->getOpcode()) {
                            case IRInstruction::SetEQ:
                            case IRInstruction::SetNE:
                                new SetCondInst(Instruction::Feq, new Value(setInst), val1, val2,
                                                this);
                                break;
                            case IRInstruction::SetLE:
                                new SetCondInst(Instruction::Fle, new Value(setInst), val1, val2,
                                                this);
                                break;
                            case IRInstruction::SetGT:
                                new SetCondInst(Instruction::Fle, new Value(setInst), val2, val1,
                                                this);
                                break;
                            case IRInstruction::SetLT:
                                new SetCondInst(Instruction::Flt, new Value(setInst), val1, val2,
                                                this);
                                break;
                            case IRInstruction::SetGE:
                                new SetCondInst(Instruction::Flt, new Value(setInst), val2, val1,
                                                this);
                                break;
                        }

                        if (needRestore) {
                            if (dynamic_cast<IRConstant *>(op1))
                                new LoadInst(val1, new Pointer(-8), this, IRType::DoubleTy);
                            if (dynamic_cast<IRConstant *>(op2))
                                new LoadInst(val2, new Pointer(-8), this, IRType::DoubleTy);
                        }
                    }
                    break;
                }
                case IRInstruction::Load: {
                    auto loadInst = dynamic_cast<IRLoadInst *>(irInst);
                    auto irPtr = loadInst->getPointerOperand();
                    auto alloc = dynamic_cast<IRAllocaInst *>(irPtr);
                    auto ty = loadInst->getType();
                    if (IRGlobalVariable::classof(irPtr)) {
                        auto gv = parent->getParent()->findGlobalVariable(dynamic_cast<IRGlobalVariable *>(irPtr));
                        Value *rt = nullptr;
                        if (ty == IRType::DoubleTy || ty == IRType::FloatTy) {
                            rt = new Value(CallerSavedRegister::ra);
                        }
                        new LoadInst(new Value(loadInst), new Pointer(gv), this, ty, rt);
                    } else if (alloc) {
                        auto ptr = parent->getPointer(alloc);
                        if (ty->isPrimitiveType() || ty->getPrimitiveID() == IRType::PointerTyID)
                            new LoadInst(new Value(loadInst), ptr, this, ty);
                        else
                            new BinaryOperator(Instruction::Addi, IRType::IntTy, new Value(loadInst),
                                               new Value(ptr->getBase()), new Value(ptr->getOffset()), this);
                    } else {
                        new LoadInst(new Value(loadInst), new Pointer(0, irPtr->getReg()), this, ty);
                    }
                    break;
                }
                case IRInstruction::Store: {
                    auto storeInst = dynamic_cast<IRStoreInst *>(irInst);
                    auto irPtr = storeInst->getPointerOperand();
                    auto irStVal = storeInst->getOperand(0);
                    auto ty = irStVal->getType();
                    auto alloc = dynamic_cast<IRAllocaInst *>(irPtr);
                    Value *stVal = nullptr;
                    bool needRestore = false;
                    if (dynamic_cast<IRConstant *>(irStVal)) {
                        // 存储值是常数
                        if (constMap[dynamic_cast<IRConstant *>(irStVal)]) {
                            stVal = new Value(constMap[dynamic_cast<IRConstant *>(irStVal)]);
                        } else {
                            if (ty == IRType::IntTy) {
                                new LiInst(stVal = new Value(CallerSavedRegister::ra),
                                           dynamic_cast<IRConstantInt *>(irStVal)->getRawValue(), this);
                            } else if (ty == IRType::BoolTy) {
                                new LiInst(stVal = new Value(CallerSavedRegister::ra),
                                           dynamic_cast<IRConstantBool *>(irStVal)->getRawValue(), this);
                            } else if (ty == IRType::DoubleTy || ty == IRType::FloatTy) {
                                // add GV
                                auto immGV = new GlobalVariable(dynamic_cast<IRConstant *>(irStVal),
                                                                parent->getParent());
                                auto tempReg = const_cast<Register *>(irInst->getFreeFloatCallerSavedReg());
                                if (tempReg == nullptr) {
                                    // 所有的 caller 寄存器全满了，使用 fa0 替代
                                    needRestore = true;
                                    stVal = new Value(RegisterFactory::getReg("fa0"));
                                    new StoreInst(stVal, new Pointer(-8), this, IRType::DoubleTy);
                                } else {
                                    stVal = new Value(tempReg);
                                }
                                new LoadInst(stVal, new Pointer(immGV), this, ty, new Value(CallerSavedRegister::ra));
                            } else
                                assert(0 && "Error Type");
                        }
                    } else
                        stVal = new Value(irStVal);
                    if (IRGlobalVariable::classof(irPtr)) {
                        // store rd, symbol, rt
                        Value *rt = nullptr;
                        if (stVal->getReg() == CallerSavedRegister::ra) {
                            rt = new Value(RegisterFactory::getReg("a0"));
                            new StoreInst(rt, new Pointer(-8), this);
                        } else
                            rt = new Value(CallerSavedRegister::ra);
                        auto gv = parent->getParent()->findGlobalVariable(dynamic_cast<IRGlobalVariable *>(irPtr));
                        new StoreInst(stVal, new Pointer(gv), this, ty, rt);
                        if (rt->getReg() == RegisterFactory::getReg("a0")) {
                            new LoadInst(rt, new Pointer(-8), this);
                        }
                    } else if (alloc) {
                        // 栈上地址
                        new StoreInst(stVal, parent->getPointer(alloc), this, ty);
                    } else {
                        new StoreInst(stVal, new Pointer(0, irPtr->getReg()), this, ty);
                    }
                    if (needRestore)
                        new LoadInst(stVal, new Pointer(-8), this, IRType::DoubleTy);
                    break;
                }
                case IRInstruction::Memcpy: {
                    auto memcpyInst = dynamic_cast<IRMemcpyInst *>(irInst);
                    auto src = dynamic_cast<IRGlobalVariable *>(memcpyInst->getSrcPointerOperand());
                    auto dest = dynamic_cast<IRAllocaInst *>(memcpyInst->getDestPointerOperand());
                    auto arrTy = dynamic_cast<IRArrayType *>(src->getType()->getElementType());
                    auto srcPtrBase = new Value(CallerSavedRegister::ra);
                    auto destPtrBase = parent->getPointer(dest)->getBase();
                    auto destPtrOffset = parent->getPointer(dest)->getOffset();
                    auto gv = parent->getParent()->findGlobalVariable(src);
                    // la
                    new LoadInst(srcPtrBase, new Pointer(gv), this, arrTy);
                    auto rt = new Value(RegisterFactory::getReg("a0"));
                    new StoreInst(rt, new Pointer(-8), this);
                    auto size = arrTy->getNumElements() * arrTy->getElementType()->getPrimitiveSize();
                    for (unsigned i = 0; i < size; i += 8) {
                        new LoadInst(rt, new Pointer(i, CallerSavedRegister::ra), this);
                        new StoreInst(rt, new Pointer(i + destPtrOffset, destPtrBase), this);
                    }
                    new LoadInst(rt, new Pointer(-8), this);
                    break;
                }
                case IRInstruction::Call: {
                    auto callInst = dynamic_cast<IRCallInst *>(irInst);
                    auto callerRegList = irInst->getCallerSavedLiveRegList();
                    auto regSize = Function::alignSize(8 * callerRegList.size());
                    // 申请栈空间
                    if (regSize)
                        new BinaryOperator(Instruction::Addi, IRType::IntTy, new Value(CalleeSavedRegister::sp),
                                           new Value(CalleeSavedRegister::sp),
                                           new Value(-regSize), this);
                    // 存储caller寄存器
                    int index = 0;
                    for (auto reg: callerRegList) {
                        if (reg->getRegty() == Register::FloatCallerSaved)
                            new StoreInst(new Value(reg), new Pointer(index), this, IRType::DoubleTy);
                        else
                            new StoreInst(new Value(reg), new Pointer(index), this);
                        index += 8;
                    }
                    // 设置 a0..a7
                    for (unsigned i = 1, E = callInst->getNumOperands(), Idx = 0, fIdx = 0; i < E; ++i) {
                        auto param = callInst->getOperand(i);
                        Value *dest = nullptr;
                        if (param->getType() == IRType::DoubleTy || param->getType() == IRType::FloatTy) {
                            dest = new Value(RegisterFactory::getReg("fa" + std::to_string(fIdx)));
                            ++fIdx;
                        } else {
                            dest = new Value(RegisterFactory::getReg("a" + std::to_string(Idx)));
                            ++Idx;
                        }
                        auto imm = dynamic_cast<IRConstant *>(param);
                        if (imm) {
                            if (constMap[imm]) {
                                // 翻译为mv
                                if (dest->getReg() != constMap[imm])
                                    new MoveInst(imm->getType(), dest, new Value(constMap[imm]), this);
                            } else {
                                if (imm->getType() == IRType::FloatTy || imm->getType() == IRType::DoubleTy) {
                                    // 翻译为load
                                    auto immGV = new GlobalVariable(imm, parent->getParent());
                                    new LoadInst(dest, new Pointer(immGV), this, imm->getType(),
                                                 new Value(CallerSavedRegister::ra));
                                } else if (imm->getType() == IRType::BoolTy) {
                                    // 翻译为li
                                    new LiInst(dest, dynamic_cast<IRConstantBool *>(imm)->getRawValue(), this);
                                } else if (imm->getType() == IRType::IntTy) {
                                    // 翻译为li
                                    new LiInst(dest, dynamic_cast<IRConstantInt *>(imm)->getRawValue(), this);
                                } else {
                                    assert(0 && "Error Type");
                                }
                            }
                        } else {
                            if (dest->getReg() != param->getReg())
                                new MoveInst(param->getType(), dest, new Value(param), this);
                        }
                    }
                    // 生成call
                    if (callInst->getCalledFunction()->getName() == parent->getName())
                        new CallInst(parent, this);
                    else
                        new CallInst(parent->getParent()->findFunction(callInst->getCalledFunction()), this);
                    Value *src = nullptr;
                    if (callInst->getType() == IRType::DoubleTy || callInst->getType() == IRType::FloatTy) {
                        src = new Value(RegisterFactory::getReg("fa0"));
                    } else if (callInst->getType() == IRType::IntTy || callInst->getType() == IRType::BoolTy) {
                        src = new Value(RegisterFactory::getReg("a0"));
                    }
                    if (src && src->getReg() != callInst->getReg())
                        new MoveInst(callInst->getType(), new Value(callInst), src, this);
                    // 恢复 caller 寄存器
                    index = 0;
                    for (auto reg: callerRegList) {
                        if (callInst->getReg() == reg) {
                            index += 8;
                            continue;
                        }
                        if (reg->getRegty() == Register::FloatCallerSaved)
                            new LoadInst(new Value(reg), new Pointer(index), this, IRType::DoubleTy);
                        else
                            new LoadInst(new Value(reg), new Pointer(index), this);
                        index += 8;
                    }
                    if (regSize)
                        new BinaryOperator(Instruction::Addi, IRType::IntTy, new Value(CalleeSavedRegister::sp),
                                           new Value(CalleeSavedRegister::sp),
                                           new Value(regSize), this);
                    break;
                }
                case IRInstruction::Move: {
                    auto mvInst = dynamic_cast<IRMoveInst *>(irInst);
                    auto irSrc = mvInst->getSrc();
                    auto irDest = mvInst->getDest();
                    auto imm = dynamic_cast<IRConstant *>(irSrc);
                    if (imm) {
                        if (constMap[imm]) {
                            // 翻译为mv
                            if (constMap[imm] != irDest->getReg())
                                new MoveInst(irSrc->getType(), new Value(irDest), new Value(constMap[imm]), this);
                        } else {
                            if (imm->getType() == IRType::FloatTy || imm->getType() == IRType::DoubleTy) {
                                // 翻译为load
                                auto immGV = new GlobalVariable(imm, parent->getParent());
                                new LoadInst(new Value(irDest), new Pointer(immGV), this, imm->getType(),
                                             new Value(CallerSavedRegister::ra));
                            } else if (imm->getType() == IRType::IntTy)
                                // 翻译为li
                                new LiInst(new Value(irDest), dynamic_cast<IRConstantInt *>(imm)->getRawValue(), this);
                            else if (imm->getType() == IRType::BoolTy)
                                // 翻译为li
                                new LiInst(new Value(irDest), dynamic_cast<IRConstantBool *>(imm)->getRawValue(), this);
                            else
                                assert(0 && "Error Type");
                        }
                    } else {
                        if (irSrc->getReg() != irDest->getReg())
                            new MoveInst(irSrc->getType(), new Value(irDest), new Value(irSrc), this);
                    }
                    break;
                }
                case IRInstruction::Alloca:
                    break;
                case IRInstruction::Xor: {
                    new BinaryOperator(Instruction::Xori, IRType::BoolTy, new Value(irInst),
                                       new Value(irInst->getOperand(1)), new Value(1), this);
                    break;
                }
                default:
                    irInst->print(std::cerr);
                    assert(0 && "unknown ir instruction");
            }
        }
    }

    void BasicBlock::setName(const std::string &name) {
        BasicBlock::name = name;
    }

    const std::string &BasicBlock::getName() const {
        return name;
    }

    const std::vector<Instruction *> &BasicBlock::getInstList() const {
        return InstList;
    }
} // RISCV