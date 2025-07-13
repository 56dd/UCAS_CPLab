#ifndef COMPILER_GLOBALVARIABLE_H
#define COMPILER_GLOBALVARIABLE_H

#include "Environment.h"
#include <iostream>

class IRType;

class IRConstant;

class IRGlobalVariable;

namespace RISCV {

    class Module;

    class GlobalVariable {
    public:
        explicit GlobalVariable(IRGlobalVariable *irGV, Module *module = nullptr);

        GlobalVariable(IRConstant *irConstant, Module *module);

        IRGlobalVariable *getIrGv() const;

        std::string getSectionName();

        void print(std::ostream &O);

        const std::string &getName() const;

    private:
        std::string name;
        Section section;
        unsigned align = 3;
        unsigned size;
        IRGlobalVariable *irGV;
        IRConstant *initializer;

        void printInitVal(std::ostream &O);

        static void printType(std::ostream &O, IRType *type);

        static void printVal(std::ostream &O, IRConstant *val);
    };

} // RISCV

#endif //COMPILER_GLOBALVARIABLE_H
