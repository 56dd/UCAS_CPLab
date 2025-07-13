//
// Created by yuanjunkang on 24-5-5.
//

#include "TemporaryVariable.h"


const std::any &TemporaryVariable::getValue() const {
    return value;
}

TemporaryVariable::tempVarType TemporaryVariable::getType() const {
    return type;
}

void TemporaryVariable::setValue(const std::any &value) {
    TemporaryVariable::value = value;
}

void TemporaryVariable::setType(TemporaryVariable::tempVarType type) {
    TemporaryVariable::type = type;
}

TemporaryVariable::TemporaryVariable(std::any value, TemporaryVariable::tempVarType type,
                                     TemporaryVariable::tempVarType elementType, unsigned long arraySize) :
                                     value(std::move(value)), type(type), elementType(elementType), arraySize(arraySize){}

std::string TemporaryVariable::getTypeString(tempVarType ty) {
    switch (ty) {
        case Func:
            return "Func";
        case Int:
            return "Int";
        case Float:
            return "Float";
        case Double:
            return "Double";
        case Bool:
            return "Bool";
        case Void:
            return "Void";
        case Pointer:
            return "Pointer";
        default:
            return "Unknown";
    }
}

void TemporaryVariable::print() {
    auto ty = getType();
    printf("Temporary Variable Type = ");
    std::cout << getTypeString(ty);
    printf(" , value = ");
    switch (ty) {
        case Bool:{
            printf("%d", std::any_cast<bool>(getValue()));
            break;
        }
        case Int:{
            printf("%d", std::any_cast<int>(getValue()));
            break;
        }
        case Float:{
            printf("%f", std::any_cast<float>(getValue()));
            break;
        }
        case Double:{
            printf("%lf", std::any_cast<double>(getValue()));
            break;
        }
        case Pointer:{
            printf("%lu", std::any_cast<unsigned long>(getValue()));
            printf(", Element Type = ");
            std::cout << getTypeString(elementType);
            printf(", Array Size = ");
            printf("%d", arraySize);
            break;
        }
        default:{
            printf("NULL");
        }
    }
    puts("");
}

unsigned long TemporaryVariable::getTypeSize(TemporaryVariable::tempVarType ty) {
    switch (ty) {
        case Bool :     return 1;
        case Int :      return 4;
        case Float :    return 4;
        case Double :   return 8;
        case Pointer:   return 8;
        default :       return 0;
    }
}

TemporaryVariable::tempVarType TemporaryVariable::getElementType() const {
    return elementType;
}

void TemporaryVariable::setElementType(TemporaryVariable::tempVarType elementType) {
    TemporaryVariable::elementType = elementType;
}

unsigned long TemporaryVariable::getArraySize() const {
    return arraySize;
}

void TemporaryVariable::setArraySize(unsigned long  arraySize) {
    TemporaryVariable::arraySize = arraySize;
}
