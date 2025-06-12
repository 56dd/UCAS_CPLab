#include "GlobalSubExpPass.h"
#include "IR/IRFunction.h"
#include "IR/IRInstruction.h"
#include "IR/IRType.h"
#include "IR/IRValue.h"
#include "Pass/Pass.h"
#include "utils/DominatorTree.h"

#include <algorithm>
#include <bitset>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::vector<IRInstruction *> irdomiinstArray;
std::vector<IRInstruction *> irloadstoreArray;
bool global_optflag;

/*我认为这两个函数是解耦的：一个负责消除除了ldst之外其他的公共子表达式，另一个负责在此基础上进行ld
 * st指令的尽可能消除
 */
void childrenldst(IRBasicBlock &BB, ControlFlowGraph *cfg) {

    /*对于子块中的每一条load
     * store指令，如果操作数之前从没有出现过，那么就必然要放进去
     */
    for (unsigned i = 0; i < BB.getInstList().size();) {
        IRInstruction *childinst = BB.getInstList()[i];

        if ((childinst->getOpcode() == IRInstruction::Store) ||
            (childinst->getOpcode() == IRInstruction::Load)) {
            bool flag = false;

            for (unsigned j = 0; j < irloadstoreArray.size(); j++) {
                IRInstruction *parentinst = irloadstoreArray[j];

                /*这里专门进行loadstore指令相关的消除*/
                if ((childinst->getOpcode() == IRInstruction::Store) &&
                    (parentinst->getOpcode() == IRInstruction::Load) &&
                    (parentinst->getOperand(0) == childinst->getOperand(1))) {

                    /*Array中ld指令到st指令的更新*/
                    auto irldstcancelinst = std::find(irloadstoreArray.begin(),
                                                      irloadstoreArray.end(), parentinst);
                    auto irldstinsert = irloadstoreArray.erase(irldstcancelinst);
                    irloadstoreArray.insert(irldstinsert, childinst);

                    flag = true;
                    i++;
                    break;
                } else if ((childinst->getOpcode() == IRInstruction::Load) &&
                           (parentinst->getOpcode() == IRInstruction::Store) &&
                           (parentinst->getOperand(1) == childinst->getOperand(0))) {

                    /*Array中st指令到ld指令的更新*/
                    auto irldstcancelinst = std::find(irloadstoreArray.begin(),
                                                      irloadstoreArray.end(), parentinst);
                    auto irldstinsert = irloadstoreArray.erase(irldstcancelinst);
                    irloadstoreArray.insert(irldstinsert, childinst);

                    flag = true;
                    i++;
                    break;
                } else if ((childinst->getOpcode() == IRInstruction::Load) &&
                           (parentinst->getOpcode() == IRInstruction::Load) &&
                           (parentinst->getOperand(0) == childinst->getOperand(0))) {

                    /*childBB中childinst的删除，同时用array中的指令替代所有需要子指令*/
                    auto ircancelinst = std::find(BB.getInstList().begin(),
                                                  BB.getInstList().end(), childinst);
                    childinst->dropAllReferences();
                    BB.getInstList().erase(ircancelinst);
                    childinst->replaceAllUsesWith(parentinst);

                    flag = true;
                    global_optflag = true;
                    break;
                } else if ((childinst->getOpcode() == IRInstruction::Store) &&
                           (parentinst->getOpcode() == IRInstruction::Store) &&
                           (parentinst->getOperand(1) == childinst->getOperand(1))) {
                    /*Array中st指令到st指令的更新*/
                    auto irldstcancelinst = std::find(irloadstoreArray.begin(),
                                                      irloadstoreArray.end(), parentinst);
                    auto irldstinsert = irloadstoreArray.erase(irldstcancelinst);
                    irloadstoreArray.insert(irldstinsert, childinst);

                    /*？
                     *这里的store指令其实是可以考虑子指令替换父指令的，需要进行这个操作吗？
                     */
                    flag = true;
                    i++;
                    break;
                }
            }

            /*
             * 如果flag为true，证明之前loadstoreArray里就有，并且已经顶替过
             * 如果为false，证明没有顶替，且需要重新压入
             */
            if (!flag) {
                irloadstoreArray.push_back(childinst);
                i++;
            }
        } else {
            i++;
        }
    }

    for (auto domi: BB.getDominatorTree(cfg)->children) {
        auto childBB = domi->basicBlock;

        /*继续往下消*/
        childrenldst(*childBB, cfg);
    }

    /*
     * 在回溯过程中，将load指令全部消除
     * 不消store指令的原因：store指令虽然不支配后面的节点，但是仍可能会通过某条路径产生影响，因此不消除
     * 消除load的原因：load可能是因为一条可能的路径而产生的load，并不能保证都在后面的load之前执行(后面的load可能仍需要进行操作)，因此需要消除
     */
    for (unsigned k = 0; k < BB.getInstList().size(); k++) {
        for (unsigned t = 0; t < irloadstoreArray.size();) {
            if (BB.getInstList()[k] == irloadstoreArray[t] &&
                BB.getInstList()[k]->getOpcode() == IRInstruction::Load) {
                auto ircancelinst =
                        std::find(irloadstoreArray.begin(), irloadstoreArray.end(),
                                  irloadstoreArray[t]);
                irloadstoreArray.erase(ircancelinst);
            } else {
                t++;
            }
        }
    }
}

void childrenSubExp(IRBasicBlock &BB, ControlFlowGraph *cfg) {

    /*用到当前支配路径上的所有可用的指令变量*/
    for (unsigned j = 0; j < irdomiinstArray.size(); j++) {
        for (unsigned i = 0; i < BB.getInstList().size();) {
            IRInstruction *childinst = BB.getInstList()[i];
            IRInstruction *parentinst = irdomiinstArray[j];

            bool flag = false;
            /*满足两者操作类型相同，并且以下几种指令是不可以消除局部公共子表达式的*/
            if ((childinst->getOpcode() == parentinst->getOpcode()) &&
                (childinst->getOpcode() != IRInstruction::Br) &&
                (childinst->getOpcode() != IRInstruction::PHI) &&
                (childinst->getOpcode() != IRInstruction::Load) &&
                (childinst->getOpcode() != IRInstruction::Store) &&
                (childinst->getOpcode() != IRInstruction::Memcpy) &&
                (childinst->getOpcode() != IRInstruction::Call)) {
                /*如果是可交换的，则两方都需要进行考虑*/
                if (childinst->isCommutative()) {
                    if ((childinst->getOperand(0) == parentinst->getOperand(0) &&
                         childinst->getOperand(1) == parentinst->getOperand(1)) ||
                        (childinst->getOperand(0) == parentinst->getOperand(1) &&
                         childinst->getOperand(1) == parentinst->getOperand(0))) {
                        flag = true;
                        global_optflag = true;
                    }
                } else {
                    /*如果opcode是比较并且是两个整型之间的比较，则不能进行删除*/
                    if((childinst->getOpcode() >= IRInstruction::SetEQ &&
                        childinst->getOpcode() <= IRInstruction::SetGT)&&
                        childinst->getOperand(0)->getType()->getPrimitiveID() == IRType::IntTyID ){
                            flag = false;
                        }else{
                        /*按顺序进行检验*/
                        for (unsigned k = 0; k < childinst->getNumOperands(); k++) {
                            if (childinst->getOperand(k) == parentinst->getOperand(k)) {
                                flag = true;
                            } else {
                                flag = false;
                                break;
                            }
                        }
                    }
                }
            }

            if (flag) { // erase完毕后下一条指令自动上前
                global_optflag = true;
                auto ircancelinst = std::find(BB.getInstList().begin(),
                                              BB.getInstList().end(), childinst);
                childinst->dropAllReferences();
                BB.getInstList().erase(ircancelinst);
                childinst->replaceAllUsesWith(parentinst);
            } else {
                i++;
            }
        }
    }
    /*支配路径上的所有指令连同当前块的所有指令放到irchildinstarray里，然后继续沿着支配路径往下走*/
    for (auto inst: BB.getInstList()) {
        irdomiinstArray.push_back(inst);
    }


    for (auto domi: BB.getDominatorTree(cfg)->children) {
        auto childBB = domi->basicBlock;
        childrenSubExp(*childBB, cfg);
    }


    for (unsigned k = 0; k < BB.getInstList().size(); k++) {
        irdomiinstArray.pop_back();
    }
}

void GlobalSubExpPass::runOnFunction(IRFunction &F) {
    ControlFlowGraph cfg(&F);
    DominatorTree::getDominatorTree(&cfg);
    auto rootBB = F.getEntryBlock();
    
    //判断当前优化迭代后是否还有可优化的空间
    global_optflag = true;
    while(global_optflag){
        global_optflag = false;
        /*多跑几次进行迭代*/
        childrenSubExp(*rootBB, &cfg);
        childrenldst(*rootBB, &cfg);
    }

    irdomiinstArray.clear();
    irloadstoreArray.clear();
}

GlobalSubExpPass::GlobalSubExpPass(std::string name, int level) : FunctionPass(name, level) {}
