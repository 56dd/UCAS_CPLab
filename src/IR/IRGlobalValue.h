#ifndef COMPILER_IRGLOBALVALUE_H
#define COMPILER_IRGLOBALVALUE_H


#include "IRUser.h"
class IRPointerType;
class IRModule;

class IRGlobalValue : public IRUser {
public:
    enum LinkageTypes {
        ExternalLinkage, // Externally visible function
        LinkOnceLinkage, // Keep one copy of named function when linking (inline)
        WeakLinkage,     // Keep one copy of named function when linking (weak)
        AppendingLinkage,// Special purpose, only applies to global arrays
        InternalLinkage  // Rename collisions when linking (static functions)
    };

protected:
    IRGlobalValue(IRType *Ty, ValueTy vty, LinkageTypes linkage,
                  const std::string &name = "")
        : IRUser(Ty, vty, name), Linkage(linkage), Parent(nullptr) {}
    LinkageTypes Linkage;
    IRModule *Parent;

public:
    ~IRGlobalValue() = default;

    /******注意这里的强制转换类型，对于IRGlobalValue，全部将type类型强制转换为pointertype******/
    inline IRPointerType *getType() const {
        return (IRPointerType *) IRUser::getType();
    }
    /******提供一个不强制转换类型的函数******/
    inline IRType *getOriginType() const {
        return IRUser::getType();
    }

    /******linkage的作用目前尚不明确******/
    bool hasExternalLinkage() const { return Linkage == ExternalLinkage; }
    bool hasLinkOnceLinkage() const { return Linkage == LinkOnceLinkage; }
    bool hasWeakLinkage() const { return Linkage == WeakLinkage; }
    bool hasAppendingLinkage() const { return Linkage == AppendingLinkage; }
    bool hasInternalLinkage() const { return Linkage == InternalLinkage; }
    void setLinkage(LinkageTypes LT) { Linkage = LT; }
    LinkageTypes getLinkage() const { return Linkage; }

    /******获得最大块******/
    inline IRModule *getParent() { return Parent; }

    /******classof判断******/
    static inline bool classof(const IRGlobalValue *T) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::FunctionVal ||
               V->getValueType() == IRValue::GlobalVariableVal;
    }
};


#endif//COMPILER_IRGLOBALVALUE_H
