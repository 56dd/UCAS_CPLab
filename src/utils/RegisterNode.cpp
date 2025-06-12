#include "RegisterNode.h"
#include "IR/IRArgument.h"
#include "IR/IRInstruction.h"
#include "IR/IRType.h"
#include "IR/IRValue.h"
#include "IR/iOther.h"
#include "utils/DominatorTree.h"
#include "utils/LiveVariable.h"
#include "utils/Register.h"
#include "IR/IRConstant.h"
#include "utils/RegisterMove.h"
#include <algorithm>
#include <cstddef>
#include <vector>
#include <tuple>

unsigned RegisterNode::regNum = 0;
RegisterNode::WHICH RegisterNode::which = RegisterNode::GENERAL;
IRFunction* RegisterNode::curF = nullptr;

std::list<RegisterNode*> RegisterNode::precolored {};
std::set<RegisterNode*> RegisterNode::initial {};
std::list<RegisterNode*> RegisterNode::simplifyWorklist {};
std::list<RegisterNode*> RegisterNode::freezeWorklist {};
std::list<RegisterNode*> RegisterNode::spillWorklist {};
std::list<RegisterNode*> RegisterNode::spilledNodes {};
std::list<RegisterNode*> RegisterNode::coalescedNodes {};
std::list<RegisterNode*> RegisterNode::coloredNodes {};
std::list<RegisterNode*> RegisterNode::selectStack {};

std::vector<RegisterMove*> RegisterNode::coalescedMoves {};    
std::vector<RegisterMove*> RegisterNode::constrainedMoves {};   
std::vector<RegisterMove*> RegisterNode::frozenMoves {};        
std::vector<RegisterMove*> RegisterNode::worklistMoves {};
std::vector<RegisterMove*> RegisterNode::activeMoves {};                  

std::vector<std::tuple<RegisterNode*, RegisterNode*>> RegisterNode::adjSet {};
std::map<RegisterNode*, unsigned> RegisterNode::degree {};
std::map<RegisterNode*, RegisterNode*> RegisterNode::alias {};    

std::vector<RegisterNode*> RegisterNode::Adjcent(RegisterNode* node){
    std::vector<RegisterNode*> adjcent;

    for(auto adjnode: node->adjList){
        /*如果两处都没有找到，说明既没有被简化入栈也没有被合并，即还在图中，因此它是node当前还有效的邻接结点*/
        if(std::find(selectStack.begin(), selectStack.end(), adjnode) == selectStack.end() &&
           std::find(coalescedNodes.begin(), coalescedNodes.end(), adjnode) == coalescedNodes.end()){
            adjcent.push_back(adjnode);
           }
    }
    return adjcent;
}


/*与这个结点相关的还没有合并的传送指令*/
std::vector<RegisterMove*> RegisterNode::NodeMoves(RegisterNode* node){
    std::vector<RegisterMove*> NodeMoves;
    /*adjList[n]\(selectStack U coalescedNodes)*/
    for(auto irmove: node->moveList){ 
        if(std::find(activeMoves.begin(), activeMoves.end(), irmove) != activeMoves.end() ||
           std::find(worklistMoves.begin(), worklistMoves.end(), irmove) != worklistMoves.end()){
                NodeMoves.push_back(irmove);
           }
    }
    return NodeMoves;
}

bool RegisterNode::MoveRelated(RegisterNode* node){
    if(!NodeMoves(node).empty()) return true;
    else return false;
};

void RegisterNode::init(){
    if(which == GENERAL){ regNum = GPRNUM; }
    else if(which == FLOAT){ regNum = FPRNUM; }

    /*机器寄存器冲突图*/
    switch(which){
        case GENERAL:
            for(auto reg1: RegisterFactory::getGRegList()){
                precolored.push_back(reg1->getRegNode());
                for(auto reg2: RegisterFactory::getGRegList()){
                    RegisterNode::AddEdge(reg1->getRegNode(), reg2->getRegNode());
                }
            }
            break;
        case FLOAT:
            for(auto reg1: RegisterFactory::getFRegList()){
                precolored.push_back(reg1->getRegNode());
                for(auto reg2: RegisterFactory::getFRegList()){
                    RegisterNode::AddEdge(reg1->getRegNode(), reg2->getRegNode());
                }
            }
            break;
    }

    /*参数机器寄存器move指令*/
    unsigned argcnt = 0;
    switch(which){
        case GENERAL:
            for(auto arg: curF->getArgumentList()){
                if(!(arg->getType()->getPrimitiveID() == IRType::FloatTyID ||
                     arg->getType()->getPrimitiveID() == IRType::DoubleTyID)){
                        /*为参数创建regNode结点*/
                        arg->setRegNode();
                        initial.insert(arg->getRegNode());

                        /*创建参数到寄存器的move指令*/
                        auto move = new RegisterMove(arg, ParamRegister::Num2Reg(argcnt));
                        worklistMoves.push_back(move);
                        arg->getRegNode()->moveList.insert(move);
                        arg->getRegNode()->nodemovenum++;
                        argcnt++;
                    }
                }
            break;
        case FLOAT:
            for(auto arg: curF->getArgumentList()){
                if((arg->getType()->getPrimitiveID() == IRType::FloatTyID ||
                    arg->getType()->getPrimitiveID() == IRType::DoubleTyID)){
                        /*为参数创建regNode结点*/
                        arg->setRegNode();
                        initial.insert(arg->getRegNode());

                        /*创建参数到寄存器的move指令*/
                        auto move = new RegisterMove(arg, FloatParamRegister::Num2Reg(argcnt));
                        worklistMoves.push_back(move);
                        arg->getRegNode()->moveList.insert(move);
                        arg->getRegNode()->nodemovenum++;
                        argcnt++;
                    }
                }
            break;
    }

    /*这里是给每条指令都添加一个regNode*/
    for(auto BB: curF->getBasicBlockList()){
        for(auto inst: BB->getInstList()){
            if((inst->isBinaryOp() ||
                inst->getOpcode() == IRInstruction::Call ||
                inst->getOpcode() == IRInstruction::Load ||
                inst->getOpcode() == IRInstruction::Shl ||
                inst->getOpcode() == IRInstruction::Shr)){
                inst->setRegNode();
            }else if( inst->getOpcode() == IRInstruction::Move){
                dynamic_cast<IRInstruction*>(inst->getOperand(0))->setRegNode();

                if(!dynamic_cast<IRConstant*>(inst->getOperand(1))){
                    /*考虑move指令op可能是arg或者指令*/
                    if(inst->getOperand(1)->getValueType() == IRValue::InstructionVal)
                        dynamic_cast<IRInstruction*>(inst->getOperand(1))->setRegNode();
                    else if(inst->getOperand(1)->getValueType() == IRValue::ArgumentVal)
                        dynamic_cast<IRArgument*>(inst->getOperand(1))->setRegNode();    
                }
            }
        }
    }

    /*指令寄存器冲突图*/
    std::vector<IRValue*> defvec;
    switch(which){
        case GENERAL:
            for(auto BB: curF->getBasicBlockList()){
                for(auto inst: BB->getInstList()){
                    if((inst->isBinaryOp() ||
                       (inst->getOpcode() == IRInstruction::Call && inst->getType()->getPrimitiveID() != IRType::VoidTyID) ||
                        inst->getOpcode() == IRInstruction::Load ||
                        inst->getOpcode() == IRInstruction::Shl ||
                        inst->getOpcode() == IRInstruction::Shr) &&
                      !(inst->getType()->getPrimitiveID() == IRType::FloatTyID ||
                        inst->getType()->getPrimitiveID() == IRType::DoubleTyID)){
                        defvec.push_back(inst);
                    }else if( inst->getOpcode() == IRInstruction::Move &&
                            !(inst->getOperand(0)->getType()->getPrimitiveID() == IRType::FloatTyID ||
                              inst->getOperand(0)->getType()->getPrimitiveID() == IRType::DoubleTyID)){
                        /*源操作数与目的操作数均与这条move指令相关*/
                        defvec.push_back(inst->getOperand(0));

                        if(!dynamic_cast<IRConstant*>(inst->getOperand(1))){
                            auto move = new RegisterMove(dynamic_cast<IRMoveInst*>(inst));
                            dynamic_cast<IRInstruction*>(inst->getOperand(0))->getRegNode()->moveList.insert(move);
                            dynamic_cast<IRInstruction*>(inst->getOperand(0))->getRegNode()->nodemovenum++;

                            /*考虑move指令op可能是arg或者指令*/
                            if(inst->getOperand(1)->getValueType() == IRValue::InstructionVal) {
                                dynamic_cast<IRInstruction *>(inst->getOperand(1))->getRegNode()->moveList.insert(move);
                                dynamic_cast<IRInstruction *>(inst->getOperand(1))->getRegNode()->nodemovenum++;
                            }
                            else if(inst->getOperand(1)->getValueType() == IRValue::ArgumentVal) {
                                dynamic_cast<IRArgument *>(inst->getOperand(1))->getRegNode()->moveList.insert(move);
                                dynamic_cast<IRArgument *>(inst->getOperand(1))->getRegNode()->nodemovenum++;
                            }
                            /*有可能合并的传送指令,必须保证两边都不是常数才算一条传送指令*/
                            RegisterNode::worklistMoves.push_back(move);
                        }
                    }

                    for(auto ir:defvec){
                        RegisterNode::initial.insert(dynamic_cast<IRInstruction*>(ir)->getRegNode());
                        for(auto irlive:*inst->getLive()->getOUTLive()){
                            /*这里要保证本身不是move指令；如果是move指令，那么def不会与use发生冲突*/
                            if(!(inst->getOpcode() == IRInstruction::Move &&
                                 irlive == dynamic_cast<IRMoveInst*>(inst)->getSrc())) {
                                if(dynamic_cast<IRInstruction *>(irlive) == nullptr){
                                    RegisterNode::AddEdge(dynamic_cast<IRInstruction *>(ir)->getRegNode(),
                                                          dynamic_cast<IRArgument *>(irlive)->getRegNode());
                                }else{
                                    RegisterNode::AddEdge(dynamic_cast<IRInstruction *>(ir)->getRegNode(),
                                                          dynamic_cast<IRInstruction *>(irlive)->getRegNode());
                                }
                            }
                        }
                    }
                    defvec.clear();
                }
            }
            break;
        case FLOAT:
            for(auto BB: curF->getBasicBlockList()){
                for(auto inst: BB->getInstList()){
                    if((inst->isBinaryOp() ||
                       (inst->getOpcode() == IRInstruction::Call && inst->getType()->getPrimitiveID() != IRType::VoidTyID) ||
                        inst->getOpcode() == IRInstruction::Load ||
                        inst->getOpcode() == IRInstruction::Shl ||
                        inst->getOpcode() == IRInstruction::Shr) &&
                       (inst->getType()->getPrimitiveID() == IRType::FloatTyID ||
                        inst->getType()->getPrimitiveID() == IRType::DoubleTyID)){
                        defvec.push_back(inst);
                    }else if( inst->getOpcode() == IRInstruction::Move &&
                             (inst->getOperand(0)->getType()->getPrimitiveID() == IRType::FloatTyID ||
                              inst->getOperand(0)->getType()->getPrimitiveID() == IRType::DoubleTyID)){
                        /*源操作数与目的操作数均与这条move指令相关*/
                        defvec.push_back(inst->getOperand(0));

                        if(!dynamic_cast<IRConstant*>(inst->getOperand(1))){
                            auto move = new RegisterMove(dynamic_cast<IRMoveInst*>(inst));
                            dynamic_cast<IRInstruction*>(inst->getOperand(0))->getRegNode()->moveList.insert(move);
                            
                            /*考虑move指令op可能是arg或者指令*/
                            if(inst->getOperand(1)->getValueType() == IRValue::InstructionVal)
                                dynamic_cast<IRInstruction*>(inst->getOperand(1))->getRegNode()->moveList.insert(move);
                            else if(inst->getOperand(1)->getValueType() == IRValue::ArgumentVal)
                                dynamic_cast<IRArgument*>(inst->getOperand(1))->getRegNode()->moveList.insert(move); 
                            /*有可能合并的传送指令,必须保证两边都不是常数才算一条传送指令*/
                            worklistMoves.push_back(move);
                        }
                    }

                    for(auto ir:defvec){
                        initial.insert(dynamic_cast<IRInstruction*>(ir)->getRegNode());
                        for(auto irlive:*inst->getLive()->getOUTLive()){
                            /*这里要保证本身不是move指令；如果是move指令，那么def不会与use发生冲突*/
                            if(!(inst->getOpcode() == IRInstruction::Move &&
                                 irlive == dynamic_cast<IRMoveInst*>(inst)->getSrc())) {
                                if(dynamic_cast<IRInstruction *>(irlive) == nullptr){
                                    RegisterNode::AddEdge(dynamic_cast<IRInstruction *>(ir)->getRegNode(),
                                                          dynamic_cast<IRArgument *>(irlive)->getRegNode());
                                }else{
                                    RegisterNode::AddEdge(dynamic_cast<IRInstruction *>(ir)->getRegNode(),
                                                          dynamic_cast<IRInstruction *>(irlive)->getRegNode());
                                }
                            }
                        }
                    }
                    defvec.clear();
                }
            }
            break;
    }
}

void RegisterNode::AddEdge(RegisterNode* u, RegisterNode* v){
    auto it = std::find(adjSet.begin(), adjSet.end(), std::make_tuple(u,v));

    /*若adjList没有该元素，则加入*/
    if((it==adjSet.end()) && (u!=v)){
        adjSet.emplace_back(u,v);
        adjSet.emplace_back(v,u);

        /*相当于要求不是机器寄存器*/
        if(std::find(precolored.begin(), precolored.end(), u) == precolored.end()){
            u->adjList.push_back(v);
            degree[u]++;
            u->nodedegree++;
        }

        if(std::find(precolored.begin(), precolored.end(), v) == precolored.end()){
            v->adjList.push_back(u);
            degree[v]++;
            v->nodedegree++;
        }
    }

}

void RegisterNode::MakeWorklist(){
    while(!initial.empty()){
        auto node = *initial.begin();
        initial.erase(std::find(initial.begin(), initial.end(), node));

        if(degree[node] >= regNum){
            spillWorklist.push_back(node);          //准备溢出
        }else if(MoveRelated(node)){
            freezeWorklist.push_back(node);         //
        }else{
            simplifyWorklist.push_back(node);       //可以简化该结点
        }
    }
}

/*简化掉低度数结点*/
void RegisterNode::simplify(){
    auto simplifynode = *simplifyWorklist.begin();
    selectStack.push_back(simplifynode);
    simplifyWorklist.erase(simplifyWorklist.begin());

    auto adjcent = Adjcent(simplifynode);
    for(auto adjnode: adjcent){
        DecrementDegree(adjnode);
    }
}

void RegisterNode::DecrementDegree(RegisterNode* node){
    //度数--
    degree[node]--;
    node->nodedegree--;
    if(degree[node] == regNum-1){
        auto adjmove = Adjcent(node);
        adjmove.push_back(node);
        EnableMoves(adjmove);

        //度数降为低度数，因此不用考虑假溢出，考虑合并或者冻结
        spillWorklist.erase(std::find(spillWorklist.begin(), spillWorklist.end(), node));
        if(MoveRelated(node)){
            freezeWorklist.push_back(node);
        }else{
            simplifyWorklist.push_back(node);
        }
    }
}

/*node中的未做好合并准备的指令加入到准备合并的指令集中*/
void RegisterNode::EnableMoves(std::vector<RegisterNode*> nodes){
    for(auto node: nodes){
        for(auto nodemove: NodeMoves(node)){
            auto movepos = std::find(activeMoves.begin(), activeMoves.end(), nodemove);
            if(movepos != activeMoves.end()){
                activeMoves.erase(movepos);
                worklistMoves.push_back(nodemove);
            }
        }
    }
}

void RegisterNode::Coalesce(){
    auto move = *worklistMoves.begin();
    RegisterNode* dst = GetAlias(move->getDstNode());
    RegisterNode* src = GetAlias(move->getSrcNode());

    /*构建unode,vnode*/
    RegisterNode* unode;
    RegisterNode* vnode;
    if(std::find(precolored.begin(), precolored.end(), src) != precolored.end()){ unode = src; vnode = dst; }
    else{ unode = dst; vnode = src; }

    worklistMoves.erase(worklistMoves.begin());
    unode->nodemovenum--;
    vnode->nodemovenum--;
    if(unode == vnode){                                                                                                 //两个node一样
        coalescedMoves.push_back(move);
        AddWorkList(unode);
    }else if(std::find(precolored.begin(), precolored.end(), vnode) != precolored.end() ||
             std::find(adjSet.begin(), adjSet.end(), std::make_tuple(unode, vnode)) != adjSet.end()){   //vnode,unode都是机器寄存器或者unode,vnode冲突受到抑制
                constrainedMoves.push_back(move);
                AddWorkList(unode);
                AddWorkList(vnode);
    }else if((std::find(precolored.begin(), precolored.end(), unode) != precolored.end() && George(vnode, unode)) ||    //采用George保守合并策略(unode是机器寄存器)
             (std::find(precolored.begin(), precolored.end(), unode) == precolored.end() && Briggs(vnode, unode))       //采用Briggs保守合并策略(两个都不是机器寄存器)
                ){                                                                                                        
                    coalescedMoves.push_back(move);
                    Combine(unode, vnode);
                    AddWorkList(unode);
    }else{
        activeMoves.push_back(move);
    }
}

/*返回alias*/
RegisterNode* RegisterNode::GetAlias(RegisterNode* node){
    if(std::find(coalescedNodes.begin(), coalescedNodes.end(), node) != coalescedNodes.end()){
        return GetAlias(alias[node]);
    }else{
        return node;
    }
}

/*即满足低度数传送无关的节点，可以加入simplifyWorkList*/
void RegisterNode::AddWorkList(RegisterNode* node){
    if( std::find(precolored.begin(), precolored.end(), node) == precolored.end() &&
        !MoveRelated(node) && (degree[node]<regNum)){
            freezeWorklist.erase(std::find(freezeWorklist.begin(), freezeWorklist.end(), node));
            simplifyWorklist.push_back(node);
        }
}

/*考虑到tnode是机器寄存器，t与v邻接或tnode可以合并*/
bool RegisterNode::OK(RegisterNode* tnode, RegisterNode* rnode){
    return  degree[tnode]<regNum ||
            std::find(precolored.begin(), precolored.end(), tnode)!=precolored.end() ||
            std::find(adjSet.begin(), adjSet.end(), std::make_tuple(tnode, rnode))!=adjSet.end();
}

/*邻接高度数结点不能大于K*/
bool RegisterNode::Conservative(std::vector<RegisterNode*> nodes){
    unsigned k=0;
    for(auto nnode: nodes){
        if(degree[nnode]>=regNum)
            k++;
    }
    return (k<regNum);
}

bool RegisterNode::Briggs(RegisterNode* vnode, RegisterNode* unode){
    auto uadj = Adjcent(unode);
    auto vadj = Adjcent(vnode);
    std::vector<RegisterNode*> uvunion(uadj.size() + vadj.size());

    /*unadj是一个迭代器*/
    auto uvadj = std::set_union(uadj.begin(), uadj.end(), vadj.begin(), vadj.end(), uvunion.begin());
    uvunion.resize(uvadj - uvunion.begin());
    return Conservative(uvunion);
}

bool RegisterNode::George(RegisterNode* vnode, RegisterNode* unode){
    bool flag = true;
    auto vadj = Adjcent(vnode);
    for(auto tnode: vadj){
        flag &= OK(tnode, unode);
    }
    return flag;
}

void RegisterNode::Combine(RegisterNode* unode, RegisterNode* vnode){
    /*将vnode从哪个工作集中删除*/
    if(std::find(freezeWorklist.begin(), freezeWorklist.end(), vnode) != freezeWorklist.end()){
        freezeWorklist.erase(std::find(freezeWorklist.begin(), freezeWorklist.end(), vnode));
    }else{
        spillWorklist.erase(std::find(spillWorklist.begin(), spillWorklist.end(), vnode));
    }
    coalescedNodes.push_back(vnode);

    /*unode传送有关的指令给到vnode,vnode进行enable*/
    alias[vnode]=unode;
    for(auto move: vnode->moveList){
        unode->moveList.insert(move);
        unode->nodemovenum++;
    }
    unode->nodemovenum--;       //这里--的原因，是因为需要把当前的这条move指令排除在外
    EnableMoves({vnode});

    /*vnode的邻接结点处理到unode上*/
    for(auto tnode:Adjcent(vnode)){
        AddEdge(tnode, unode);
        DecrementDegree(tnode);
    }

    /*经过处理之后，unode可能需要加入到溢出工作集中(如果>=K)*/
    if(degree[unode]>=regNum && std::find(freezeWorklist.begin(), freezeWorklist.end(), unode)!=freezeWorklist.end()){
        freezeWorklist.erase(std::find(freezeWorklist.begin(), freezeWorklist.end(), unode));
        spillWorklist.push_back(unode);
    }
}

void RegisterNode::Freeze(){
    RegisterNode* unode = *freezeWorklist.begin();

    /*首先unode变成可简化的节点==结点，然后对与其相关的move指令的其他节点进行冻结操作*/
    freezeWorklist.erase(freezeWorklist.begin());
    simplifyWorklist.push_back(unode);
    FreezeMoves(unode);
}

/*对应的unode在被冻结之后，考虑unode相关的传送指令对应的其他结点是否要加入简化工作集中*/
void RegisterNode::FreezeMoves(RegisterNode* unode){

    RegisterNode* xnode;
    RegisterNode* ynode;
    RegisterNode* vnode;
    for(auto move: NodeMoves(unode)){
        xnode = move->getDstNode();
        ynode = move->getSrcNode();

        /*通过检查最终将vnode,unode表示为该move指令对应的两个node*/
        if(GetAlias(ynode) == GetAlias(unode)){
            vnode = GetAlias(xnode);
        }else{
            vnode = GetAlias(ynode);
        }

        /*这条传送指令将被冻结*/
        activeMoves.erase(std::find(activeMoves.begin(), activeMoves.end(), move));
        frozenMoves.push_back(move);

        /*低度数传送有关结点变成低度数传送无关结点*/
        if(NodeMoves(vnode).empty() && degree[vnode]<regNum){
            freezeWorklist.erase(std::find(freezeWorklist.begin(), freezeWorklist.end(), vnode));
            simplifyWorklist.push_back(vnode);
        }
    }                                                   
}

void RegisterNode::SelectSpill(){
    RegisterNode* mnode = *spillWorklist.begin();

    spillWorklist.erase(spillWorklist.begin());
    simplifyWorklist.push_back(mnode);
    FreezeMoves(mnode);
}

void RegisterNode::AssignColors(){
    while(!selectStack.empty()){
        RegisterNode* nnode = selectStack.back();
        selectStack.pop_back();
        
        /*初始化颜色种类*/
        std::vector<unsigned> okColors;
        switch(which) {
            case GENERAL:
                for(auto reg: RegisterFactory::getGRegList()){
                    okColors.push_back(reg->getRegNode()->getColor());
                }
                break;
            case FLOAT:
                for(auto reg: RegisterFactory::getFRegList()){
                    okColors.push_back(reg->getRegNode()->getColor());
                }
                break;
        }

        /*若邻接结点已被染色，则选择数目减少*/
        for(auto wnode: nnode->adjList){
            if((std::find(coloredNodes.begin(), coloredNodes.end(), GetAlias(wnode)) != coloredNodes.end() ||
                std::find(precolored.begin(), precolored.end(), GetAlias(wnode)) != precolored.end()) &&
                std::find(okColors.begin(), okColors.end(), GetAlias(wnode)->color) != okColors.end()){
                    okColors.erase(std::find(okColors.begin(), okColors.end(), GetAlias(wnode)->color));
                }
        }

        if(okColors.empty()){
            spilledNodes.push_back(nnode);
        }else{
            coloredNodes.push_back(nnode);
            /*这里可以考虑优先选择那个寄存器进行染色*/
            nnode->color = *okColors.begin();                                                                                                                                                                                             nnode->color = *okColors.begin();
        }

        /*根据颜色赋予指令reg*/
        auto colorReg = getColorReg(nnode->color);
        if(nnode->getParentInst() != nullptr)
            nnode->getParentInst()->setReg(colorReg);
        if(nnode->getParentArg() != nullptr)
            nnode->getParentArg()->setReg(colorReg);
        /*相应的函数记录下对应的reg*/
        switch (colorReg->getRegty()) {
            case Register::CallerSaved:           
            case Register::Param:
            case Register::FloatCallerSaved:
            case Register::FloatParam:
                curF->setCallerSavedReg(colorReg);
                break;
            case Register::CalleeSaved:      
            case Register::FloatCalleeSaved:       
                curF->setCalleeSavedReg(colorReg);
                break;
        }

        okColors.clear();
    }

    RegisterNode* coalesnode;
    /*已经被合并的结点采用与其合并的寄存器结点的颜色*/
    for(auto coalesnode: coalescedNodes) {
        coalesnode->color = GetAlias(coalesnode)->color;

        auto colorReg = getColorReg(coalesnode->color);
        if(coalesnode->getParentInst() != nullptr)
            coalesnode->getParentInst()->setReg(colorReg);
        if(coalesnode->getParentArg() != nullptr)
            coalesnode->getParentArg()->setReg(colorReg);
        /*相应的函数记录下对应的reg*/
        switch (colorReg->getRegty()) {
            case Register::CallerSaved:           
            case Register::Param:
            case Register::FloatCallerSaved:
            case Register::FloatParam:
                curF->setCallerSavedReg(colorReg);
                break;
            case Register::CalleeSaved:      
            case Register::FloatCalleeSaved:       
                curF->setCalleeSavedReg(colorReg);
                break;
        }
    }

}

void RegisterNode::RewriteProgram(){
    spilledNodes.clear();
    coloredNodes.clear();
    coalescedNodes.clear();
}

void RegisterNode::RegisterAlloc(IRFunction &F, WHICH which){
    /*初始化寄存器分配需要的静态变量*/
    curF = &F;
    RegisterNode::which = which;

    /*开始寄存器分配*/
    Build();
    MakeWorklist();
    while(!(simplifyWorklist.empty() && worklistMoves.empty() && freezeWorklist.empty() && spillWorklist.empty())){
        if(!simplifyWorklist.empty()) simplify();
        else if(!worklistMoves.empty()) Coalesce();
        else if(!freezeWorklist.empty()) Freeze();
        else if(!spillWorklist.empty()) SelectSpill();
    }
    AssignColors();
    if(!spilledNodes.empty()){
        RewriteProgram();
        RegisterAlloc(F, which);
    }
}

void RegisterNode::Build(){
    if(which == GENERAL) RegisterFactory::initGReg();
    else if(which == FLOAT) RegisterFactory::initFReg();
    RegisterNode::init();
}

void RegisterNode::End(){
    precolored.clear();
    simplifyWorklist.clear();
    freezeWorklist.clear();
    spillWorklist.clear();
    spilledNodes.clear();
    coalescedNodes.clear();
    coloredNodes.clear();
    selectStack.clear();

    coalescedMoves.clear();
    constrainedMoves.clear();
    frozenMoves.clear();
    activeMoves.clear();

    adjSet.clear();
    degree.clear();
    alias.clear();
    initial.clear();
    worklistMoves.clear();
}

Register* RegisterNode::getColorReg(int color){
    for(auto regnode: precolored){
        if(color == regnode->getColor()){
            return regnode->getParentReg();
        }
    }
}