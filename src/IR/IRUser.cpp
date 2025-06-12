#include "IRUser.h"

IRUser::IRUser(IRType *Ty, IRValue::ValueTy vty, const std::string &name)
        : IRValue(Ty, vty, name) {
}

void IRUser::replaceUsesOfWith(IRValue *From, IRValue *To) {
    if (From == To)
        return;     // for what?
    for (int i = 0, E = getNumOperands(); i < E; ++i) {
        if (getOperand(i) == From) {
            setOperand(i, To);
        }
    }
}
