#ifndef COMPILER_REGISTER_H
#define COMPILER_REGISTER_H

#include "IR/IRValue.h"
#include <vector>
#include <string>
#include <iostream>
#include <cassert>

#define GPRCallerSavedNUM 7
#define GPRCalleeSavedNUM 12
#define GPRPARAMNUM 8
#define FPRCallerSavedNUM 12
#define FPRCalleeSavedNUM 12
#define FPRPARAMNUM 8

#define GPRNUM GPRCallerSavedNUM+GPRCalleeSavedNUM+GPRPARAMNUM
#define FPRNUM FPRCallerSavedNUM+FPRCalleeSavedNUM+FPRPARAMNUM

class RegisterNode;

class IRFunction;

class IRInstruction;

class Register {
public:
    enum RegTy {
        CallerSaved,            //t系列寄存器
        CalleeSaved,            //s系列寄存器
        Param,                  //a系列寄存器
        FloatCallerSaved,       //ft系列寄存器
        FloatCalleeSaved,       //fs系列寄存器
        FloatParam,             //fa系列寄存器
    };

protected:
    unsigned regNum;    //系列中寄存器的编号
    unsigned regSeq;    //所有寄存器中的编号
    std::string regName;//寄存器的名字
    RegTy regty;     //寄存器的类型
    RegisterNode *regNode;

public:

    /*获得reg系列及其编号*/
    virtual const std::string &getRegName() = 0;

    /*获得在所有reg中的序号*/
    virtual unsigned getRegSeq() = 0;

    /*获得reg中的类型*/
    virtual RegTy getRegty() = 0;

    RegisterNode *getRegNode() { return regNode; };
};

class ZeroRegister : public Register {
public:

    explicit ZeroRegister(std::string name);

    static ZeroRegister *zero;

    const std::string &getRegName() override { return regName; };

    unsigned getRegSeq() override { return regSeq; };

    RegTy getRegty() override { return regty; };
};

class CallerSavedRegister : public Register {
private:
    static std::vector<CallerSavedRegister *> CallerSavedvec;
    static const unsigned RegMAXNum = GPRCallerSavedNUM;

public:

    static CallerSavedRegister *ra;

    explicit CallerSavedRegister(std::string name);

    explicit CallerSavedRegister(unsigned num);

    /*初始化静态reg对象，并获得静态reg对象List*/
    static void initTreg() {
        if (CallerSavedvec.empty()) {
            for (unsigned i = 0; i < RegMAXNum; i++) {
                CallerSavedvec.push_back(new CallerSavedRegister(i));
            }
        }
    }

    static std::vector<CallerSavedRegister *> &getTregList() {
        return CallerSavedvec;
    }

    /*获得reg属性*/
    const std::string &getRegName() { return regName; };

    unsigned getRegSeq() { return regSeq; };

    RegTy getRegty() { return regty; };

    static CallerSavedRegister *Num2Reg(unsigned int num);
};

class CalleeSavedRegister : public Register {
private:
    static std::vector<CalleeSavedRegister *> CalleeSavedvec;
    static const unsigned RegMAXNum = GPRCalleeSavedNUM;

public:

    static CalleeSavedRegister *sp;

    explicit CalleeSavedRegister(std::string name);

    explicit CalleeSavedRegister(unsigned num);


    /*初始化静态reg对象，并获得静态reg对象List*/
    static void initSreg() {
        if (CalleeSavedvec.empty()) {
            for (unsigned i = 0; i < RegMAXNum; i++) {
                CalleeSavedvec.push_back(new CalleeSavedRegister(i));
            }
        }
    }

    static std::vector<CalleeSavedRegister *> &getSregList() {
        return CalleeSavedvec;
    }

    /*获得reg属性*/
    const std::string &getRegName() { return regName; };

    unsigned getRegSeq() { return regSeq; };

    RegTy getRegty() { return regty; };

    static CalleeSavedRegister *Num2Reg(unsigned int num);
};



class ParamRegister : public Register {
private:
    static std::vector<ParamRegister *> Paramvec;
    static const unsigned RegMAXNum = GPRPARAMNUM;

public:
    explicit ParamRegister(unsigned num);

    /*初始化静态reg对象，并获得静态reg对象List*/
    static void initAreg() {
        if (Paramvec.empty()) {
            for (unsigned i = 0; i < RegMAXNum; i++) {
                Paramvec.push_back(new ParamRegister(i));
            }
        }
    }

    static std::vector<ParamRegister *> &getAregList() {
        return Paramvec;
    }

    /*获得reg属性*/
    const std::string &getRegName() { return regName; };

    unsigned getRegSeq() { return regSeq; };

    RegTy getRegty() { return regty; };

    static ParamRegister *Num2Reg(unsigned int num);
};

class FloatCallerSavedRegister : public Register {
private:
    static std::vector<FloatCallerSavedRegister *> FloatCallerSavedvec;
    static const unsigned RegMAXNum = FPRCallerSavedNUM;

public:
    explicit FloatCallerSavedRegister(unsigned num);

    /*初始化静态reg对象，并获得静态reg对象List*/
    static void initFTreg() {
        if (FloatCallerSavedvec.empty()) {
            for (unsigned i = 0; i < RegMAXNum; i++) {
                FloatCallerSavedvec.push_back(new FloatCallerSavedRegister(i));
            }
        }
    }

    static std::vector<FloatCallerSavedRegister *> &getFTregList() {
        return FloatCallerSavedvec;
    }

    /*获得reg属性*/
    const std::string &getRegName() { return regName; };

    unsigned getRegSeq() { return regSeq; };

    RegTy getRegty() { return regty; };

    FloatCallerSavedRegister *Num2Reg(unsigned int num);

};

class FloatCalleeSavedRegister : public Register {
private:
    static std::vector<FloatCalleeSavedRegister *> FloatCalleeSavedvec;
    static const unsigned RegMAXNum = FPRCalleeSavedNUM;

public:
    explicit FloatCalleeSavedRegister(unsigned num);

    /*初始化静态reg对象，并获得静态reg对象List*/
    static void initFSreg() {
        if (FloatCalleeSavedvec.empty()) {
            for (unsigned i = 0; i < RegMAXNum; i++) {
                FloatCalleeSavedvec.push_back(new FloatCalleeSavedRegister(i));
            }
        }
    }

    static std::vector<FloatCalleeSavedRegister *> &getFSregList() {
        return FloatCalleeSavedvec;
    }

    /*获得reg属性*/
    const std::string &getRegName() { return regName; };

    unsigned getRegSeq() { return regSeq; };

    RegTy getRegty() { return regty; };

    static FloatCalleeSavedRegister *Num2Reg(unsigned int num);
};

class FloatParamRegister : public Register {
private:
    static std::vector<FloatParamRegister *> FloatParamvec;
    static const unsigned RegMAXNum = FPRPARAMNUM;

public:
    explicit FloatParamRegister(unsigned num);

    /*初始化静态reg对象，并获得静态reg对象List*/
    static void initFAreg() {
        if (FloatParamvec.empty()) {
            for (unsigned i = 0; i < RegMAXNum; i++) {
                FloatParamvec.push_back(new FloatParamRegister(i));
            }
        }
    }

    static std::vector<FloatParamRegister *> &getFAregList() {
        return FloatParamvec;
    }

    /*获得reg属性*/
    const std::string &getRegName() { return regName; };

    unsigned getRegSeq() { return regSeq; };

    RegTy getRegty() { return regty; };

    static FloatParamRegister *Num2Reg(unsigned int num);
};

class RegisterFactory {
private:
    static std::vector<Register *> GeneralRegList;
    static std::vector<Register *> FloatRegList;

public:

    /*初始化所有静态reg对象*/
    static void initGReg();

    /*初始化所有静态reg对象*/
    static void initFReg();

    /*获得所有静态reg对象List*/
    static std::vector<Register *> &getGRegList() {
        return GeneralRegList;
    }

    static std::vector<Register *> &getFRegList() {
        return FloatRegList;
    }

    static Register *getReg(std::string name) {
        for (auto reg : GeneralRegList) {
            if (reg->getRegName() == name)
                return reg;
        }
        for (auto reg : FloatRegList) {
            if (reg->getRegName() == name)
                return reg;
        }
        assert(0 && "wrong reg name");
    }

    static void print(std::ostream &OS, IRFunction &F);

    static void printInst(std::ostream& OS, IRInstruction& inst);

    static void check(IRFunction &F);
};

#endif //COMPILER_REGISTER_H