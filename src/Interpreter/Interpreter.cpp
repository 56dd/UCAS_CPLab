//
// Created by yuanjunkang on 24-5-5.
//

#include "Interpreter.h"
#include "IR/IRConstant.h"
#include "IR/iMemory.h"

std::map<IRValue *, TemporaryVariable *> Interpreter::GlobalVarMap;
std::vector<TemporaryVariable *> Interpreter::Stack;
bool Interpreter::debugOpt;
int Interpreter::inst_cnt;

Interpreter::Interpreter(IRModule *ir) : ir(ir) {
}

int Interpreter::interpret() {
    auto mainFunc = ir->getMainFunction();
    auto varList = ir->getVarList();
    initGlobalVar(varList);
    Stack.push_back(new TemporaryVariable(0, TemporaryVariable::Func));   // 把函数标识符放入栈
    TemporaryVariable *ret = interpretFunction(mainFunc);
    return std::any_cast<int>(ret->getValue());
}


void Interpreter::initGlobalVar(const std::vector<IRGlobalVariable *> &varVector) {
    for (auto var: varVector) {
        auto initializer = var->getInitializer();
        auto varType = getTempVarType(var->getType());
        auto tempVar = change_ConstantVal_to_TemporaryVariable(initializer);
        Stack.push_back(new TemporaryVariable(tempVar->getValue(), tempVar->getType(),
                                              tempVar->getElementType(), tempVar->getArraySize()));
        GlobalVarMap[var] = new TemporaryVariable(Stack.size() - 1,
                                                  TemporaryVariable::Pointer,
                                                  varType);
        if (debugOpt)
            tempVar->print();
    }
}

void Interpreter::initFuncArg(const std::vector<IRArgument *> &argVector, std::map<IRValue *, TemporaryVariable *> &tempVarMap) {
    auto argNum = argVector.size();
    auto stackSize = Stack.size();
    for (int i = 0; i < argNum; ++i) {
        tempVarMap[argVector[i]] = Stack[stackSize - argNum + i];
    }
}

TemporaryVariable *Interpreter::interpretFunction(IRFunction *func) {
    if (debugOpt)
        std::cout << "Func Name: " << func->getName() << std::endl;

    std::map<IRValue *, TemporaryVariable *> tempVarMap;
    tempVarMap.clear();

    auto argList = func->getArgumentList(); // 函数参数列表
    initFuncArg(argList, tempVarMap);   // 初始化参数列表
    auto entryBlock = func->getEntryBlock();
    auto currentBlock = entryBlock;
    IRBasicBlock *lastBlock = currentBlock;

    InterpretBasicBlock:
    auto instList = currentBlock->getInstList();

    if (debugOpt)
        std::cout << "Block Name: " << currentBlock->getName() << std::endl;

    for (auto inst: instList) {
//        getchar();
        auto opcode = inst->getOpcode();
        ++inst_cnt;

        if (debugOpt) {
            std::cout << "Inst Name: " << inst->getName();
            printf(", Opname = %s, ", inst->getOpcodeName());
        }

        auto operandNum = inst->getNumOperands();

        if (debugOpt) {
            printf("Operand Number = %d\n", operandNum);
            for (int i = 0; i < operandNum; ++i) {
                if (inst->getOpcode() == IRInstruction::Br && (i == 0 || i == 1))
                    continue;
                if (inst->getOpcode() == IRInstruction::PHI || inst->getOpcode() == IRInstruction::Call)
                    continue;
                printf("Operand ");
                std::cout << inst->getOperand(i)->getName() << ": ";
                if (change_Operand_To_TemporaryVariable(inst->getOperand(i), tempVarMap))
                    change_Operand_To_TemporaryVariable(inst->getOperand(i), tempVarMap)->print();
            }
        }
        switch (opcode) {
            case IRInstruction::Ret : {
                TemporaryVariable* ret;
                if (operandNum == 0) {
                    ret = new TemporaryVariable(nullptr, TemporaryVariable::Void);
                    if (debugOpt) {
                        ret->print();
                    }
                } else if (operandNum == 1) {
                    auto operand = inst->getOperand(0);
                    ret = change_Operand_To_TemporaryVariable(operand, tempVarMap);
                    if (debugOpt) {
                        ret->print();
                    }
                }

                while (Stack.back()->getType() != TemporaryVariable::Func) {   // 弹出局部变量和参数，直到遇到函数标识符
                    Stack.pop_back();
                }
                Stack.pop_back();   // 弹出函数标识符

                return ret;
            }
            case IRInstruction::Br : {
                if (operandNum == 1) {
                    auto dest = inst->getOperand(0);
                    if (dest->getValueType() != IRValue::BasicBlockVal) {
                        printf("Branch Operand is not BasicBlockVal valueType\n");
                    }
                    lastBlock = currentBlock;
                    currentBlock = dynamic_cast<IRBasicBlock *>(dest);
                } else {
                    if (operandNum != 3) {
                        printf("Undefined Branch Inst With Operand Number = %d\n");
                    }

                    auto destTrue = inst->getOperand(0);
                    auto destFalse = inst->getOperand(1);
                    auto cond = inst->getOperand(2);
                    auto tempVarCond = change_Operand_To_TemporaryVariable(cond, tempVarMap);

                    if (tempVarCond->getType() != TemporaryVariable::Bool) {
                        printf("Cannot Branch With Condition Type: ");
                        std::cout << TemporaryVariable::getTypeString(tempVarCond->getType()) << std::endl;
                    }

                    if (std::any_cast<bool>(tempVarCond->getValue())) {
                        lastBlock = currentBlock;
                        currentBlock = dynamic_cast<IRBasicBlock *>(destTrue);
                    } else {
                        lastBlock = currentBlock;
                        currentBlock = dynamic_cast<IRBasicBlock *>(destFalse);
                    }
                }
                goto InterpretBasicBlock;
            }

            case IRInstruction::Add : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 + *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::Sub : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 - *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::Mul : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 * *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::Div : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 / *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::Rem : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 % *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::And : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 && *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::Or : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 || *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::Xor : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 ^ *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::SetLE : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 <= *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::SetGE : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 >= *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::SetLT : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 < *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::SetGT : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 > *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::SetEQ : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 == *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::SetNE : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 != *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::Alloca : {
                auto seqType = dynamic_cast<IRSequentialType *>(inst->getType());
                auto operand = inst->getOperand(0);
                auto varType = getTempVarType(seqType->getElementType());
                auto tempVar = allocaOnStack(operand, varType);
                Stack.push_back(new TemporaryVariable(tempVar->getValue(),
                                                      tempVar->getType(),
                                                      tempVar->getElementType(),
                                                      tempVar->getArraySize()));
                tempVarMap[inst] = new TemporaryVariable{Stack.size() - 1, TemporaryVariable::Pointer, varType};
                if (debugOpt)
                    tempVar->print();
                break;
            }

            case IRInstruction::Load : {
                auto operand = inst->getOperand(0);
                auto tempVar = change_Operand_To_TemporaryVariable(operand, tempVarMap);
                if (tempVar->getType() != TemporaryVariable::Pointer) {
                    printf("Error: Load operand is not Pointer type!");
                }
                auto offset = std::any_cast<unsigned long>(tempVar->getValue());
                TemporaryVariable *loadVar;
                loadVar = Stack[offset];
                tempVarMap[inst] = new TemporaryVariable{loadVar->getValue(),
                                                         loadVar->getType(),
                                                         loadVar->getElementType(),
                                                         loadVar->getArraySize()};
                if (debugOpt)
                    loadVar->print();
                break;
            }

            case IRInstruction::Store : {
                auto operand0 = inst->getOperand(0);
                auto operand1 = inst->getOperand(1);
                auto tempVar0 = change_Operand_To_TemporaryVariable(operand0, tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(operand1, tempVarMap);
                if (tempVar1->getType() != TemporaryVariable::Pointer) {
                    printf("Error: Store destination is not Pointer type!");
                }
                auto offset = std::any_cast<unsigned long>(tempVar1->getValue());
                Stack[offset]->setValue(tempVar0->getValue());
                Stack[offset]->setType(tempVar0->getType());
                Stack[offset]->setElementType(tempVar0->getElementType());
                Stack[offset]->setArraySize(tempVar0->getArraySize());
                if (debugOpt)
                    Stack[offset]->print();
                break;
            }

            case IRInstruction::Memcpy : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(
                        dynamic_cast<IRMemcpyInst *>(inst)->getSrcPointerOperand(), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(
                        dynamic_cast<IRMemcpyInst *>(inst)->getDestPointerOperand(), tempVarMap);
                auto pointer_offset0 = std::any_cast<unsigned long>(tempVar0->getValue());
                auto pointer_offset1 = std::any_cast<unsigned long>(tempVar1->getValue());
                auto array0 = Stack[pointer_offset0];
                auto array1 = Stack[pointer_offset1];
                auto array0_address = std::any_cast<unsigned long>(array0->getValue());
                auto array1_address = std::any_cast<unsigned long>(array1->getValue());
                auto arraySize = array0->getArraySize();
                for (auto i = 0; i < arraySize; ++i) {
                    Stack[array1_address + i]->setValue(Stack[array0_address + i]->getValue());
                    Stack[array1_address + i]->setType(Stack[array0_address + i]->getType());
                    Stack[array1_address + i]->setElementType(Stack[array0_address + i]->getElementType());
                    Stack[array1_address + i]->setArraySize(Stack[array0_address + i]->getArraySize());
                }
                break;
            }

            case IRInstruction::PHI : {
                auto labelNum = operandNum / 2;
                auto foundLabel = false;
                for (auto i = 0; i < labelNum; ++i) {
                    auto label = inst->getOperand(2 * i + 1);
                    if (label->getName() == lastBlock->getName()) {
                        auto tempVar = change_Operand_To_TemporaryVariable(inst->getOperand(2 * i), tempVarMap);
                        tempVarMap[inst] = new TemporaryVariable{tempVar->getValue(),
                                                                 tempVar->getType(),
                                                                 tempVar->getElementType(),
                                                                 tempVar->getArraySize()};
                        foundLabel = true;
                        break;
                    }
                }
                if (!foundLabel)
                    printf("Phi: Failed to Find LastBlock Label in Given Label List!\n");
                break;
            }

            case IRInstruction::Call : {
                auto operand0 = inst->getOperand(0);

                auto funcName = operand0->getName();

                if (operand0->getValueType() != IRValue::FunctionVal) {
                    printf("Call Operand0 is not FunctionVal valueType\n");
                }

                Stack.push_back(new TemporaryVariable(0, TemporaryVariable::Func));   // 把函数标识符放入栈

                for (int i = 1; i < operandNum; ++i) {    // 把参数放入栈里
                    auto operand_i = inst->getOperand(i);
                    auto arg_i = change_Operand_To_TemporaryVariable(operand_i, tempVarMap);
                    Stack.push_back(new TemporaryVariable{arg_i->getValue(),
                                                          arg_i->getType(),
                                                          arg_i->getElementType(),
                                                          arg_i->getArraySize()});
                }

                TemporaryVariable *ret = nullptr;
                if (isBuildInFunction(funcName)) {   // 内置函数
                    ret = runBuildInFunction(funcName);
                } else {
                    auto callFunc = dynamic_cast<IRFunction *>(operand0);    // 函数指针
                    ret = interpretFunction(callFunc);
                }
                tempVarMap[inst] = new TemporaryVariable{ret->getValue(),
                                                         ret->getType(),
                                                         ret->getElementType(),
                                                         ret->getArraySize()};

                if(debugOpt) {
                    printf("return Value of Call: ");
                    ret->print();
                }
                break;
            }

            case IRInstruction::Shl : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 << *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::Shr : {
                auto tempVar0 = change_Operand_To_TemporaryVariable(inst->getOperand(0), tempVarMap);
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                TemporaryVariable result = *tempVar0 >> *tempVar1;
                tempVarMap[inst] = new TemporaryVariable{result.getValue(),
                                                         result.getType(),
                                                         result.getElementType(),
                                                         result.getArraySize()};
                if (debugOpt)
                    result.print();
                break;
            }

            case IRInstruction::Move : {
                auto tempVar0 = new TemporaryVariable{0, TemporaryVariable::Void};
                tempVarMap[inst->getOperand(0)] = tempVar0;
                auto tempVar1 = change_Operand_To_TemporaryVariable(inst->getOperand(1), tempVarMap);
                tempVar0->setValue(tempVar1->getValue());
                tempVar0->setType(tempVar1->getType());
                tempVar0->setElementType(tempVar1->getElementType());
                tempVar0->setArraySize(tempVar1->getArraySize());
                if (debugOpt)
                    tempVar0->print();
                break;
            }

            default: {
                printf("Undefined Operator: %s\n", inst->getOpcodeName());
            }
        }
    }
}

TemporaryVariable *Interpreter::change_Operand_To_TemporaryVariable(IRValue *irValue, std::map<IRValue *, TemporaryVariable *> &tempVarMap) {
    auto valueType = irValue->getValueType();
    if (valueType == IRValue::GlobalVariableVal) {
        return GlobalVarMap[irValue];
    }
    if (valueType == IRValue::ArgumentVal || valueType == IRValue::InstructionVal) {
        if (!tempVarMap[irValue]) {
            printf("tempVar of irValue is NULL!");
        }
        return tempVarMap[irValue];
    } else if (valueType == IRValue::ConstantVal) {
        return change_ConstantVal_to_TemporaryVariable(irValue);
    } else {
        printf("Cannot change IRValue: ");
        std::cout << irValue->getName() << std::endl;
        printf(" to TemporaryVariable");
    }
}

TemporaryVariable::tempVarType Interpreter::getTempVarType(IRType *ty) {
    switch (ty->getPrimitiveID()) {
        case IRType::VoidTyID : {
            return TemporaryVariable::tempVarType::Void;
        }
        case IRType::BoolTyID : {
            return TemporaryVariable::tempVarType::Bool;
        }
        case IRType::IntTyID : {
            return TemporaryVariable::tempVarType::Int;
        }
        case IRType::FloatTyID : {
            return TemporaryVariable::tempVarType::Float;
        }
        case IRType::DoubleTyID : {
            return TemporaryVariable::tempVarType::Double;
        }
        case IRType::PointerTyID : {
            return TemporaryVariable::tempVarType::Pointer;
        }
        case IRType::ArrayTyID : {
            return TemporaryVariable::tempVarType::Pointer;
        }
        default: {
            printf("Cannot change IRType to tempVarType\n");
        }
    }
}

TemporaryVariable *Interpreter::change_ConstantVal_to_TemporaryVariable(IRValue *irValue) {
    if (irValue->getType()->getPrimitiveID() == IRType::ArrayTyID) {
        auto arrayType = dynamic_cast<IRConstantArray *>(irValue);
        auto elementList = arrayType->getValues();
        auto arraySize = 0;
        TemporaryVariable::tempVarType elementTy;
        for (const auto &element: elementList) {
            auto val = element.get();
            auto constValue = dynamic_cast<IRConstant *>(val);
            if(constValue->getConstTy() == IRConstant::init) {
                auto initializer = dynamic_cast<IRConstantinitializer *>(constValue);
                auto initSize = initializer->getInitSize();
                auto initConst = initializer->getInitconst();
                arraySize += initSize;
                for(auto i = 0; i < initSize; ++i){
                    auto elementType = getTempVarType(val->getType());
                    elementTy = elementType;
                    auto tempVar = change_ConstantVal_to_TemporaryVariable(initConst);
                    Stack.push_back(new TemporaryVariable(tempVar->getValue(), tempVar->getType(),
                                                          tempVar->getElementType(), tempVar->getArraySize()));
                }
            }
            else {
                arraySize += 1;
                auto elementType = getTempVarType(val->getType());
                elementTy = elementType;
                auto tempVar = change_ConstantVal_to_TemporaryVariable(val);
                Stack.push_back(new TemporaryVariable(tempVar->getValue(), tempVar->getType(),
                                                      tempVar->getElementType(), tempVar->getArraySize()));
            }
        }
        return new TemporaryVariable(Stack.size() - arraySize, TemporaryVariable::Pointer, elementTy, arraySize);
    }



    auto ty = getTempVarType(irValue->getType());
    switch (ty) {
        case TemporaryVariable::Int : {
            auto constInt = dynamic_cast<IRConstantInt *>(irValue);
            auto val = constInt->getRawValue();
            return new TemporaryVariable{val, TemporaryVariable::Int};
        }
        case TemporaryVariable::Float : {
            auto constFloat = dynamic_cast<IRConstantFloat *>(irValue);
            auto val = constFloat->getRawValue();
            return new TemporaryVariable{val, TemporaryVariable::Float};
        }
        case TemporaryVariable::Double : {
            auto constDouble = dynamic_cast<IRConstantDouble *>(irValue);
            auto val = constDouble->getRawValue();
            return new TemporaryVariable{val, TemporaryVariable::Double};
        }
        case TemporaryVariable::Bool : {
            auto constBool = dynamic_cast<IRConstantBool *>(irValue);
            auto val = constBool->getRawValue();
            return new TemporaryVariable{(bool) val, TemporaryVariable::Bool};
        }
        case TemporaryVariable::Void : {
            return new TemporaryVariable{nullptr, TemporaryVariable::Void};
        }
        default : {
            printf("Cannot change type:");
            std::cout << TemporaryVariable::getTypeString(ty);
            printf(" to TemporaryVariable\n");
        }
    }
}

TemporaryVariable *Interpreter::allocaOnStack(IRValue *irValue, TemporaryVariable::tempVarType varType) {
    if (irValue->getType()->getPrimitiveID() == IRType::ArrayTyID) {
        auto arrayType = dynamic_cast<IRConstantArray *>(irValue);
        auto elementList = arrayType->getValues();
        auto arraySize = elementList.size();
        auto elementType = getTempVarType(arrayType->getType()->getElementType());
        for (int i = 0; i < arraySize; ++i) {
            Stack.push_back(new TemporaryVariable(get_initial_value(elementType), elementType));
        }
        return new TemporaryVariable(Stack.size() - arraySize, varType, elementType, arraySize);
    } else {
        return new TemporaryVariable(get_initial_value(varType), varType);
    }
}

std::any Interpreter::get_initial_value(TemporaryVariable::tempVarType ty) {
    switch (ty) {
        case TemporaryVariable::Int :
            return (int) 0;
        case TemporaryVariable::Float :
            return (float) 0;
        case TemporaryVariable::Double :
            return (double) 0;
        case TemporaryVariable::Bool :
            return false;
        case TemporaryVariable::Pointer :
            return (unsigned long) 0;
        default : {
            return nullptr;
        }
    }
}

bool Interpreter::isBuildInFunction(const std::string &funcName) {
    if (funcName == "print_int") return true;
    if (funcName == "print_float") return true;
    if (funcName == "print_double") return true;
    if (funcName == "print_bool") return true;
    if (funcName == "get_int") return true;
    if (funcName == "get_float") return true;
    if (funcName == "get_double") return true;
    return false;
}

TemporaryVariable *Interpreter::runBuildInFunction(const std::string &funcName) {
    TemporaryVariable *ret;

    if (funcName == "print_int") {
        if (Stack.back()->getType() != TemporaryVariable::Int) {
            printf("print_int Error: variable type = ");
            std::cout << TemporaryVariable::getTypeString(Stack.back()->getType()) << std::endl;
        }
        auto val = std::any_cast<int>(Stack.back()->getValue());
        printf("%d\n", val);
        ret = new TemporaryVariable(nullptr, TemporaryVariable::Void);
    }

    if (funcName == "print_float") {
        if (Stack.back()->getType() != TemporaryVariable::Float) {
            printf("print_float Error: variable type = ");
            std::cout << TemporaryVariable::getTypeString(Stack.back()->getType()) << std::endl;
        }
        auto val = std::any_cast<float>(Stack.back()->getValue());
        printf("%f\n", val);
        ret = new TemporaryVariable(nullptr, TemporaryVariable::Void);
    }

    if (funcName == "print_double") {
        if (Stack.back()->getType() != TemporaryVariable::Double) {
            printf("print_double Error: variable type = ");
            std::cout << TemporaryVariable::getTypeString(Stack.back()->getType()) << std::endl;
        }
        auto val = std::any_cast<double>(Stack.back()->getValue());
        printf("%lf\n", val);
        ret = new TemporaryVariable(nullptr, TemporaryVariable::Void);
    }

    if (funcName == "print_bool") {
        if (Stack.back()->getType() != TemporaryVariable::Bool) {
            printf("print_bool Error: variable type = ");
            std::cout << TemporaryVariable::getTypeString(Stack.back()->getType()) << std::endl;
        }
        int val = std::any_cast<bool>(Stack.back()->getValue());
        if (val) puts("true");
        else puts("false");
        ret = new TemporaryVariable(nullptr, TemporaryVariable::Void);
    }

    if (funcName == "get_int") {
        int val;
//        printf("get_int: ");
        std::cin >> val;
        ret = new TemporaryVariable(val, TemporaryVariable::Int);
    }

    if (funcName == "get_float") {
        float val;
//        printf("get_float: ");
        std::cin >> val;
        ret = new TemporaryVariable(val, TemporaryVariable::Float);
    }

    if (funcName == "get_double") {
        double val;
//        printf("get_double: ");
        std::cin >> val;
        ret = new TemporaryVariable(val, TemporaryVariable::Double);
    }

    while (Stack.back()->getType() != TemporaryVariable::Func) {   // 弹出临时变量，直到遇到函数标识符
        Stack.pop_back();
    }
    Stack.pop_back();   // 弹出函数标识符

    return ret;
}

int Interpreter::getInstCnt() {
    return inst_cnt;
}
