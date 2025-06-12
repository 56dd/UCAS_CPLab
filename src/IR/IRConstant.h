#ifndef COMPILER_IRCONSTANT_H
#define COMPILER_IRCONSTANT_H


#include <any>
#include <map>

#include "IR/IRType.h"
#include "IRDerivedTypes.h"
#include "IRUser.h"
#include "utils/Register.h"

/******这里是一系列IRConstant的子类，如果往里面传入一个val值，那么可以直接获得一个IRConstant子类的静态对象******/
class IRConstant : public IRUser {
public:
    enum constType{
        normal = 0,
        init,
    };

protected:
    inline explicit IRConstant(IRType *Ty) : IRUser(Ty, IRValue::ConstantVal) {}
    constType constTy = normal;
    // Register* reg = nullptr;

public:
    static IRConstant *getNullValue(const IRType *Ty);
    static IRConstant *getAllOnesValue(const IRType *Ty);

    void print(std::ostream &OS) const override;
    void printPrefixName(std::ostream &OS) const override;
    bool jugdeZero(IRConstant* irconst) const;
    void zeroProcess(std::vector<IRConstant*>& zeroArray, std::ostream &OS) const;
    constType getConstTy() { return constTy; };

    // void setReg(Register* reg) { this->reg = reg; };

    // Register* getReg() { return reg; };

    static inline bool classof(IRConstant *) {return true;}

    static inline bool classof(IRValue *v) {
        return v->getValueType() == IRValue::ConstantVal;
    }
};

class IRConstantBool : public IRConstant {
    bool Val;

public:
    explicit IRConstantBool(bool V);

    /******静态的true和false对象******/
    static IRConstantBool *True, *False;// The True & False values

    /******IRConstantBool的get方法，通过判断给定的真实的bool值，返回一个IRConstant的对象******/
    static IRConstantBool *get(bool Value) { return Value ? True : False; }
    static IRConstantBool *get(const IRType *Ty, bool Value) { return get(Value); }

    /******IRConstantBool的judge方法，可以直接发挥一个true或false的IRConstant对象******/
    inline IRConstantBool *inverted() const { return (this == True) ? False : True; }

    inline bool getRawValue() const { return Val; }
};

class IRConstantInt : public IRConstant {
    int Val;
    static std::map<int, IRConstantInt *> constantMap;

protected:
    /******构造******/
    explicit IRConstantInt(int V);

public:
    static IRConstantInt *Null, *AllOnes;

    /**
     * 构造 IRConstantInt 的工厂方法，返回一个创建好的对象指针
     * @param V 常数的值
     * @return 创建好的对象的指针
     */
    static IRConstantInt *get(int V);

    /******返回val******/
    inline int getRawValue() const { return Val; }
};

class IRConstantFloat : public IRConstant {
    float Val;
    static std::map<float, IRConstantFloat *> constantMap;

protected:
    /******构造******/
    explicit IRConstantFloat(float V);

public:
    static IRConstantFloat *Null;

    /**
     * 构造 IRConstantFloat 的工厂方法，返回一个创建好的对象指针
     * @param V 常数的值
     * @return 创建好的对象的指针
     */
    static IRConstantFloat *get(float V);
    /******返回val******/
    inline float getRawValue() const { return Val; }
};

class IRConstantDouble : public IRConstant {
    double Val;
    static std::map<double, IRConstantDouble *> constantMap;

protected:
    /******构造******/
    explicit IRConstantDouble(double V);

public:
    static IRConstantDouble *Null;

    /**
     * 构造 IRConstantFloat 的工厂方法，返回一个创建好的对象指针
     * @param V 常数的值
     * @return 创建好的对象的指针
     */
    static IRConstantDouble *get(double V);
    /******返回val******/
    inline double getRawValue() const { return Val; }
};

class IRConstantinitializer : public IRConstant {
private:
    IRConstant* initconst;

    /*记录init size的大小*/
    unsigned initsize;

protected:

public:
    /******构造******/
    explicit IRConstantinitializer(unsigned size, IRConstant* val) : initsize(size), IRConstant(val->getType()) { 
        /*switch (val->getType()->getPrimitiveID()) {
            case IRType::IntTyID:
                initconst = IRConstantInt::get(dynamic_cast<IRConstantInt*>(val)->getRawValue());
                break;
            case IRType::FloatTyID:
                initconst = IRConstantInt::get(dynamic_cast<IRConstantFloat*>(val)->getRawValue());
                break;
            case IRType::DoubleTyID:
                initconst = IRConstantInt::get(dynamic_cast<IRConstantDouble*>(val)->getRawValue());
                break;
            case IRType::BoolTyID:
                initconst = IRConstantInt::get(dynamic_cast<IRConstantBool*>(val)->getRawValue());
                break;
        }*/
        initconst = val;
        constTy=init; 
    };

    inline unsigned getInitSize() const { return initsize; };

    /******返回内部的IRConstant******/
    inline IRConstant* getInitconst() const { return initconst; };
};

class IRConstantArray : public IRConstant {
    IRArrayType *arrayTy;
    unsigned zeroNum;

public:
    /******构造******/
    IRConstantArray(IRArrayType *ty, const std::vector<IRConstant *> &V);

    /******强转类型。上面的子类都是primitiveType，这里的类是arrayType，与globalvarible那里强转pointertype同理******/
    inline const IRArrayType *getType() const {
        return (IRArrayType *) IRValue::getType();
    }
    /******返回val******/
    inline const std::vector<IRUse> &getValues() const { return Operands; }
};


#endif//COMPILER_IRCONSTANT_H
