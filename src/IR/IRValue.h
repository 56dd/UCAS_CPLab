#ifndef COMPILER_IRVALUE_H
#define COMPILER_IRVALUE_H

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "IRUse.h"

class IRType;

class IRConstant;

class IRArgument;

class IRInstruction;

class IRBasicBlock;

class IRGlobalValue;

class IRFunction;

class IRGlobalVariable;

class TemporaryVariable;

class Register;

class IRValue {
public:
    enum ValueTy {
        TypeVal,          // This is an instance of Type            //不需要有printPrefix
        ConstantVal,      // This is an instance of Constant        //不需要有printPrefix
        ArgumentVal,      // This is an instance of Argument        //需要有printPrefix,%
        InstructionVal,   // This is an instance of Instruction     //需要有printPrefix,%
        BasicBlockVal,    // This is an instance of BasicBlock      //需要有printPrefix,%
        FunctionVal,      // This is an instance of Function        //需要有printPrefix,@
        GlobalVariableVal,// This is an instance of GlobalVariable  //需要有printPrefix,@
    };

private:
    std::vector<IRUse *> Uses;
    std::string name;
    IRType *ty;
    ValueTy vTy;
    TemporaryVariable *tempVar;

public:
    //void operator=(const IRValue &) = delete;
    //IRValue(const IRValue &) = delete;
    IRValue(IRType *Ty, ValueTy vty, std::string name = "");

    virtual ~IRValue() = default;

    /******printPrefixName虚函数******/
    virtual void printPrefixName(std::ostream &OS) const {};

    virtual void print(std::ostream &OS) const = 0;

    /******了解IRvalue的type指针******/
    IRType *getType() const { return ty; }

    inline bool hasName() const { return name != ""; }

    inline const std::string &getName() const { return name; }

    void setName(std::string Name) { name = std::move(Name); }

    /******知道这个IRvalue是哪一个子类******/
    inline ValueTy getValueType() const { return vTy; }

    void replaceAllUsesWith(IRValue *V);

    /******对IRValue的Uses进行操作******/
    /**
     * add Use in Uses. It should only be used by the Use class
     * @param U
     */
    void addUse(IRUse &U) {
        Uses.push_back(&U);
    }

    /**
     * delete all Use* in Uses which equals &U. It should only be used by ths Use class
     * @param U
     */
    void killUse(IRUse &U) {
        auto ptr = std::find(Uses.begin(), Uses.end(), &U);
        Uses.erase(ptr);
    }

    std::vector<IRUse *> getUses() const {
        return Uses;
    }

    void setTempVar(TemporaryVariable *tempVar);

    TemporaryVariable *getTempVar();

    virtual Register* getReg() { return nullptr; }
};

#endif//COMPILER_IRVALUE_H
