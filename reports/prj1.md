# 编译原理实验一：词法-语法分析

## 小组成员
朱徐塬、陈嘉康、楼云韬

## 1. 任务说明

本次实验实现了一个简单的CACT语言编译器前端，主要完成以下任务：

1. 根据CACT文法规范编写ANTLR文法文件（.g4），并通过ANTLR生成CACT源码的词法-语法分析器
2. 覆写ANTLR默认的文法错误处理机制，能检查出源码中的词法语法错误



## 2. 实验设计

### 2.1 编译器设计

本实验的主要代码包括：
- `CACT.g4`：ANTLR语法文件，定义了CACT语言的词法和语法规则
- `main.cpp`：主程序，实现编译器的驱动逻辑

### 2.2 ANTLR文法设计思路

CACT语言的文法设计基于以下思路：

1. **模块化设计**：
   - 将词法规则和语法规则清晰分离
   - 将语法规则按功能（表达式、语句、声明等）分组

2. **继承C语言风格**：
   - 保持与C语言类似的语法结构
   - 支持基本的C语言语法特性（函数、变量、控制流等）

3. **表达式优先级**：
   - 使用ANTLR的左递归特性实现表达式优先级
   - 确保运算符优先级与C语言一致

4. **错误处理**：
   - 实现自定义的错误监听机制
   - 提供清晰的错误信息

## 3. 实验实现

### 3.1 搭建ANTLR环境，运行demo

使用ANTLR工具生成visitor的C++代码：

```bash
java -jar ../deps/antlr-4.13.1-complete.jar -Dlanguage=Cpp CACT.g4 -visitor -no-listener
```

编译cact项目文件夹,在build目录下测试：

```bash
mkdir -p build
cd build
cmake ..
make
./compiler
```

### 3.2 CACT.g4文件实现

CACT.g4文件定义了CACT语言的词法和语法规则：

#### 3.2.1 语法规则部分

语法规则定义了CACT语言的程序结构，包括：

- 编译单元（compilationUnit）作为起始规则
- 函数定义和声明
- 各种类型的语句（if-else、while、return等）
- 表达式及其优先级
- 变量声明和初始化

#### 3.2.2 词法规则部分

词法规则定义了CACT语言的词法单元，包括：

- 关键字（if、else、while等）
- 标识符
- 各种常量（整数、浮点数、字符）
- 运算符和分隔符
- 空白字符和注释的处理

### 3.3 main.cpp实现

main.cpp是编译器的主程序，实现了以下功能：

1. 命令行参数处理：接收源文件路径
2. 建立编译管道：
   - 创建输入流
   - 初始化词法分析器
   - 初始化语法分析器
3. 语法分析：调用parser.compilationUnit()进行分析
4. 错误处理：检查词法和语法错误
5. 结果输出：输出分析结果（成功或失败）

### 3.4 错误处理实现

错误处理通过以下方式实现：

```cpp
int flag = 1;

if (lexer.getNumberOfSyntaxErrors() > 0) {
    std::cout << "lex error: " << lexer.getNumberOfSyntaxErrors() << std::endl;
    flag = 0;
}

if (parser.getNumberOfSyntaxErrors() > 0) {
    std::cout << "syntax error: " << parser.getNumberOfSyntaxErrors() << std::endl;
    flag = 0;
}

if (flag)
    std::cout << "true" << std::endl;
else
    std::cout << "false" << std::endl;
```

### 3.5 使用ANTLR工具，根据语法描述文件，生成词法分析器、语法分析器等模块

运行CMake项目gen_files_form_g4：

```bash
# 进入grammar目录
cd grammar

# 使用ANTLR生成C++代码
java -jar ../deps/antlr-4.13.1-complete.jar -Dlanguage=Cpp CACT.g4 -visitor -no-listener

# 检查生成的文件
ls -la CACT*.{cpp,h}

# 输出文件列表和大小信息
du -sh CACT*.{cpp,h}

# 回到项目根目录
cd ..
```

### 3.6 运行cmake project，编译源代码，生成可执行的compiler文件

```bash
mkdir -p build
cd build
cmake ..
make -j
```

### 3.7 在测试用例上运行compiler，并根据测试结果修改bug

通过在测试用例上运行编译器，我们可以验证语法定义的正确性，并根据测试结果不断调整和优化语法规则。例如，我们发现了一些常见的错误模式：

#### 3.7.1 十六进制数字格式错误（如0x后没有数字）

在测试用例`01_false_hex_num.cact`中，我们发现了十六进制数字格式错误问题：

```c
int main()
{
    int a = 0x;    // 错误：十六进制常量后没有数字
    return a;
}
```

这个问题出现的原因是CACT.g4中对十六进制数字的定义不够严格：

```antlr
fragment HexadecimalConstant
    : '0'[xX][0-9a-fA-F]+
    ;
```

当源代码中出现`0x`后没有跟数字时，词法分析器无法识别它作为一个完整的十六进制常量，因此产生错误。解决方法是确保十六进制常量规则要求至少一个十六进制数字，并在词法分析器中添加适当的错误处理。

编译器正确识别出了这个错误，输出：
```
line 3:13 extraneous input 'x' expecting {';', ','}
syntax error: 1
false
```

#### 3.7.2 字符常量定义不规范

在测试字符常量定义时，我们发现了一些不规范的用法，例如在`char_test_error.cact`中：

```c
char c1 = '';       // 错误：空字符常量
char c2 = 'ab';     // 错误：多字符常量
char c3 = 'a;       // 错误：未闭合的字符常量
char c4 = '\k';     // 错误：非法转义序列
```

CACT语言中字符常量的定义如下：

```antlr
CharacterConstant
    : '\'' (EscapeSequence | ~['\\\r\n]) '\''
    ;

fragment EscapeSequence
    : '\\' [btnvrfa\\'"?]
    | '\\' OctalDigit+
    | '\\x' HexadecimalDigit+
    ;
```

这些规则要求字符常量必须：
1. 由单引号括起来
2. 包含且仅包含一个字符或转义序列
3. 转义序列必须是有效的（如\n, \t等）

针对这些错误，编译器能够正确地识别并报告问题：
```
line 3:14 token recognition error at: ''''
line 6:14 token recognition error at: ''ab''
line 9:14 token recognition error at: ''a;'
line 12:14 token recognition error at: ''\k''
```

#### 3.7.3 嵌套注释处理问题

嵌套注释是指在一个注释块内部包含另一个注释块的情况。在测试用例`13_false_nested_comment.cact`中：

```c
int main()
{
    int a[10];
    int i = 3;
    /*  
    /*
        False nested comment
    */
    */
    return i;
}
```

CACT语言的块注释定义如下：

```antlr
CommentBlock
    : '/*' .*? '*/' -> channel(HIDDEN)
    ;
```

这种定义方式不支持嵌套注释，因为：
1. 使用贪婪匹配模式`.*?`，它会匹配最近的`*/`作为注释结束
2. 当遇到内层注释的结束标记`*/`时，整个注释块被认为是结束的
3. 导致外层注释的剩余部分，包括第二个`*/`被错误地视为普通代码

编译器在运行此测试用例时报告错误：
```
line 9:1 mismatched input '*' expecting '}'
syntax error: 1
false
```

这表明在第9行的`*`被视为普通代码而不是注释的一部分，因此产生了语法错误。

为了解决这个问题，有两种方法：
1. **明确禁止嵌套注释**：在语言规范中明确指出不允许嵌套注释
2. **支持嵌套注释**：修改词法规则，使用递归方式处理嵌套注释，例如：
   ```antlr
   CommentBlock
       : '/*' (CommentBlock | .)*? '*/' -> channel(HIDDEN)
       ;
   ```

在当前的CACT实现中，我们选择了第一种方法，明确不支持嵌套注释，将其视为语法错误。这是一种设计决策，与C语言的处理方式一致。

## 4. 问题思考

### 4.1 如何设计编译器的目录结构？

本编译器采用了以下目录结构：

```
cact/
├── CMakeLists.txt         # CMake构建文件
├── README.md              # 项目说明
├── build/                 # 构建产物目录
│   └── compiler           # 编译好的可执行文件
├── deps/                  # 外部依赖
│   └── antlr4-runtime/    # ANTLR4运行时库
├── grammar/               # 语法定义和ANTLR生成的代码
│   ├── CACT.g4            # CACT语言语法文件
│   └── ...                # ANTLR生成的词法语法分析器代码
├── reports/               # 实验报告
│   └── prj1.md            # 本实验报告
├── src/                   # 源代码
│   └── main.cpp           # 主程序
└── test/                  # 测试用例
    └── samples_lex_and_syntax/ # 词法语法测试样例
```

这种目录结构具有以下优点：
1. **职责分离**：将语法定义、源代码、构建产物、测试用例等不同功能的文件分开存放
2. **易于维护**：各模块独立，方便后续扩展和维护
3. **构建清晰**：使用CMake进行构建，能够方便地管理依赖关系

1. **模块化**：将不同功能的代码分离到不同目录，如词法分析、语法分析、语义分析等
2. **可扩展性**：结构设计应便于后续添加新功能
3. **构建系统**：采用合适的构建系统（如CMake）管理项目依赖和构建过程
4. **测试框架**：包含专门的测试目录和测试框架
5. **文档**：包含文档目录，存放设计文档、API文档等

本项目采用的目录结构遵循了这些原则，将语法定义、源代码、构建产物等分离，便于维护和扩展。

### 4.2 如何把表达式优先级体现在文法设计中？

在ANTLR4中，表达式优先级主要通过以下方式体现：

1. **使用左递归**：ANTLR4支持直接使用左递归来定义表达式优先级

```antlr
// 从低优先级到高优先级
expression
    : logicalOrExpression
    ;

logicalOrExpression
    : logicalAndExpression (op='||' logicalAndExpression)*
    ;

logicalAndExpression
    : equalityExpression (op='&&' equalityExpression)*
    ;

// 更多表达式规则...
```

2. **操作符优先级**：通过嵌套规则定义优先级，越底层的规则优先级越高

这种方式的优点是：
- 文法清晰易读
- 与数学表达式的优先级自然对应
- 避免了使用ANTLR的显式优先级标记（如^）
- 生成的语法树结构与优先级一致

### 4.3 如何设计数值常量的词法规则？

CACT语言中数值常量主要包括整数常量和浮点数常量，设计思路如下：

1. **整数常量**：支持十进制、八进制、十六进制
```antlr
IntegerConstant
    : DecimalConstant
    | OctalConstant
    | HexadecimalConstant
    ;

fragment DecimalConstant
    : [1-9][0-9]*
    ;

fragment OctalConstant
    : '0'[0-7]*
    ;

fragment HexadecimalConstant
    : '0'[xX][0-9a-fA-F]+
    ;
```

2. **浮点数常量**：支持小数形式和科学计数法
```antlr
FloatingConstant
    : FractionalConstant ExponentPart? FloatingSuffix?
    | DigitSequence ExponentPart FloatingSuffix?
    ;

fragment FractionalConstant
    : DigitSequence? '.' DigitSequence
    | DigitSequence '.'
    ;

fragment ExponentPart
    : [eE] [+-]? DigitSequence
    ;

fragment DigitSequence
    : [0-9]+
    ;

fragment FloatingSuffix
    : [flFL]
    ;
```

这种设计的特点是：
- 使用fragment规则降低复杂度，提高可读性
- 支持多种表示形式，增强语言表达能力
- 与C语言风格保持一致，降低学习成本

### 4.4 如何替换ANTLR的默认异常处理方法？

ANTLR默认的异常处理机制可以通过以下方式替换：

1. **实现自定义错误监听器**：继承BaseErrorListener类
```cpp
class CACTErrorListener : public antlr4::BaseErrorListener {
public:
    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol,
                    size_t line, size_t charPositionInLine,
                    const std::string &msg, std::exception_ptr e) override {
        // 自定义错误处理逻辑
        std::cerr << "Error at line " << line << ":" << charPositionInLine
                << " - " << msg << std::endl;
    }
};
```

2. **注册错误监听器**：将自定义监听器添加到lexer和parser
```cpp
CACTErrorListener errorListener;
lexer.removeErrorListeners();  // 移除默认监听器
lexer.addErrorListener(&errorListener);
parser.removeErrorListeners();
parser.addErrorListener(&errorListener);
```

3. **错误恢复策略**：通过BailErrorStrategy可以在遇到第一个错误时立即停止
```cpp
parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());
```

在当前实现中，我们通过检查lexer和parser的错误计数来判断分析是否成功，这是一种简单但有效的错误处理方式。

### 4.5 了解ANTLR工具生成词法-语法源码的能力

ANTLR（ANother Tool for Language Recognition）是一个强大的语言识别工具，能够自动生成词法分析器和语法分析器。它具有以下核心能力：

1. **自动生成代码**：
   - 从单一语法文件（.g4）自动生成词法分析器和语法分析器
   - 支持多种目标语言，如Java、C++、Python、JavaScript等
   - 生成的代码易于集成到现有项目中

2. **强大的语法表达能力**：
   - 支持正则表达式语法来定义词法规则
   - 支持上下文无关文法（Context-Free Grammar）来定义语法规则
   - 支持左递归表达式，使文法更加直观
   - 提供语义谓词（Semantic Predicates）支持，增强语法表达能力

3. **高级语法分析特性**：
   - 自动生成抽象语法树（AST）
   - 提供访问者（Visitor）和监听器（Listener）两种遍历模式
   - 内置错误恢复机制
   - 支持规则参数化和回调

4. **开发工具支持**：
   - 提供语法调试工具
   - 可视化语法树生成
   - 代码高亮和自动完成（通过IDE插件）

在我们的CACT编译器中，利用ANTLR的这些能力，只需编写一个CACT.g4文件，就能自动生成完整的词法分析器和语法分析器，大大简化了编译器前端的开发工作。

### 4.6 掌握ANTLR生成lexer和parser的流程

ANTLR从g4文件生成词法分析器和语法分析器的流程如下：

1. **语法文件编写**：
   - 创建.g4文件，定义语言的词法和语法规则
   - 可以在一个文件中同时定义词法和语法（如我们的CACT.g4）
   - 也可以分别创建Lexer.g4和Parser.g4文件分开定义

2. **ANTLR处理流程**：
   - **语法分析阶段**：ANTLR工具首先分析g4文件，检查语法规则的有效性
   - **内部表示生成**：将语法规则转换为内部表示形式，如ATN（Augmented Transition Networks）
   - **语法优化**：对语法进行优化，如消除左递归、避免回溯等
   - **代码生成**：根据目标语言生成对应的词法分析器和语法分析器代码

3. **生成的主要文件**（以C++为例）：
   - **词法分析器文件**：
     - `CACTLexer.h` 和 `CACTLexer.cpp`：包含词法分析器的定义和实现
     - `CACTLexer.tokens`：包含词法单元的标识符和对应的数字ID

   - **语法分析器文件**：
     - `CACTParser.h` 和 `CACTParser.cpp`：包含语法分析器的定义和实现
     - `CACT.tokens`：包含所有词法单元的标识符和数字ID映射

   - **访问者模式文件**（当使用-visitor选项）：
     - `CACTVisitor.h` 和 `CACTVisitor.cpp`：定义访问者接口
     - `CACTBaseVisitor.h` 和 `CACTBaseVisitor.cpp`：提供默认访问者实现

   - **监听器模式文件**（当使用-listener选项）：
     - `CACTListener.h` 和 `CACTListener.cpp`：定义监听器接口
     - `CACTBaseListener.h` 和 `CACTBaseListener.cpp`：提供默认监听器实现

4. **编译和集成**：
   - 将生成的源代码编译为目标库或可执行文件
   - 集成到项目中，构建完整的编译管道

5. **使用生成的分析器**：
   - 创建输入流，如`ANTLRInputStream`
   - 初始化词法分析器，输入字符流，生成词法单元流
   - 初始化语法分析器，分析词法单元流，构建语法树
   - 使用访问者或监听器遍历语法树，执行所需的处理

在本项目中，我们使用`-visitor -no-listener`选项生成代码，这意味着我们选择使用访问者模式而不是监听器模式来处理语法树。访问者模式提供了更大的灵活性，使我们能够更精细地控制语法树的遍历过程，更适合后续的语义分析和代码生成阶段。

## 5. 总结和实验结果

### 5.1 实验总结

通过本次实验，我们成功实现了CACT语言的词法-语法分析器，主要成果包括：

1. 完成了CACT语言的语法定义文件（CACT.g4）
2. 实现了编译器前端的基本框架
3. 能够正确分析CACT语言的源程序
4. 能够识别词法和语法错误

### 5.2 实验结果

我们通过测试用例验证了编译器的功能：

1. **正确用例测试**：编译器能够正确分析符合CACT语法的程序
   - 基本函数定义
   - 变量声明和初始化
   - 控制流语句（if-else、while）
   - 各种类型的表达式

2. **错误用例测试**：编译器能够检测出各种词法和语法错误
   - 非法标识符
   - 非法数值常量（如0x）
   - 未闭合的括号或引号
   - 错误的语法结构

### 5.3 后续改进

尽管本次实验已经实现了基本功能，但仍有以下改进空间：

1. 错误信息可以更加详细和友好
2. 可以实现更好的错误恢复机制
3. 可以添加语义分析功能
4. 可以增强语法树的可视化，便于调试

通过这些改进，可以进一步提升编译器的功能和用户体验。 