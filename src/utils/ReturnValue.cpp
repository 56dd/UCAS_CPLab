#include "ReturnValue.h"

#include <utility>


DataType ReturnValue::getDataType() const {
    return dataType;
}

int ReturnValue::getDimension() const {
    return dimension;
}

const std::vector<int> &ReturnValue::getArraySize() const {
    return arraySize;
}

SymbolType ReturnValue::getSymbolType() const {
    return symbolType;
}

ReturnValue::ReturnValue(DataType dataType, int dimension, std::vector<int> arraySize, SymbolType symbolType) {
    ReturnValue::dataType = dataType;
    ReturnValue::dimension = dimension;
    ReturnValue::arraySize = std::move(arraySize);
    ReturnValue::symbolType = symbolType;
}
