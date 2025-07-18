# UCAS_CPLab_CACT

中国科学院大学2022届编译原理研讨课仓库（陈嘉康，楼云韬，朱徐塬）

第9组

# CACT compiler skeleton

## using antlr4 to generate files from grammar file

```bash
java -jar ../deps/antlr-4.13.1-complete.jar -Dlanguage=Cpp CACT.g4 -visitor -no-listener
```

## compile the cmake project

```bash
mkdir -p build
cd build
cmake ..
make -j
./compiler ../test/samples_lex_and_syntax/00_true_main.cact
```

## 运行方法

1. 编译与测试：

```bash
./test_compiler.sh
```

2. 批量编译并运行所有生成的RISC-V汇编代码：

```bash
./run_assembly.sh
```

- 所有生成的RISC-V汇编文件和可执行文件均位于 `Codegencases-main/functional/` 目录下。
- `run_assembly.sh` 会自动编译该目录下所有 `.s` 文件并运行，输出结果和退出码。
