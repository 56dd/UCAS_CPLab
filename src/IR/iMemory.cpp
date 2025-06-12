#include "iMemory.h"

#include "IRConstant.h"
#include "IRDerivedTypes.h"

IRAllocationInst::IRAllocationInst(IRType *Ty, IRValue *ArraySize, unsigned int iTy, const std::string &Name,
                                   IRBasicBlock *parent)
        : IRInstruction(new IRPointerType(Ty), iTy, Name, parent) {
    if (!ArraySize) ArraySize = IRConstantInt::get(1);
    Operands.reserve(1);
    Operands.emplace_back(ArraySize, this);
}

bool IRAllocationInst::isArrayAllocation() const {
    return dynamic_cast<IRConstantInt *>(getOperand(0))->getRawValue() != 1;
}

const IRType *IRAllocationInst::getAllocatedType() const {
    return getType()->getElementType();
}


IRLoadInst::IRLoadInst(IRValue *Ptr, const std::string &Name, IRBasicBlock *parent)
        : IRInstruction(dynamic_cast<IRSequentialType *>(Ptr->getType())->getElementType(),
                        Load, Name, parent),
          Volatile(false) {
    Operands.reserve(1);
    Operands.emplace_back(Ptr, this);
}

IRLoadInst::IRLoadInst(IRValue *Ptr, const std::string &Name, bool isVolatile, IRBasicBlock *parent)
        : IRInstruction(dynamic_cast<IRSequentialType *>(Ptr->getType())->getElementType(),
                        Load, Name, parent),
          Volatile(isVolatile) {
    Operands.reserve(1);
    Operands.emplace_back(Ptr, this);
}

IRStoreInst::IRStoreInst(IRValue *Val, IRValue *Ptr, IRBasicBlock *parent)
        : IRInstruction(IRType::VoidTy, Store, "", parent), Volatile(false) {
    Operands.reserve(2);
    Operands.emplace_back(Val, this);
    Operands.emplace_back(Ptr, this);
}

IRStoreInst::IRStoreInst(IRValue *Val, IRValue *Ptr, bool isVolatile, IRBasicBlock *parent)
        : IRInstruction(IRType::VoidTy, Store, "", parent), Volatile(isVolatile) {
    Operands.reserve(2);
    Operands.emplace_back(Val, this);
    Operands.emplace_back(Ptr, this);
}

IRMemcpyInst::IRMemcpyInst(IRValue *DestPtr, IRValue *SrcPtr, IRBasicBlock *InsertBefore)
        : IRInstruction(IRType::VoidTy, Memcpy, "", InsertBefore), Volatile(false) {
    Operands.reserve(2);
    Operands.emplace_back(DestPtr, this);
    Operands.emplace_back(SrcPtr, this);
}

IRMemcpyInst::IRMemcpyInst(IRValue *DestPtr, IRValue *SrcPtr, bool isVolatile, IRBasicBlock *parent)
        : IRInstruction(IRType::VoidTy, Memcpy, "", parent), Volatile(isVolatile) {
    Operands.reserve(2);
    Operands.emplace_back(DestPtr, this);
    Operands.emplace_back(SrcPtr, this);
}
