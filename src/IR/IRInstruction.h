#ifndef COMPILER_IRINSTRUCTION_H
#define COMPILER_IRINSTRUCTION_H

#include <vector>

#pragma once

#include "IRUser.h"
#include "IRBasicBlock.h"
#include "utils/LiveVariable.h"
#include "utils/RegisterNode.h"
#include "utils/Register.h"

class LiveVariableInst;

class IRUser;

class RegisterNode;

class Register;

class IRInstruction : public IRUser {
private:
    IRBasicBlock *Parent;

    LiveVariableInst *Live;
    RegisterNode *regNode = nullptr;
    Register *reg;
    std::set<Register *> CallerSavedLiveRegList;
    std::set<Register *> CalleeSavedLiveRegList;

    std::set<Register *> CallerSavedINLiveRegList;
    std::set<Register *> CalleeSavedINLiveRegList;   //这两个都是INLive!!目的只是给出当前的FreeReg

protected:

    unsigned iType;// InstructionType: The opcode of the instruction
    IRInstruction(IRType *Ty, unsigned iType, const std::string &Name = "",
                  IRBasicBlock *parent = nullptr);

public:

    /**
     * clone - clone the same instruction like this, except following
     * the instruction has no name
     * the instruction has no parent
     * @return the pointer to the new instruction
     */
    virtual IRInstruction *clone() const = 0;

    inline IRBasicBlock *getParent() { return Parent; }

    void setParent(IRBasicBlock *P);

    /**
     * mayWriteToMemory - Return true if this instruction may modify memory.
     * @return bool true for this instruction may modify memory
     */
    virtual bool mayWriteToMemory() const { return false; }

    unsigned getOpcode() const { return iType; }

    virtual const char *getOpcodeName() const {
        return getOpcodeName(getOpcode());
    }

    static const char *getOpcodeName(unsigned OpCode);

    inline bool isTerminator() const {// Instance of TerminatorInst?
        return iType >= TermOpsBegin && iType < TermOpsEnd;
    }

    inline bool isBinaryOp() const {
        return iType >= BinaryOpsBegin && iType < BinaryOpsEnd;
    }

    /**
     * isAssociative - return true if the instruction is associative
     * associative is like
     *          x op (y op z) = (x op y) op z
     * @return bool
     */
    bool isAssociative() const { return isAssociative(getOpcode(), getType()); }

    static bool isAssociative(unsigned op, const IRType *Ty);

    /**
     * isCommutative - return true if the instruction is commutative
     * commutative is like
     *          x op y = y op x
     * @return
     */
    bool isCommutative() const { return isCommutative(getOpcode()); }

    static bool isCommutative(unsigned op);

    void BinaryLogicalIRInstPrint(std::ostream &OS, bool AskFloat) const;

    void SetCCIRInstPrint(std::ostream &OS) const;

    void printPrefixName(std::ostream &OS) const override;

    void print(std::ostream &OS) const override;

    LiveVariableInst *getLive() { return Live; }

    RegisterNode *getRegNode() { return regNode; };

    void setRegNode() { if (regNode == nullptr) regNode = new RegisterNode(this->getName(), this); };

    void setReg(Register *reg) {
        this->reg = reg;
    };

    Register *getReg() override { return reg; };

    void setCalleeSavedLiveReg(Register *reg) { CalleeSavedLiveRegList.insert(reg); };

    void setCallerSavedLiveReg(Register *reg) { CallerSavedLiveRegList.insert(reg); };       //对OUTLive的进行操作
    void setCalleeSavedINLiveReg(Register *reg) { CalleeSavedINLiveRegList.insert(reg); };

    void setCallerSavedINLiveReg(Register *reg) { CallerSavedINLiveRegList.insert(reg); };   //对INLive的进行操作

    const std::set<Register *> &getCallerSavedLiveRegList() { return CallerSavedLiveRegList; }; //给出OUTLIVE的活跃寄存器

    const std::set<Register *> &getCalleeSavedLiveRegList() { return CalleeSavedLiveRegList; };

    const std::set<Register *> &getCallerSavedINLiveRegList() { return CallerSavedINLiveRegList; }; //给出INLIVE的活跃寄存器

    const std::set<Register *> &getCalleeSavedINLiveRegList() { return CalleeSavedINLiveRegList; };

    const Register *getFreeGenCallerSavedReg(); //给出INLIVE的FreeReg

    const Register *getFreeFloatCallerSavedReg();

    static inline bool classof(const IRInstruction *I) { return true; }

    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::InstructionVal;
    }

    enum TermOps {// These terminate basic blocks
#define FIRST_TERM_INST(N) TermOpsBegin = N,
#define HANDLE_TERM_INST(N, OPC, CLASS) OPC = N,
#define LAST_TERM_INST(N) TermOpsEnd = N + 1,

#include "IR/Instruction.def"
    };

    enum BinaryOps {
#define FIRST_BINARY_INST(N) BinaryOpsBegin = N,
#define HANDLE_BINARY_INST(N, OPC, CLASS) OPC = N,
#define LAST_BINARY_INST(N) BinaryOpsEnd = N + 1,

#include "IR/Instruction.def"
    };

    enum MemoryOps {
#define FIRST_MEMORY_INST(N) MemoryOpsBegin = N,
#define HANDLE_MEMORY_INST(N, OPC, CLASS) OPC = N,
#define LAST_MEMORY_INST(N) MemoryOpsEnd = N + 1,

#include "IR/Instruction.def"
    };

    enum OtherOps {
#define FIRST_OTHER_INST(N) OtherOpsBegin = N,
#define HANDLE_OTHER_INST(N, OPC, CLASS) OPC = N,
#define LAST_OTHER_INST(N) OtherOpsEnd = N + 1,

#include "IR/Instruction.def"
    };
};


#endif//COMPILER_IRINSTRUCTION_H
