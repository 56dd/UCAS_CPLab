# UCAS_CPLab_CACT

中国科学院大学2022届编译原理研讨课仓库（陈嘉康，楼云韬，朱徐塬）

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
