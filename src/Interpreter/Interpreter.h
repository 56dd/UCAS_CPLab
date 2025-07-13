//
// Created by yuanjunkang on 24-5-5.
//

#ifndef COMPILER_INTERPRETER_H
#define COMPILER_INTERPRETER_H

#include <vector>
#include <any>
#include "IR/IRModule.h"
#include "TemporaryVariable.h"

class Interpreter {
private:
    IRModule *ir;

    static int inst_cnt;

private:

    static std::map<IRValue *, TemporaryVariable *> GlobalVarMap;

    static std::vector<TemporaryVariable*> Stack;

    static TemporaryVariable* interpretFunction(IRFunction *func);

    static void initFuncArg(const std::vector<IRArgument *> &argVector, std::map<IRValue *, TemporaryVariable *> &tempVarMap);

    static void initGlobalVar(const std::vector<IRGlobalVariable *>& varVector);

    static TemporaryVariable* change_Operand_To_TemporaryVariable(IRValue* irValue, std::map<IRValue *, TemporaryVariable *> &tempVarMap);

    static TemporaryVariable* change_ConstantVal_to_TemporaryVariable(IRValue *irValue);

    static TemporaryVariable::tempVarType getTempVarType(IRType* ty);

    static std::any get_initial_value(TemporaryVariable::tempVarType type);

    static bool isBuildInFunction(const std::string& name);

    static TemporaryVariable* runBuildInFunction(const std::string& name);

    static TemporaryVariable* allocaOnStack(IRValue* irValue, TemporaryVariable::tempVarType varType);

public:
    explicit Interpreter(IRModule *ir);

    int interpret();

    static bool debugOpt;

    static int getInstCnt() ;
};


#endif //COMPILER_INTERPRETER_H
