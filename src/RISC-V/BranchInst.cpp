#include "BranchInst.h"
#include "IR/IRType.h"
#include "Value.h"

namespace RISCV {
    BranchInst::BranchInst(unsigned int iType, BasicBlock *dest, Value *op1, Value *op2, BasicBlock *parent)
            : Instruction(IRType::VoidTy, iType, parent) {
        Operands.push_back(op1);
        if (op2) {
            Operands.push_back(op2);
        }
        Operands.push_back(new Value(dest));
    }

    void BranchInst::print(std::ostream &O) const {
        switch (iType) {
            case Beq:
                O << "beq ";
                break;
            case Beqz:
                O << "beqz ";
                break;
            case Bge:
                O << "bge ";
                break;
            case Bgez:
                O << "bgez ";
                break;
            case Bgt:
                O << "bgt ";
                break;
            case Bgtz:
                O << "bgtz ";
                break;
            case Ble:
                O << "ble ";
                break;
            case Blez:
                O << "blez ";
                break;
            case Blt:
                O << "blt ";
                break;
            case Bltz:
                O << "bltz ";
                break;
            case Bne:
                O << "bne ";
                break;
            case Bnez:
                O << "bnez ";
                break;
            default:
                assert(0 && "Unknown iType");
        }
        switch (iType) {
            case Beq:
            case Bge:
            case Bgt:
            case Ble:
            case Bne:
            case Blt:
                Operands[0]->print(O);
                O << ", ";
                Operands[1]->print(O);
                O << ", ";
                Operands[2]->print(O);
                break;
            case Beqz:
            case Bgez:
            case Bgtz:
            case Blez:
            case Bltz:
            case Bnez:
                Operands[0]->print(O);
                O << ", ";
                Operands[1]->print(O);
                break;
            default:
                assert(0 && "Unknown iType");
        }
        O << std::endl;
    }
} // RISCV