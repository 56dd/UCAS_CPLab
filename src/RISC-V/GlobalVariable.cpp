#include "GlobalVariable.h"
#include "Module.h"
#include "IR/IRGlobalVariable.h"
#include <iostream>
#include <cassert>
#include <iomanip>
#include "IR/IRConstant.h"

namespace RISCV {
    GlobalVariable::GlobalVariable(IRGlobalVariable *irGV, Module *module) {
        this->irGV = irGV;
        name = irGV->getName();
        initializer = irGV->getInitializer();
        IRType *ty = nullptr;
        if (IRArrayType::classof(irGV->getType()->getElementType())) {
            // 是数组
            auto arrayType = dynamic_cast<IRArrayType *>(irGV->getType()->getElementType());
            size = arrayType->getNumElements() * (arrayType->getElementType()->getPrimitiveSize());
            ty = arrayType->getElementType();
        } else {
            // 不是数组
            auto varType = irGV->getType()->getElementType();
            size = varType->getPrimitiveSize();
            ty = varType;
        }
        assert(ty->isPrimitiveType() && "Error ty");
        if (irGV->isConstant()) {
            section = Section::RODATA;
        } else {
            if (irGV->isIsinitial() || ty == IRType::FloatTy || ty == IRType::DoubleTy) {
                section = Section::DATA;
            } else {
                section = Section::BSS;
            }
        }
        if (module)
            module->addGlobalVariable(this);
    }

    IRGlobalVariable *GlobalVariable::getIrGv() const {
        return irGV;
    }

    void GlobalVariable::print(std::ostream &O) {
        O << "\t.globl\t" << name << "_obj" << std::endl;
        O << "\t" << getSectionName() << std::endl;
        O << "\t.align\t" << align << std::endl;
        O << "\t.type\t" << name << "_obj" << ", @object" << std::endl;
        O << "\t.size\t" << name << "_obj, " << size << std::endl;
        O << name << "_obj:" << std::endl;
        printInitVal(O);
        O << std::endl;
    }

    std::string GlobalVariable::getSectionName() {
        switch (section) {
            case BSS:
                return ".bss";
            case DATA:
                return ".data";
            case RODATA:
                return ".section .rodata";
            default:
                assert(0 && "error section");
        }
    }

    void GlobalVariable::printInitVal(std::ostream &O) {
        switch (initializer->getType()->getPrimitiveID()) {
            case IRType::IntTyID:
                O << "\t.word " << dynamic_cast<IRConstantInt *>(initializer)->getRawValue() << std::endl;
                break;
            case IRType::FloatTyID:
                O << "\t.float " << std::fixed << std::setprecision(6)
                  << dynamic_cast<IRConstantFloat *>(initializer)->getRawValue() << std::endl;
                break;
            case IRType::DoubleTyID:
                O << "\t.double " << std::fixed << std::setprecision(15)
                  << dynamic_cast<IRConstantDouble *>(initializer)->getRawValue() << std::endl;
                break;
            case IRType::BoolTyID:
                O << "\t.byte " << dynamic_cast<IRConstantBool *>(initializer)->getRawValue() << std::endl;
                break;
            case IRType::ArrayTyID:
                auto initVec = dynamic_cast<IRConstantArray *>(initializer)->getValues();
                auto ty = initVec.front().get()->getType();
                auto size = ty->getPrimitiveSize();
                if (dynamic_cast<IRConstantinitializer *>(initVec.front().get()) == nullptr) {
                    printType(O, ty);
                }
                for (const auto &irUse: initVec) {
                    auto val = dynamic_cast<IRConstant *>(irUse.get());
                    if (dynamic_cast<IRConstantinitializer *>(val) == nullptr) {
                        printVal(O, val);
                    } else {
                        if (irUse != initVec.front()) {
                            O.seekp(static_cast<std::streampos>(static_cast<std::streamoff>(O.tellp()) - 2));
                            O << std::endl;
                        }
                        auto zeroInit = dynamic_cast<IRConstantinitializer *>(irUse.get());
                        O << "\t.zero " << zeroInit->getInitSize() * size << std::endl;
                    }
                }
                if (dynamic_cast<IRConstantinitializer *>(initVec.back().get()) == nullptr) {
                    O.seekp(static_cast<std::streampos>(static_cast<std::streamoff>(O.tellp()) - 2));
                    O << std::endl;
                }
        }
    }

    void GlobalVariable::printType(std::ostream &O, IRType *type) {
        switch (type->getPrimitiveID()) {
            case IRType::IntTyID:
                O << "\t.word ";
                break;
            case IRType::FloatTyID:
                O << "\t.float ";
                break;
            case IRType::DoubleTyID:
                O << "\t.double ";
                break;
            case IRType::BoolTyID:
                O << "\t.byte ";
                break;
            default:
                assert(0 && "wtf");
        }
    }

    void GlobalVariable::printVal(std::ostream &O, IRConstant *val) {
        switch (val->getType()->getPrimitiveID()) {
            case IRType::IntTyID:
                O << dynamic_cast<IRConstantInt *>(val)->getRawValue() << ", ";
                break;
            case IRType::FloatTyID:
                O << std::fixed << std::setprecision(6)
                  << dynamic_cast<IRConstantFloat *>(val)->getRawValue() << ", ";
                break;
            case IRType::DoubleTyID:
                O << std::fixed << std::setprecision(15)
                  << dynamic_cast<IRConstantDouble *>(val)->getRawValue() << ", ";
                break;
            case IRType::BoolTyID:
                O << dynamic_cast<IRConstantBool *>(val)->getRawValue() << ", ";
                break;
            default:
                assert(0 && "wtf");
        }
    }

    const std::string &GlobalVariable::getName() const {
        return name;
    }

    GlobalVariable::GlobalVariable(IRConstant *irConstant, Module *module) {
        irGV = nullptr;
        initializer = irConstant;
        name = "Constant" + std::to_string(module->getLabelCount());
        section = Section::RODATA;
        size = irConstant->getType()->getPrimitiveSize();
        module->addGlobalVariable(this);
    }
} // RISCV