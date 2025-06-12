#include "IRValue.h"

#include <utility>

#include "IRUse.h"


IRValue::IRValue(IRType *Ty, IRValue::ValueTy vty, std::string name) : name(std::move(name)) {
    ty = Ty;
    vTy = vty;
    tempVar = nullptr;
}

void IRValue::replaceAllUsesWith(IRValue *V) {
    while (!Uses.empty()) {
        IRUse *U = Uses.back();
        U->set(V);
    }
}

void IRValue::setTempVar(TemporaryVariable *tempVar) {
    IRValue::tempVar = tempVar;
}

TemporaryVariable *IRValue::getTempVar(){
    return tempVar;
}

IRUse::IRUse(IRValue *v, IRUser *user) : val(v), user(user) {
    if (val)
        val->addUse(*this);
}

IRUse::IRUse(const IRUse &u) : val(u.val), user(u.user) {
    if (val)
        val->addUse(*this);
}

IRUse::~IRUse() {
    if (val)
        val->killUse(*this);
}

void IRUse::set(IRValue *Val) {
    if (val)
        val->killUse(*this);
    val = Val;
    if (Val)
        Val->addUse(*this);
}
