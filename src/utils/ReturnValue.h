#ifndef COMPILER_RETURNVALUE_H
#define COMPILER_RETURNVALUE_H

#include <vector>

#include "CACT.h"

class ReturnValue {

private:
    DataType dataType;

    int dimension{};

    std::vector<int> arraySize;

    SymbolType symbolType;

public:
    ReturnValue(DataType dataType, int dimension, std::vector<int> arraySize, SymbolType symbolType);

    DataType getDataType() const;

    int getDimension() const;

    const std::vector<int> &getArraySize() const;

    SymbolType getSymbolType() const;
};


#endif//COMPILER_RETURNVALUE_H
