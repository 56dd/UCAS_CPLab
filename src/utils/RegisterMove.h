#ifndef COMPILER_REGISTERMOVE_H
#define COMPILER_REGISTERMOVE_H

class IRMoveInst;
class RegisterNode;
class Register;
class IRArgument;

class RegisterMove{
private:
    RegisterNode* srcNode;
    RegisterNode* dstNode;

public:
    explicit RegisterMove(IRMoveInst* moveinst);
    explicit RegisterMove(IRArgument* funcarg, Register* reg);

    RegisterNode* getSrcNode() { return srcNode; }
    RegisterNode* getDstNode() { return dstNode; }
};

#endif //COMPILER_REGISTERMOVE_H