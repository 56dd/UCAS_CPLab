#include <iostream>
#include <ostream>

#include "IR/IRModule.h"
#include "FrontEnd.h"
#include "Optimizer.h"
#include "BackEnd.h"
#include "Interpreter/Interpreter.h"
#include "utils/CLParser.h"

using namespace antlr4;

int main(int argc, const char *argv[]) {
    CLParser parser;
    parser.add("simulate");
    parser.add("verbose");
    parser.add("c");
    parser.add("emit-IR");
    parser.parse(argc, argv);

    /*读取输入cact文件*/
    std::string file(parser.getFilePath());
    std::ifstream stream;
    stream.open(file);

    /*文件不存在则报错*/
    if (!stream.is_open()) {
        std::cerr << "Error: Fail to open " << file << std::endl;
        return 1;
    }

    /*遍历语法树，生成无优化IR代码*/
    IRModule ir(file);
    FrontEnd frontEnd(&stream, &ir);

    try {
        frontEnd.analyze();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    /*对IR代码进行优化；opt建立，划定优先级，根据优先级跑优化pass*/
    Optimizer opt(&ir);
    opt.build();
    opt.setLevel(parser.getLevel());
    opt.run();

    /*打印优化之后的IR代码*/
    if (parser.get("emit-IR"))
        frontEnd.print();

    /*解释执行或者直接生成RISCV代码*/
    Interpreter ip(&ir);
    Interpreter::debugOpt = parser.get("verbose");
    if (parser.get("simulate") || parser.get("verbose")) {
        int ret = ip.interpret();
        if (parser.get("c"))
            printf("inst_cnt = %d\n", Interpreter::getInstCnt());
        return ret;
    } else {
        BackEnd backEnd(&ir);
        backEnd.print();
    }

    return 0;
}