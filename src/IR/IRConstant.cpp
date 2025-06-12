#include "IRConstant.h"

#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define initThreshold 10000

IRConstantBool::IRConstantBool(bool V) : IRConstant(IRType::BoolTy) {
    Val = V;
}

IRConstantBool *IRConstantBool::True = new IRConstantBool(true);
IRConstantBool *IRConstantBool::False = new IRConstantBool(false);
IRConstantInt *IRConstantInt::Null = new IRConstantInt(0);
IRConstantInt *IRConstantInt::AllOnes = new IRConstantInt(-1);
IRConstantFloat *IRConstantFloat::Null = new IRConstantFloat(0);
IRConstantDouble *IRConstantDouble::Null = new IRConstantDouble(0);

std::map<int, IRConstantInt *> IRConstantInt::constantMap;
std::map<float, IRConstantFloat *> IRConstantFloat::constantMap;
std::map<double, IRConstantDouble *> IRConstantDouble::constantMap;

bool IRConstant::jugdeZero(IRConstant* irconst) const {
    /******根据IRConstant中的type类型来打印出它的value值******/
    switch (irconst->getType()->getPrimitiveID()) {
        case IRType::IntTyID:
            return dynamic_cast<const IRConstantInt *>(irconst)->getRawValue() == 0;
        case IRType::FloatTyID:
            return dynamic_cast<const IRConstantFloat *>(irconst)->getRawValue() == 0;
        case IRType::DoubleTyID:
            return dynamic_cast<const IRConstantDouble *>(irconst)->getRawValue() == 0;
        case IRType::BoolTyID:
            return dynamic_cast<const IRConstantBool *>(irconst)->getRawValue() == false;
    }
}

void IRConstant::printPrefixName(std::ostream &OS) const {
    /******根据IRConstant中的type类型来打印出它的value值******/
    switch (this->getType()->getPrimitiveID()) {
        case IRType::IntTyID:
            OS << dynamic_cast<const IRConstantInt *>(this)->getRawValue();
            break;
        case IRType::FloatTyID:
            OS << dynamic_cast<const IRConstantFloat *>(this)->getRawValue();
            break;
        case IRType::DoubleTyID:
            OS << dynamic_cast<const IRConstantDouble *>(this)->getRawValue();
            break;
        case IRType::BoolTyID:
            OS << std::boolalpha << dynamic_cast<const IRConstantBool *>(this)->getRawValue();
            break;
        case IRType::ArrayTyID:
            OS << "[";
            for(auto iruse: dynamic_cast<const IRConstantArray *>(this)->getValues()){
                dynamic_cast<IRConstant*>(iruse.get())->print(OS);
                OS << ", ";
            }

            // 回退2个字符
            OS.seekp(static_cast<std::streampos>(static_cast<std::streamoff>(OS.tellp()) - 2));
            OS << "]";
    }
}

void IRConstant::print(std::ostream &OS) const {
    switch (constTy) {
        case normal:
            this->getType()->print(OS);
            this->printPrefixName(OS);
            break;
        case init:
            dynamic_cast<const IRConstantinitializer*>(this)->getInitconst()->getType()->print(OS);
            dynamic_cast<const IRConstantinitializer*>(this)->getInitconst()->printPrefixName(OS);
            OS << "(initialize size: " << dynamic_cast<const IRConstantinitializer*>(this)->getInitSize() << ")";
    }
}

IRConstant *IRConstant::getNullValue(const IRType *Ty) {
    switch (Ty->getPrimitiveID()) {
        case IRType::IntTyID:
            return IRConstantInt::Null;
        case IRType::FloatTyID:
            return IRConstantFloat::Null;
        case IRType::DoubleTyID:
            return IRConstantDouble::Null;
        case IRType::BoolTyID:
            return IRConstantBool::False;
    }
    return nullptr;
}
IRConstant *IRConstant::getAllOnesValue(const IRType *Ty) {
    switch (Ty->getPrimitiveID()) {
        case IRType::IntTyID:
            return IRConstantInt::AllOnes;
        case IRType::BoolTyID:
            return IRConstantBool::True;
    }
    return nullptr;
}

IRConstantInt::IRConstantInt(int V) : IRConstant(IRType::IntTy) {
    Val = V;
}

IRConstantInt *IRConstantInt::get(int V) {
    if (V == 0) {
        return IRConstantInt::Null;
    } else if (V == -1) {
        return IRConstantInt::AllOnes;
    } else if (auto ret = constantMap[V]) {
        return ret;
    } else {
        ret = new IRConstantInt(V);
        constantMap[V] = ret;
        return ret;
    }
}

IRConstantFloat::IRConstantFloat(float V) : IRConstant(IRType::FloatTy) {
    Val = V;
}
IRConstantFloat *IRConstantFloat::get(float V) {
    if (V == 0) {
        return IRConstantFloat::Null;
    } else if (auto ret = constantMap[V]) {
        return ret;
    } else {
        ret = new IRConstantFloat(V);
        constantMap[V] = ret;
        return ret;
    }
}

IRConstantDouble::IRConstantDouble(double V) : IRConstant(IRType::DoubleTy) {
    Val = V;
}
IRConstantDouble *IRConstantDouble::get(double V) {
    if (V == 0) {
        return IRConstantDouble::Null;
    } else if (auto ret = constantMap[V]) {
        return ret;
    } else {
        ret = new IRConstantDouble(V);
        constantMap[V] = ret;
        return ret;
    }
}

IRConstantArray::IRConstantArray(IRArrayType *ty, const std::vector<IRConstant *> &V)
    : IRConstant(dynamic_cast<IRType *>(ty)) {
    arrayTy = ty;
    if(V.size() > initThreshold){
        /*从末尾开始数，看连续的const有多少个*/
        auto constNum = V.back();
        unsigned initsize = 0;
        for (auto Vit = V.rbegin(); Vit != V.rend(); ++Vit) {
            if(*Vit != constNum)
                break;
            initsize++;
        }

        /*从头开始向operands中间压值，最后一个压initializer*/
        for(unsigned i=0; i<V.size()-initsize; i++){
            Operands.emplace_back(V[i], this);
        }
        auto irinit = new IRConstantinitializer(initsize, constNum);
        Operands.emplace_back(irinit,this);

    }else{
        for (auto val: V) {
            Operands.emplace_back(val, this);
        }
    }
}
