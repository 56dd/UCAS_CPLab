#include "symbolTable.h"
#include "IR/IRArgument.h"
#include "IR/IRBasicBlock.h"
#include "IR/IRDerivedTypes.h"
#include "IR/IRModule.h"
#include "IR/IRType.h"
#include "IR/IRValue.h"
#include "IR/IRConstant.h"
#include "IR/IRGlobalValue.h"
#include "IR/IRGlobalVariable.h"
#include "IR/IRInstruction.h"
#include "IR/iMemory.h"
#include "IR/IRFunction.h"
#include "cassert"
#include "utils/CACT.h"

#include <cstddef>
#include <iostream>
#include <string>

std::string ToString(DataType x) {
    if (x == VOID) {
        return "void";
    } else if (x == BOOL) {
        return "bool";
    } else if (x == INT) {
        return "int";
    } else if (x == FLOAT) {
        return "float";
    } else if (x == DOUBLE) {
        return "double";
    }
    return "unknown";
}

int SizeOfDataType(DataType x) {
    if (x == BOOL) {
        return 4;
    } else if (x == INT) {
        return 4;
    } else if (x == FLOAT) {
        return 4;
    } else if (x == DOUBLE) {
        return 8;
    }
    return 0;
}


/***********符号表***********/
SymbolInfo::SymbolInfo(const std::string &name, int line)
        : name(name), operand(nullptr), line(line) {}

void SymbolInfo::setOp(IROperand *op) {
    operand = op;
}

IROperand *SymbolInfo::getOp() {
    if (!operand) {
        throw std::runtime_error("try to get null op");
    }
    return operand;
}

void ConstSymbolInfo::setIRValue() {
    irValue = initValueArray[0];
}

void VarSymbolInfo::setIRValue(IRValue::ValueTy vTy, unsigned SymbolCount, IRBasicBlock *parent, IRValue *IRinitializer,
                               IRModule *irmodule) {

    /******对一个var而言,所有显式和非显式的初始化全部都在外面做好之后压到initvaluearray里面******/
    if (!initValueArray.empty()) {
        irinitializer = initValueArray[0];
    } else {
        irinitializer = IRinitializer;
    }
    assert(irinitializer);

    switch (vTy) {
        case IRValue::GlobalVariableVal :
            irValue = new IRGlobalVariable
                    (irinitializer->getType(), false, IRGlobalValue::InternalLinkage,
                     dynamic_cast<IRConstant *>(irinitializer),
                     this->getName(), irmodule, isinitial);
            break;

        case IRValue::InstructionVal :
            irValue = new IRAllocaInst
                    (irinitializer->getType(), nullptr, this->getName() + std::to_string(SymbolCount), parent);
            break;
    }
}

/******const的initArray必须有数据，var可以没有，因为可能是参数******/
/******constArray我添加到irmodule的globalvariablelist中去******/
void ConstArraySymbolInfo::setIRValue(IRModule *irmodule, unsigned SymbolCount, const std::string &FuncName) {

    if (!initValueArray.empty()) {
        irinitializer = new IRConstantArray(new IRArrayType(initValueArray[0]->getType(), initValueArray.size()),
                                            initValueArray);
    }
    assert(irinitializer);

    if (!FuncName.empty()) {//如果不是空串，则是函数内的constArray
        irValue = new IRGlobalVariable
                (irinitializer->getType(), true, IRGlobalValue::ExternalLinkage,
                 dynamic_cast<IRConstant *>(irinitializer),
                 this->getName() + std::to_string(SymbolCount) + "_" + FuncName, irmodule);
    } else {
        irValue = new IRGlobalVariable
                (irinitializer->getType(), true, IRGlobalValue::InternalLinkage,
                 dynamic_cast<IRConstant *>(irinitializer),
                 this->getName(), irmodule);
    }
}

/******VarArray:如果是globalVar,那么new一个globalVar就行；如果不是，那么就new一个instruction和一个globalVar，然后memcpy;******/
/******注意，如果是后者，那么new的globalVar在第一次******/
void
VarArraySymbolInfo::setIRValue(IRValue::ValueTy vTy, unsigned SymbolCount, IRBasicBlock *parent, IRValue *IRinitializer,
                               IRModule *irmodule) {

    /******两种可能性
    1.有initial，那么就可以直接从initValueArray中取;
    2.没有，那么就传进来一个已经写在funcsymbol里面的arg来作为参数init******/

    if (!initValueArray.empty()) {
        irinitializer = new IRConstantArray(new IRArrayType(initValueArray[0]->getType(), initValueArray.size()),
                                            initValueArray);
    } else {
        irinitializer = IRinitializer;
    }
    assert(irinitializer);

    // IRConstantArray(IRArrayType *ty, const std::vector<IRConstant *> &V)
    // IRArrayType(IRType *ElType, unsigned NumEl)
    switch (vTy) {
        case IRValue::GlobalVariableVal : //数组类型
            irValue = new IRGlobalVariable
                    (irinitializer->getType(), false, IRGlobalValue::InternalLinkage,
                     dynamic_cast<IRConstant *>(irinitializer),
                     this->getName(), irmodule, isinitial);
            break;

        case IRValue::InstructionVal :
            irValue = new IRAllocaInst
                    (irinitializer->getType(), irinitializer,
                     this->getName() + std::to_string(SymbolCount), parent);
            break;
    }
}


void FuncSymbolInfo::setIRValue(IRModule *irModule, IRFunction::FuncTy functy) {

    /******通过这个类自己的属性Result来构建IR需要的Result******/
    const IRType *IRResult;
    switch (returnType) {
        case VOID:
            IRResult = IRType::getPrimitiveType(IRType::VoidTyID);
            break;
        case BOOL:
            IRResult = IRType::getPrimitiveType(IRType::BoolTyID);
            break;
        case INT:
            IRResult = IRType::getPrimitiveType(IRType::IntTyID);
            break;
        case FLOAT:
            IRResult = IRType::getPrimitiveType(IRType::FloatTyID);
            break;
        case DOUBLE:
            IRResult = IRType::getPrimitiveType(IRType::DoubleTyID);
            break;
    }

    irValue = new IRFunction(new IRFunctionType(const_cast<IRType *>(IRResult), IRParams),
                             IRGlobalValue::InternalLinkage,
                             this->getName(), irModule, functy);
    /******将已经分配出的参数个数算进去******/

    /******arg与函数的双向奔赴******/
    for (auto arg: getIRArgs()) {
        arg->setParent(dynamic_cast<IRFunction *>(irValue));
        dynamic_cast<IRFunction *>(irValue)->addArgument(arg);
    }

    dynamic_cast<IRFunction *>(irValue)->setCount(IRArgs.size() + 1);
}


/***********常量变量数组符号表(init函数)***********/
ConstVarArraySymbolInfo::ConstVarArraySymbolInfo(const std::string &name, int line, DataType dataType, int global)
        : SymbolInfo(name, line), initValue(), dataType(dataType), global(global) {}

ConstSymbolInfo::ConstSymbolInfo(const std::string &name, int line, DataType dataType, int global)
        : ConstVarArraySymbolInfo(name, line, dataType, global) {}


VarSymbolInfo::VarSymbolInfo(const std::string &name, int line, DataType dataType, int global)
        : ConstVarArraySymbolInfo(name, line, dataType, global) {}


ConstArraySymbolInfo::ConstArraySymbolInfo(const std::string &name, int line, DataType dataType, int global,
                                           const std::vector<int> arraySize, int dimension)
        : ConstVarArraySymbolInfo(name, line, dataType, global), arraySize(arraySize), dimension(dimension) {}


VarArraySymbolInfo::VarArraySymbolInfo(const std::string &name, int line, DataType dataType, int global,
                                       const std::vector<int> arraySize, int dimension)
        : ConstVarArraySymbolInfo(name, line, dataType, global), arraySize(arraySize), dimension(dimension) {}


/***********FuncSymbolInfo***********/
FuncSymbolInfo::FuncSymbolInfo(const std::string &name, int line, DataType returnType)
        : SymbolInfo(name, line), returnType(returnType), baseblock(nullptr) {}

SymbolInfo *FuncSymbolInfo::addParamVar(const std::string &name, int line, DataType dataType) {
    VarSymbolInfo *newParam = new VarSymbolInfo(name, line, dataType, 0);//函数的形参必然不是全局变量
    paramList.push_back(newParam);                                       //函数形参压栈
    return newParam;
}

SymbolInfo *
FuncSymbolInfo::addParamArray(const std::string &name, int line, DataType dataType, const std::vector<int> arraySize,
                              int dimension) {
    VarArraySymbolInfo *newParam = new VarArraySymbolInfo(name, line, dataType, 0, arraySize,
                                                          dimension);//函数形参数组的全局属性和arraysize都是0
    paramList.push_back(newParam);
    return newParam;
}


/***********BlockInfo***********/

/***********BlockInfo(init函数)***********/
BlockInfo::BlockInfo(BlockInfo *parentBlock) : parentBlock(parentBlock) {
    if (parentBlock) {
        belongTo = parentBlock->belongTo;
    }
}

BlockInfo::BlockInfo(BlockInfo *parentBlock, FuncSymbolInfo *belongTo, const std::vector<SymbolInfo *> &paramList)
        : parentBlock(parentBlock), belongTo(belongTo) {
    for (SymbolInfo *one_param: paramList) {
        if (symbolTable.symbolList.count(one_param->getName()) > 0) {
            ErrorHandler::printErrorSymbol(one_param, "redefinition. Previous definition is on line " + std::to_string(
                    symbolTable.symbolList[one_param->getName()]->getline()));
            throw std::runtime_error(
                    "Syntax analysis failed at " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
        }

        //对symboltable进行操作
        symbolTable.symbolList[one_param->getName()] = one_param;
        symbolTable.stackSymbol_size += SizeOfDataType(one_param->getDataType()) *
                                        ((one_param->getArrayLength() == -1) ? 1
                                                                             : one_param->getArrayLength());//看看是否是数组，是数组那么栈要多加一些
        symbolTable.curSymbol = one_param->getName();
    }
}

/***********SymbolTable相关***********/

/***********在Block中查找符号表***********/
SymbolInfo *BlockInfo::lookUpSymbol(std::string symbolName) {
    if (symbolTable.symbolList.count(symbolName) == 1) {
        return symbolTable.symbolList[symbolName];
    } else if (parentBlock != nullptr) {
        return parentBlock->lookUpSymbol(symbolName);
    }
    return nullptr;
}//一层层往外递归查找符号
//注意这里的lookUpSymbol是不会局限于一个块的，因此后面检查duplicate的时候不能直接调用这个函数

/***********在Block中添加各种符号***********/
ConstSymbolInfo *BlockInfo::addNewConst(const std::string &name, int line, DataType dataType) {
    //symbol符号表添加
    if (symbolTable.symbolList.count(name) > 0) {//这里注意，我还会去全局的函数表里面寻找函数名，任何块内定义的变量名都不能和全局的函数名相同//不用
        ErrorHandler::printErrorMessage(
                "'" + name + "' redefinition. Previous definition is on line " +
                std::to_string(symbolTable.symbolList[name]->getline()));
        throw std::runtime_error("Syntax analysis failed at " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }
    ConstSymbolInfo *newSymbol = new ConstSymbolInfo(name, line, dataType, 0);

    //对symboltable进行操作
    symbolTable.symbolList[name] = newSymbol;
    symbolTable.stackSymbol_size += SizeOfDataType(dataType);
    symbolTable.curSymbol = name;

    return newSymbol;
}

VarSymbolInfo *BlockInfo::addNewVar(const std::string &name, int line, DataType dataType) {
    if (symbolTable.symbolList.count(name) > 0) {
        ErrorHandler::printErrorMessage(
                "'" + name + "' redefinition. Previous definition is on line " +
                std::to_string(symbolTable.symbolList[name]->getline()));
        throw std::runtime_error("Syntax analysis failed at " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }
    VarSymbolInfo *newSymbol = new VarSymbolInfo(name, line, dataType, 0);

    //对symboltable进行操作
    symbolTable.symbolList[name] = newSymbol;
    symbolTable.stackSymbol_size += SizeOfDataType(dataType);
    symbolTable.curSymbol = name;

    return newSymbol;
}

ConstArraySymbolInfo *
BlockInfo::addNewConstArray(const std::string &name, int line, DataType dataType, const std::vector<int> arraySize,
                            int dimension) {
    if (symbolTable.symbolList.count(name) > 0) {
        ErrorHandler::printErrorMessage(
                "'" + name + "' redefinition. Previous definition is on line " +
                std::to_string(symbolTable.symbolList[name]->getline()));
        throw std::runtime_error("Syntax analysis failed at " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }
    ConstArraySymbolInfo *newSymbol = new ConstArraySymbolInfo(name, line, dataType, 0, arraySize, dimension);

    //对symboltable进行操作
    symbolTable.symbolList[name] = newSymbol;
    symbolTable.stackSymbol_size += SizeOfDataType(dataType) * (newSymbol->getArrayLength());
    symbolTable.curSymbol = name;

    return newSymbol;
}

VarArraySymbolInfo *
BlockInfo::addNewVarArray(const std::string &name, int line, DataType dataType, const std::vector<int> arraySize,
                          int dimension) {
    if (symbolTable.symbolList.count(name) > 0) {
        ErrorHandler::printErrorMessage(
                "'" + name + "' redefinition. Previous definition is on line " +
                std::to_string(symbolTable.symbolList[name]->getline()));
        throw std::runtime_error("Syntax analysis failed at " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }
    VarArraySymbolInfo *newSymbol = new VarArraySymbolInfo(name, line, dataType, 0, arraySize, dimension);

    //对symboltable进行操作
    symbolTable.symbolList[name] = newSymbol;
    symbolTable.stackSymbol_size += SizeOfDataType(dataType) * (newSymbol->getArrayLength());
    symbolTable.curSymbol = name;

    return newSymbol;
}


/***********BlockTable相关***********/
//一般不会去查找block
BlockInfo *BlockInfo::addNewBlock(FuncSymbolInfo *belongTo) {
    BlockInfo *newBlock = new BlockInfo(this, belongTo, belongTo->getparamList());

    //对blocktable进行操作
    blockTable.blockList.push_back(newBlock);
    blockTable.stackBlock_size++;

    return newBlock;
}

BlockInfo *BlockInfo::addNewBlock() {
    BlockInfo *newBlock = new BlockInfo(this);

    //对blocktable进行操作
    blockTable.blockList.push_back(newBlock);
    blockTable.stackBlock_size++;

    return newBlock;
}


/***********GlobalBlock***********/

GlobalBlock::GlobalBlock()
        : BlockInfo(nullptr) {};

/***********在GlobalBlock中添加各种符号***********/
//注意这里的函数与blockInfo不是覆写的关系，因为添加常量或者变量总需要查找全局的函数表以防同名，这里直接查自己即可
ConstSymbolInfo *GlobalBlock::addNewConst(const std::string &name, int line, DataType dataType) {
    if (symbolTable.symbolList.count(name) > 0 || lookUpFunc(name) != nullptr) {//这里注意，我还会去全局的函数表里面寻找函数名，全局变量不能和全局的函数名相同
        ErrorHandler::printErrorMessage(
                "'" + name + "' redefinition. Previous definition is on line " +
                std::to_string(symbolTable.symbolList[name]->getline()));
        throw std::runtime_error("Syntax analysis failed at " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }
    ConstSymbolInfo *newSymbol = new ConstSymbolInfo(name, line, dataType, 0);

    //对symboltable进行操作
    symbolTable.symbolList[name] = newSymbol;
    symbolTable.stackSymbol_size += SizeOfDataType(dataType);
    symbolTable.curSymbol = name;

    return newSymbol;
}

VarSymbolInfo *GlobalBlock::addNewVar(const std::string &name, int line, DataType dataType) {
    if (symbolTable.symbolList.count(name) > 0) {
        ErrorHandler::printErrorMessage(
                "'" + name + "' redefinition. Previous definition is on line " +
                std::to_string(symbolTable.symbolList[name]->getline()));
        throw std::runtime_error("Syntax analysis failed at " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }
    VarSymbolInfo *newSymbol = new VarSymbolInfo(name, line, dataType, 0);

    //对symboltable进行操作
    symbolTable.symbolList[name] = newSymbol;
    symbolTable.stackSymbol_size += SizeOfDataType(dataType);
    symbolTable.curSymbol = name;

    return newSymbol;
}

ConstArraySymbolInfo *
GlobalBlock::addNewConstArray(const std::string &name, int line, DataType dataType, const std::vector<int> arraySize,
                              int dimension) {
    if (symbolTable.symbolList.count(name) > 0 || lookUpFunc(name) != nullptr) {
        ErrorHandler::printErrorMessage(
                "'" + name + "' redefinition. Previous definition is on line " +
                std::to_string(symbolTable.symbolList[name]->getline()));
        throw std::runtime_error("Syntax analysis failed at " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }
    ConstArraySymbolInfo *newSymbol = new ConstArraySymbolInfo(name, line, dataType, 0, arraySize, dimension);

    //对symboltable进行操作
    symbolTable.symbolList[name] = newSymbol;
    symbolTable.stackSymbol_size += SizeOfDataType(dataType) * (newSymbol->getArrayLength());
    symbolTable.curSymbol = name;

    return newSymbol;
}

VarArraySymbolInfo *
GlobalBlock::addNewVarArray(const std::string &name, int line, DataType dataType, const std::vector<int> arraySize,
                            int dimension) {
    if (symbolTable.symbolList.count(name) > 0 || lookUpFunc(name) != nullptr) {
        ErrorHandler::printErrorMessage(
                "'" + name + "' redefinition. Previous definition is on line " +
                std::to_string(symbolTable.symbolList[name]->getline()));
        throw std::runtime_error("Syntax analysis failed at " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }
    VarArraySymbolInfo *newSymbol = new VarArraySymbolInfo(name, line, dataType, 0, arraySize, dimension);

    //对symboltable进行操作
    symbolTable.symbolList[name] = newSymbol;
    symbolTable.stackSymbol_size += SizeOfDataType(dataType) * (newSymbol->getArrayLength());
    symbolTable.curSymbol = name;

    return newSymbol;
}


/***********FuncTable相关***********/
//由于所有的函数都是全局的，因此如果要查找函数表，必须去全局的块里面进行查询，在其他的块里面进行查询都是无效的
FuncSymbolInfo *GlobalBlock::lookUpFunc(std::string symbolName) {
    if (funcTable.funcList.count(symbolName) == 1) {
        if (funcTable.funcList[symbolName]->getSymbolType() == SymbolType::FUNC) {
            return funcTable.funcList[symbolName];
        } else {
            ErrorHandler::printErrorMessage("'" + symbolName + "' is not function");
            throw std::runtime_error(
                    "Syntax analysis failed at " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
        }
    }
    return nullptr;
}

FuncSymbolInfo *GlobalBlock::addNewFunc(const std::string &name, int line, DataType returnType) {
    //首先在global中加入函数
    if (funcTable.funcList.count(name) > 0) {
        ErrorHandler::printErrorMessage(
                "'" + name + "' redefinition. Previous definition is on line " +
                std::to_string(funcTable.funcList[name]->getline()));
        throw std::runtime_error("Syntax analysis failed at " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }
    FuncSymbolInfo *newFunc = new FuncSymbolInfo(name, line, returnType);

    //对functable进行操作
    funcTable.funcList[name] = newFunc;
    funcTable.stackFunc_size++;
    funcTable.curFunc = name;

    //然后在global中加入函数的block
    addNewBlock(newFunc);

    return newFunc;
}

void GlobalBlock::initIOFunction(IRModule *irmodule) {
    // 建立I/O函数的符号表
    // TODO: build I/O函数的IRFunction
    IRType *irType;
    IRArgument *irarg;
    this->addNewFunc("print_int", 0, DataType::VOID)
            ->addParamVar("x", 0, DataType::INT);
    irType = const_cast<IRType *>(IRType::getPrimitiveType(IRType::IntTyID));
    irarg = new IRArgument(irType, "0");
    this->lookUpFunc("print_int")->getIRArgs().push_back(irarg);
    this->lookUpFunc("print_int")->getIRParams().push_back(irType);
    this->lookUpFunc("print_int")->setIRValue(irmodule, IRFunction::UnDeclared);

    this->addNewFunc("print_float", 0, DataType::VOID)
            ->addParamVar("x", 0, DataType::FLOAT);
    irType = const_cast<IRType *>(IRType::getPrimitiveType(IRType::FloatTyID));
    irarg = new IRArgument(irType, "0");
    this->lookUpFunc("print_float")->getIRArgs().push_back(irarg);
    this->lookUpFunc("print_float")->getIRParams().push_back(irType);
    this->lookUpFunc("print_float")->setIRValue(irmodule, IRFunction::UnDeclared);

    this->addNewFunc("print_double", 0, DataType::VOID)
            ->addParamVar("x", 0, DataType::DOUBLE);
    irType = const_cast<IRType *>(IRType::getPrimitiveType(IRType::DoubleTyID));
    irarg = new IRArgument(irType, "0");
    this->lookUpFunc("print_double")->getIRArgs().push_back(irarg);
    this->lookUpFunc("print_double")->getIRParams().push_back(irType);
    this->lookUpFunc("print_double")->setIRValue(irmodule, IRFunction::UnDeclared);

    this->addNewFunc("print_bool", 0, DataType::VOID)
            ->addParamVar("x", 0, DataType::BOOL);
    irType = const_cast<IRType *>(IRType::getPrimitiveType(IRType::BoolTyID));
    irarg = new IRArgument(irType, "0");
    this->lookUpFunc("print_bool")->getIRArgs().push_back(irarg);
    this->lookUpFunc("print_bool")->getIRParams().push_back(irType);
    this->lookUpFunc("print_bool")->setIRValue(irmodule, IRFunction::UnDeclared);

    this->addNewFunc("get_int", 0, DataType::INT);
    this->lookUpFunc("get_int")->setIRValue(irmodule, IRFunction::UnDeclared);

    this->addNewFunc("get_float", 0, DataType::FLOAT);
    this->lookUpFunc("get_float")->setIRValue(irmodule, IRFunction::UnDeclared);

    this->addNewFunc("get_double", 0, DataType::DOUBLE);
    this->lookUpFunc("get_double")->setIRValue(irmodule, IRFunction::UnDeclared);

}
