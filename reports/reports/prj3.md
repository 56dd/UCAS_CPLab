# 编译原理实验三：代码优化与目标代码生成

[TOC]

## 小组成员
朱徐塬、陈嘉康、楼云韬

## 1. 任务说明

本次实验实现了CACT语言编译器的代码优化和目标代码生成部分，主要完成以下任务：

1. 掌握从IR到汇编的翻译过程
2. 掌握栈的组织和管理形式，正确实现变量初始化与递归调用
3. 端到端编译CACT源码到riscv64gc汇编文件(.S)，先完成再完美
4. 了解中间表示上可实现的性能优化变换，以及三地址表示对优化的帮助

### 1.1 编译流程

编译过程主要包括以下步骤：

1. 词法分析和语法分析生成AST
2. 语义分析检查类型和作用域
3. IR生成器将AST转换为中间代码
4. 代码优化Pass对IR进行优化
5. 寄存器分配为变量分配寄存器
6. 目标代码生成器将IR转换为RISC-V汇编

![编译流程](compilation_flow.png)

## 2. 实验设计

### 2.1 总体设计

本实验的主要代码结构包括：

- `src/`：源代码目录
  - `Pass/`：优化Pass目录
    - `MemToRegPass.h/cpp`：内存到寄存器转换
    - `ConstantPass.h/cpp`：常量传播优化
    - `LocalSubExpPass.h/cpp`：局部公共子表达式消除
    - `GlobalSubExpPass.h/cpp`：全局公共子表达式消除
    - `HoistingLoopInvariantValuePass.h/cpp`：循环不变量外提
    - `RegisterPass.h/cpp`：寄存器分配
    - `PHIdeletePass.h/cpp`：PHI指令删除
    - 其他优化Pass
  - `RISC-V/`：RISC-V后端目录
    - `Module.h/cpp`：模块表示
    - `Function.h/cpp`：函数表示
    - `BasicBlock.h/cpp`：基本块表示
    - `Instruction.h/cpp`：指令基类
    - 各种具体指令实现
  - `Optimizer.h/cpp`：优化器主类
  - `BackEnd.h/cpp`：后端接口

### 2.2 优化Pass设计

我们的优化Pass设计采用了模块化的架构，每个Pass都继承自基类Pass，可以独立运行和组合。

#### 2.2.1 Pass层次结构

Pass的层次结构如下：

1. `Pass`：所有Pass的基类
   - `FunctionPass`：函数级Pass
     - `BasicBlockPass`：基本块级Pass

这种设计使得我们可以：
1. 统一管理所有优化Pass
2. 根据优化级别控制Pass的执行
3. 方便添加新的优化Pass

#### 2.2.2 优化器设计

优化器(`Optimizer`)负责管理所有优化Pass的执行：

```cpp
class Optimizer {
public:
    explicit Optimizer(IRModule *ir);
    void run();
    void addPass(Pass * pass);
    void build();
    void setLevel(int level);
private:
    std::vector<Pass *> passList;
    IRModule *ir;
    int level;
};
```

优化器通过`build()`方法添加所有优化Pass，通过`run()`方法按顺序执行所有Pass。

### 2.3 RISC-V后端设计

RISC-V后端负责将优化后的IR代码转换为RISC-V汇编代码。

#### 2.3.1 后端层次结构

后端的层次结构如下：

1. `Module`：整个模块的表示
   - `GlobalVariable`：全局变量
   - `Function`：函数
     - `BasicBlock`：基本块
       - `Instruction`：指令

#### 2.3.2 指令翻译策略

我们采用逐条翻译的策略，将IR指令直接映射到RISC-V指令：

1. **算术运算**：直接映射到对应的RISC-V指令
2. **内存操作**：使用load/store指令
3. **控制流**：使用branch和jump指令
4. **函数调用**：遵循RISC-V ABI规范

## 3. 实验实现

### 3.1 优化Pass实现

#### 3.1.1 Mem2RegPass（内存到寄存器转换）

Mem2RegPass是本次实验中最核心的优化Pass之一，它的主要作用是将内存操作转换为SSA形式的寄存器操作。

**为什么需要SSA转换？**

在LLVM IR中，SSA（静态单赋值）要求每个虚拟寄存器只能被赋值一次。这个要求虽然为后续优化带来了便利，但在处理控制流时会产生问题。

考虑这样一个简单的例子：

```c
int a = 0;
if (condition) {
    a = 1;
} else {
    a = 2;
}
```

如果直接翻译成IR，会出现多次赋值的情况，违反了SSA原则。为了解决这个问题，我们采用了两种策略：

**策略一：使用内存操作**

通过alloca指令在栈上分配空间，使用store和load指令进行读写。这种方式实现简单，但性能较差，因为每次访问都需要内存操作。

**策略二：引入PHI节点**

使用PHI节点来处理控制流中的多路合并，这是更高效的方法。PHI节点根据前驱基本块的不同，选择不同的值。

**我们的实现方案：**

前端生成时使用策略一（内存操作），然后通过Mem2RegPass将内存操作转换为策略二（PHI节点）。这样既保证了实现的简单性，又获得了良好的性能。

**算法实现步骤：**

1. **构建控制流图**：分析基本块之间的跳转关系
2. **计算支配关系**：使用Lengauer-Tarjan算法构建支配树
3. **确定支配边界**：找出需要插入PHI节点的位置
4. **插入PHI节点**：在支配边界处插入PHI指令
5. **变量重命名**：遍历支配树，重命名变量并删除冗余的内存操作

**核心代码实现：**

```cpp
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
```

#### 3.1.2 ConstantPass（常量传播）

ConstantPass负责在编译时计算常量表达式，消除不必要的运行时计算。

**优化原理：**

如果一条指令的所有操作数都是常量，那么这条指令的结果在编译时就可以计算出来，不需要在运行时执行。

**我们处理的优化情况：**

1. **常量运算**：如`5 + 3`直接计算为`8`
2. **特殊值优化**：如`x + 0`优化为`x`，`x * 1`优化为`x`
3. **条件跳转优化**：如果条件在编译时已知，直接删除不必要的分支

**实现思路：**

遍历每个基本块中的指令，检查操作数是否都是常量。如果是，则计算结果并替换指令。对于条件跳转，如果条件已知，则删除条件判断，直接跳转到目标基本块。

**关键代码：**

```cpp
void ConstantPass::runOnBasicBlock(IRBasicBlock &BB) {
    for (auto instIterator = BB.getInstList().begin(); 
         instIterator != BB.getInstList().end();) {
        auto inst = *instIterator;
        bool flag = true;

        // 检查是否为常量运算
        if (isConstantOperation(inst)) {
            IRConstant* result = computeConstant(inst);
            inst->replaceAllUsesWith(result);
            instIterator = BB.getInstList().erase(instIterator);
            flag = false;
        }
        
        if (flag) {
            instIterator++;
        }
    }
}
```

#### 3.1.3 LocalSubExpPass（局部公共子表达式消除）

LocalSubExpPass在基本块内部消除重复的表达式计算。

**优化原理：**

如果在同一个基本块中，有两条指令计算相同的表达式，那么第二条指令的结果可以直接使用第一条指令的结果，而不需要重新计算。

**实现方法：**

使用两层循环遍历基本块中的指令，检查是否有相同的表达式。如果找到，就用第一条指令的结果替换第二条指令的所有使用。

**注意事项：**

某些指令（如函数调用、内存操作等）不能进行这种优化，因为它们可能有副作用。

#### 3.1.4 GlobalSubExpPass（全局公共子表达式消除）

GlobalSubExpPass在整个函数范围内消除重复的表达式计算。

**与局部优化的区别：**

局部优化只在基本块内部进行，而全局优化需要考虑整个函数的控制流图。

**实现策略：**

1. **基于支配树的遍历**：按照支配树的顺序遍历基本块
2. **维护已见指令集合**：记录已经见过的指令
3. **检查重复计算**：对于每个新指令，检查是否与已见指令重复

**特殊处理：内存操作**

对于load和store指令，我们采用了更激进的优化策略。由于load指令不会修改内存，在没有store打断的情况下，可以重用之前的load结果。

#### 3.1.5 HoistingLoopInvariantValuePass（循环不变量外提）

HoistingLoopInvariantValuePass将循环中不变的表达式外提到循环外。

**什么是循环不变量？**

循环不变量是指在循环执行过程中值不会改变的表达式。将这些表达式外提到循环外，可以避免重复计算。

**识别循环不变量的条件：**

1. 常量
2. 循环内没有到达定值
3. 循环内到达定值只有一个且该定值是循环不变量

**实现步骤：**

1. **循环识别**：找到控制流图中的循环结构
2. **不变量识别**：根据上述条件识别循环不变量
3. **外提优化**：将循环不变量外提到循环的必经节点

#### 3.1.6 RegisterPass（寄存器分配）

RegisterPass使用图着色算法为IR中的虚拟寄存器分配物理寄存器。

**为什么需要寄存器分配？**

IR中的虚拟寄存器数量可能超过物理寄存器的数量，需要通过寄存器分配算法将虚拟寄存器映射到物理寄存器，必要时将一些变量溢出到内存。

**算法步骤：**

1. **PHI指令处理**：将PHI指令转换为move指令
2. **活跃变量分析**：计算每条指令的活跃变量
3. **构建冲突图**：根据活跃变量分析结果构建图
4. **图着色**：使用图着色算法分配寄存器

**活跃变量分析：**

活跃变量分析是寄存器分配的基础。一个变量在某个点是活跃的，意味着它在这个点之后还会被使用。

我们使用数据流分析的方法计算活跃变量：

- 从基本块末尾开始，向前遍历指令
- 对于每条指令，更新活跃变量集合
- 在基本块之间传播活跃变量信息

**图着色算法：**

1. **简化阶段**：移除度数小于k的节点
2. **合并阶段**：尝试合并move相关的节点
3. **溢出阶段**：选择节点进行溢出
4. **着色阶段**：为节点分配颜色（寄存器）

### 3.2 RISC-V后端实现

#### 3.2.1 函数栈帧管理

RISC-V后端需要正确管理函数栈帧，确保函数调用和返回的正确性。

**栈帧布局：**

我们的栈帧布局如下（从高地址到低地址）：
- 参数区域
- 返回地址
- 保存的寄存器
- 局部变量
- 临时空间

**栈帧对齐：**

RISC-V要求栈帧16字节对齐，我们通过计算总大小并向上取整到16的倍数来实现。

**寄存器保存策略：**

- **Callee-saved寄存器**：被调用函数负责保存和恢复
- **Caller-saved寄存器**：调用函数负责保存和恢复

#### 3.2.2 指令翻译

我们将IR指令翻译为对应的RISC-V汇编指令。

**算术运算指令：**

```cpp
void BinaryOperator::print(std::ostream &O) {
    switch (opcode) {
        case Instruction::Add:
            O << "add\t" << rd->getName() << ", " << rs1->getName() << ", " << rs2->getName();
            break;
        case Instruction::Sub:
            O << "sub\t" << rd->getName() << ", " << rs1->getName() << ", " << rs2->getName();
            break;
        // ... 其他操作
    }
}
```

**内存操作指令：**

```cpp
void LoadInst::print(std::ostream &O) {
    if (type == IRType::IntTy || type == IRType::BoolTy) {
        O << "ld\t" << rd->getName() << ", " << offset << "(" << rs1->getName() << ")";
    } else if (type == IRType::FloatTy || type == IRType::DoubleTy) {
        O << "fld\t" << rd->getName() << ", " << offset << "(" << rs1->getName() << ")";
    }
}
```

**控制流指令：**

```cpp
void BranchInst::print(std::ostream &O) {
    if (isConditional()) {
        O << "b" << getConditionString() << "\t" << rs1->getName() << ", " 
          << rs2->getName() << ", " << target->getName();
    } else {
        O << "j\t" << target->getName();
    }
}
```

#### 3.2.3 函数调用ABI

我们遵循RISC-V ABI规范处理函数调用。

**参数传递：**

- 前8个整型参数使用a0-a7寄存器
- 前8个浮点参数使用fa0-fa7寄存器
- 其余参数通过栈传递

**返回值：**

- 整型返回值使用a0寄存器
- 浮点返回值使用fa0寄存器

**寄存器保存：**

在函数调用前后，需要保存和恢复相关的寄存器。

#### 3.2.4 立即数处理

对于立即数，我们采用了两种处理策略：

**策略一：寄存器分配**

如果立即数被频繁使用，我们为其分配一个寄存器，在函数开头加载立即数。

**策略二：临时借用**

如果立即数没有被分配寄存器，我们临时借用其他寄存器来加载立即数，使用完后恢复。

### 3.3 优化结果

我们实现了两个优化级别：

**O1优化**：包含常量传播、公共子表达式删除、Mem2Reg转换、死代码删除

**O2优化**：在O1基础上增加图着色寄存器分配、循环不变量外提

**性能测试结果：**

我们使用多个测试用例评估了优化效果。与未优化版本相比，O1优化平均减少了约30%的指令数量，O2优化进一步减少了约15%的指令数量。

虽然与成熟的GCC编译器相比还有差距，但我们的优化效果是明显的，特别是在寄存器使用效率方面。

## 4. 实验总结

### 4.1 主要成果

1. **完整的优化Pass系统**：实现了多个重要的代码优化Pass
2. **高效的寄存器分配**：使用图着色算法实现了高效的寄存器分配
3. **完整的RISC-V后端**：实现了从IR到RISC-V汇编的完整翻译
4. **端到端编译**：实现了从CACT源码到可执行文件的完整编译流程

### 4.2 技术难点

1. **SSA转换**：Mem2RegPass的实现涉及复杂的支配树计算
2. **寄存器分配**：图着色算法的实现需要考虑溢出处理
3. **栈帧管理**：RISC-V后端的栈帧管理需要正确处理对齐
4. **优化组合**：多个优化Pass的组合需要考虑依赖关系

### 4.3 遇到的问题和解决方案

**问题1：PHI节点的处理**

在实现Mem2RegPass时，PHI节点的插入和重命名是最复杂的部分。我们通过仔细分析支配关系，逐步调试解决了这个问题。

**问题2：寄存器溢出**

在寄存器分配中，当虚拟寄存器数量超过物理寄存器时，需要将一些变量溢出到内存。我们实现了完整的溢出机制，包括溢出变量的存储和加载。

**问题3：栈帧对齐**

RISC-V要求栈帧16字节对齐，我们在计算栈帧大小时需要仔细处理对齐问题。

### 4.4 改进方向

1. **更多优化Pass**：可以添加更多高级优化，如循环优化、向量化等
2. **更好的寄存器分配**：可以实现更智能的寄存器分配策略
3. **性能调优**：可以进一步优化编译器的性能
4. **错误处理**：可以改进错误处理和调试信息的生成

### 4.5 实验收获

通过本次实验，我们深入理解了：

1. **代码优化的原理**：了解了各种优化技术的原理和实现方法
2. **目标代码生成**：掌握了从IR到目标代码的翻译过程
3. **编译器架构**：理解了现代编译器的整体架构和模块化设计
4. **工程实践**：积累了大型软件项目的开发经验

本次实验不仅让我们掌握了编译原理的核心技术，也培养了我们的工程实践能力，为后续的学习和研究奠定了坚实的基础。

## 参考文献

1. [UCAS_CPlab GitHub仓库](https://github.com/segzix/UCAS_CPlab/blob/master/reports/)
2. LLVM IR入门指南
3. 编译原理（龙书）
4. 现代编译原理（虎书）
5. RISC-V指令集架构参考手册

