#ifndef COMPILER_IRDERIVEDTYPES_H
#define COMPILER_IRDERIVEDTYPES_H

#include "IRType.h"


class IRFunctionType : public IRType {
private:
    IRType *resultType;
    std::vector<IRType *> paramTys;

public:
    IRFunctionType(IRType *Result, const std::vector<IRType *> &Params);

    inline IRType *getReturnType() const { return resultType; }

    inline const std::vector<IRType *> &getParamTypes() const { return paramTys; }

    IRType *getParamType(unsigned i) const { return paramTys[i]; }

    unsigned getNumParams() const { return paramTys.size(); }
};


class IRSequentialType : public IRType {
protected:
    IRType *elementType;

    IRSequentialType(PrimitiveID TID, IRType *ElType)
            : IRType("", TID) {
        elementType = ElType;
    }

public:
    inline IRType *getElementType() const { return elementType; }

    virtual const IRType *getTypeAtIndex(const IRValue *V) const {
        return elementType;
    }

    virtual bool indexValid(const IRValue *V) const {
        return V->getType() == IRType::IntTy;// Must be a 'int' index
    }

    virtual const IRType *getIndexType() const { return IRType::IntTy; }

    void IRpointerPrintAlign(std::ostream &OS);
};

class IRArrayType : public IRSequentialType {
private:
    unsigned NumElements;

public:
    IRArrayType(IRType *ElType, unsigned NumEl);

    inline unsigned getNumElements() const { return NumElements; }

    static bool classof(IRArrayType *t) { return true; }

    static bool classof(IRType *t) {
        return t->getPrimitiveID() == ArrayTyID;
    }
};

class IRPointerType : public IRSequentialType {
public:
    explicit IRPointerType(IRType *ElType);

    IRType *getArrayEleType() const { return dynamic_cast<IRArrayType *>(getElementType())->getElementType(); };

    static bool classof(IRPointerType *t) { return true; }

    static bool classof(IRType *t) {
        return t->getPrimitiveID() == PointerTyID;
    }
};

#endif//COMPILER_IRDERIVEDTYPES_H
