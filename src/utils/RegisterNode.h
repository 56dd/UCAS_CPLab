#ifndef COMPILER_REGISTERNODE_H
#define COMPILER_REGISTERNODE_H

#include <algorithm>
#include <cstddef>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
#include "Register.h"

class IRInstruction;
class Register;
class IRFunction;
class IRArgument;
class RegisterMove;

class RegisterNode{
public:
    enum WHICH{
        GENERAL = 0,
        FLOAT,
    };

private:
    static unsigned regNum;
    static WHICH which;     //记录现在是对通用寄存器进行分配还是浮点寄存器进行分配
    static IRFunction* curF;//记录现在是在对哪个函数进行寄存器分配

    static std::list<RegisterNode*> precolored;       //机器寄存器集合
    static std::list<RegisterNode*> simplifyWorklist; //低度数传送无关结点
    static std::list<RegisterNode*> freezeWorklist;   //低度数传送有关结点
    static std::list<RegisterNode*> spillWorklist;    //高度数结点表
    static std::list<RegisterNode*> spilledNodes;     //本轮要被溢出结点集合
    static std::list<RegisterNode*> coalescedNodes;   //已合并寄存器集合
    static std::list<RegisterNode*> coloredNodes;     //已成功着色结点集合
    static std::list<RegisterNode*> selectStack;      //从图中删除的临时变量的栈

    static std::vector<RegisterMove*> coalescedMoves;     //已经合并的传送指令集合
    static std::vector<RegisterMove*> constrainedMoves;   //源操作数目的操作数冲突的传送指令集合
    static std::vector<RegisterMove*> frozenMoves;        //不再考虑合并的的传送指令集合
    static std::vector<RegisterMove*> activeMoves;        //还未做好合并准备的传送指令集合
    static std::vector<RegisterMove*> worklistMoves;      //有可能合并的传送指令集合

    static std::vector<std::tuple<RegisterNode*, RegisterNode*>> adjSet;    //冲突边的集合
    static std::map<RegisterNode*, unsigned> degree;                        //包含每个结点当前度数的数组
    static std::map<RegisterNode*, RegisterNode*> alias;                    //当一条传送指令被合并，有alias(v)=u
    static std::set<RegisterNode*> initial;          //临时寄存器集合

    static void init();
    static void MakeWorklist();
    static std::vector<RegisterNode*> Adjcent(RegisterNode* node);
    static std::vector<RegisterMove*> NodeMoves(RegisterNode* node);
    static bool MoveRelated(RegisterNode* node);
    static void simplify();
    static void DecrementDegree(RegisterNode* node);
    static void EnableMoves(std::vector<RegisterNode*> nodes);
    static void Coalesce();
    static RegisterNode* GetAlias(RegisterNode* node);
    static void AddWorkList(RegisterNode* node);
    static bool OK(RegisterNode* tnode, RegisterNode* rnode);
    static bool Conservative(std::vector<RegisterNode*> nodes);
    static bool Briggs(RegisterNode* vnode, RegisterNode* unode);
    static bool George(RegisterNode* vnode, RegisterNode* unode);
    static void Combine(RegisterNode* unode, RegisterNode* vnode);
    static void Freeze();
    static void FreezeMoves(RegisterNode* unode);
    static void SelectSpill();
    static void AssignColors();
    static void RewriteProgram();
    static void Build();
    static void AddEdge(RegisterNode* u, RegisterNode* v);
    static Register* getColorReg(int color);

    /*对象私有*/
    int nodedegree = 0;                                                    //结点私有的度数(当前图上)
    int nodemovenum = 0;                                                   //结点相关的move指令(当前图上)
    std::list<RegisterNode*> adjList;                                      //图的邻接表表示
    std::set<RegisterMove*> moveList;                                      //与该结点相关的传送指令表的映射

    /*可对外展示的*/
    int color;
    std::string RegisterNodeName;
    IRInstruction* parentInst;
    Register* parentReg;
    IRArgument* parentArg;

public:
    static void RegisterAlloc(IRFunction &F, WHICH which);
    static void End();

    std::string& getRegNodeName() { return RegisterNodeName; };
    IRInstruction* getParentInst() { return parentInst; };
    Register* getParentReg() { return parentReg; };
    IRArgument* getParentArg() { return parentArg; };
    int getColor() const { return color; };

    explicit RegisterNode(std::string name, IRInstruction* inst) : RegisterNodeName(name), parentInst(inst) { parentReg = nullptr; parentArg = nullptr; color = -1; };
    explicit RegisterNode(std::string name, Register* reg) : RegisterNodeName(name), parentReg(reg) { parentInst = nullptr; parentArg = nullptr; color = reg->getRegSeq(); };
    explicit RegisterNode(std::string name, IRArgument* arg) : RegisterNodeName(name), parentArg(arg) { parentReg = nullptr; parentInst = nullptr; color = -1; };
};

#endif //COMPILER_REGISTERNODE_H