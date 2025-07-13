#ifndef COMPILER_BACKEND_H
#define COMPILER_BACKEND_H

#include "RISC-V/Module.h"

class IRModule;

class BackEnd {
public:
    explicit BackEnd(IRModule *ir);

    void print();

private:
    IRModule *ir;

    RISCV::Module module;

    void internalPrint(std::ostream &O, const std::string &srcFileName);

    static void printFileName(std::ostream &ostream, const std::string &srcFileName);

    static void printEnv(std::ostream &O);
};


#endif //COMPILER_BACKEND_H
