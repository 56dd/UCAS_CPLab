#include "MemToRegPass.h"
#include "IR/iMemory.h"
#include "utils/DominatorTree.h"
#include "IR/iTerminators.h"
#include "IR/iPHINdoe.h"
#include "IR/IRConstant.h"
#include "utils/ControlFlowGraph.h"

#include <utility>
#include <map>
#include <stack>

class DominatorTree;

MemToRegPass::MemToRegPass(std::string name, int level) : FunctionPass(std::move(name), level) {

}

void MemToRegPass::runOnFunction(IRFunction &F) {
    std::vector<IRAllocaInst *> Allocs;
    ControlFlowGraph cfg(&F);
    DominatorTree *root = DominatorTree::getDominatorTree(&cfg);
    auto entryBB = F.getEntryBlock();
    while (true) {
        Allocs.clear();
        auto instList = entryBB->getInstList();
        for (auto inst: instList) {
            if (auto AI = dynamic_cast<IRAllocaInst *>(inst)) {
                if (isAllocaPromotable(AI)) {
                    Allocs.push_back(AI);
                }
            }
        }
        if (Allocs.empty())
            break;
        mem2reg(Allocs, root, F.getBasicBlockList(), &cfg);
    }
}

bool MemToRegPass::isAllocaPromotable(IRAllocaInst *AI) {
    return AI->getAllocatedType()->isPrimitiveType() ||
           AI->getAllocatedType()->getPrimitiveID() == IRType::PointerTyID &&
           dynamic_cast<IRPointerType *>(const_cast<IRType *>(AI->getAllocatedType()))->getElementType()->isPrimitiveType();
}

void
MemToRegPass::mem2reg(std::vector<IRAllocaInst *> Allocs, DominatorTree *root, std::vector<IRBasicBlock *> &BBList,
                      ControlFlowGraph *cfg) {
    std::set<DominatorTree *> defineNode;
    std::set<DominatorTree *> userNode;
    /*!
     * 首先遍历每个块：
     * 1. 将不会跨基本块传值的store删去。
     * 2. 将使用本块中store值的load删去。
     */
    for (auto BB: BBList) {
        auto &instList = BB->getInstList();
        std::vector<IRInstruction *> bin;
        bin.clear();
        std::map<IRValue *, IRStoreInst *> lastStore;
        lastStore.clear();
        for (auto inst: instList) {
            if (auto loadInst = dynamic_cast<IRLoadInst *>(inst)) {
                //! 对于变量的load其pointer一定是allca指令
                if (!dynamic_cast<IRAllocaInst *>(loadInst->getPointerOperand())) continue;

                if (auto lastStoreInst = lastStore[loadInst->getPointerOperand()]) {
                    loadInst->replaceAllUsesWith(lastStoreInst->getOperand(0));
                    bin.push_back(dynamic_cast<IRInstruction *>(loadInst));
                }
            } else if (auto storeInst = dynamic_cast<IRStoreInst *>(inst)) {
                //! 对于变量的store其pointer一定是allca指令
                if (!dynamic_cast<IRAllocaInst *>(storeInst->getPointerOperand())) continue;

                if (auto lasInst = lastStore[storeInst->getPointerOperand()]) {
                    bin.push_back(dynamic_cast<IRInstruction *>(lasInst));
                }
                lastStore[storeInst->getPointerOperand()] = storeInst;
            }
        }
        for (auto trash: bin) {
            trash->dropAllReferences();
            instList.erase(std::find(instList.begin(), instList.end(), trash));
        }
    }
    /*!
     * 开始对每个变量开始优化
     */
    for (auto alloc: Allocs) {
        /*!
         * 计算 defineBLock 和 userBlock 还有 orig
         */
        defineNode.clear();
        userNode.clear();
        auto userList = dynamic_cast<IRValue *>(alloc)->getUses();
        for (auto use: userList) {
            auto useInst = dynamic_cast<IRInstruction *>(use->getUser());
            auto block = useInst->getParent();
            if (IRLoadInst::classof(useInst)) {
                userNode.insert(block->getDominatorTree(cfg));
            } else if (IRStoreInst::classof(useInst)) {
                defineNode.insert(block->getDominatorTree(cfg));
                block->getDominatorTree(cfg)->orig.insert(alloc);
            } else {
                assert(0 && "wtf");
            }
        }

        /*!
         * 特例：对于只赋值一次的变量进行优化
         */
        std::vector<IRInstruction *> bin;
        bin.clear();
        if (defineNode.size() == 1) {
            IRValue *replaceValue = nullptr;
            for (auto use: userList) {
                auto useInst = dynamic_cast<IRInstruction *>(use->getUser());
                if (IRStoreInst::classof(useInst)) {
                    replaceValue = dynamic_cast<IRStoreInst *>(useInst)->getOperand(0);
                    bin.push_back(useInst);
                    break;
                }
            }
            for (auto use: userList) {
                auto useInst = dynamic_cast<IRInstruction *>(use->getUser());
                if (IRLoadInst::classof(useInst)) {
                    useInst->replaceAllUsesWith(replaceValue);
                    bin.push_back(useInst);
                }
            }
        } else {
            /*!
             * 对于其他，按正常ssa转换方法进行优化，插入phi节点
             */
            std::set<DominatorTree *> workList;
            workList = defineNode;
            while (!workList.empty()) {
                auto node = *workList.begin();
                workList.erase(workList.begin());
                for (auto DFNode: node->DF) {
                    if (DFNode->phi.find(alloc) == DFNode->phi.end()) {
                        DFNode->phi.insert(alloc);
                        auto phi = new IRPHINode(const_cast<IRType *>(alloc->getAllocatedType()), alloc);
                        DFNode->basicBlock->addInstructionToFront(dynamic_cast<IRInstruction *>(phi));
                        if (DFNode->orig.find(alloc) == DFNode->orig.end()) {
                            workList.insert(DFNode);
                        }
                    }
                }
            }
            /*!
             * 重命名轮，删除load和store，填入phi
             */
            std::stack<IRValue *> valueStack;
            while (!valueStack.empty()) valueStack.pop();
            valueStack.push(dynamic_cast<IRValue *>(IRConstant::getNullValue(alloc->getAllocatedType())));
            renamePass(root, alloc, &bin, &valueStack);
        }
        for (auto trash: bin) {
            auto &list = trash->getParent()->getInstList();
            trash->dropAllReferences();
            list.erase(std::find(list.begin(), list.end(), trash));
        }
        auto &list = alloc->getParent()->getInstList();
        dynamic_cast<IRInstruction *>(alloc)->dropAllReferences();
        list.erase(std::find(list.begin(), list.end(), alloc));
    }

}

void MemToRegPass::renamePass(DominatorTree *node, IRAllocaInst *alloc, std::vector<IRInstruction *> *bin,
                              std::stack<IRValue *> *valueStack) {
    int cnt = 0;
    auto &instList = node->basicBlock->getInstList();
    for (auto inst: instList) {
        if (IRLoadInst::classof(inst)) {
            if (dynamic_cast<IRLoadInst *>(inst)->getPointerOperand() == dynamic_cast<IRValue *>(alloc)) {
                inst->replaceAllUsesWith(valueStack->top());
                bin->push_back(inst);
            }
        } else if (IRStoreInst::classof(inst)) {
            if (dynamic_cast<IRStoreInst *>(inst)->getPointerOperand() == dynamic_cast<IRValue *>(alloc)) {
                ++cnt;
                valueStack->push(inst->getOperand(0));
                bin->push_back(inst);
            }
        } else if (IRPHINode::classof(inst)) {
            if (dynamic_cast<IRPHINode *>(inst)->getVar() == alloc) {
                ++cnt;
                valueStack->push(dynamic_cast<IRValue *>(inst));
            }
        }
    }
    auto terminator = node->basicBlock->getTerminator();
    unsigned numSuccessors = terminator->getNumSuccessors();
    for (int i = 0; i < numSuccessors; ++i) {
        auto BB = terminator->getSuccessor(i);
        auto &instList = BB->getInstList();
        IRPHINode *phi = nullptr;
        for (auto inst: instList) {
            if (IRPHINode::classof(inst) && dynamic_cast<IRPHINode *>(inst)->getVar() == alloc) {
                phi = dynamic_cast<IRPHINode *>(inst);
                break;
            }
            if (!IRPHINode::classof(inst))
                break;
        }
        if (phi) {
            phi->addIncoming(valueStack->top(), node->basicBlock);
        }
    }
    for (auto child: node->children) {
        renamePass(child, alloc, bin, valueStack);
    }
    for (int i = 0; i < cnt; ++i) {
        valueStack->pop();
    }
}
