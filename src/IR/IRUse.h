#ifndef COMPILER_IRUSE_H
#define COMPILER_IRUSE_H

class IRValue;
class IRUser;

class IRUse {
    IRValue *val;
    IRUser *user;

public:
    IRUse(IRValue *v, IRUser *user);
    IRUse(const IRUse &u);
    ~IRUse();

    operator IRValue *() const { return val; }
    IRValue *get() const { return val; }
    IRUser *getUser() const { return user; }

    void set(IRValue *Val);

    IRValue *operator=(IRValue *RHS) {
        set(RHS);
        return RHS;
    }

    const IRUse &operator=(const IRUse &RHS) {
        set(RHS.val);
        return *this;
    }
};

#endif//COMPILER_IRUSE_H
