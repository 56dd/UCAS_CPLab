#pragma once

#include <iostream>

enum SymbolType {
    CONST,
    VAR,
    CONST_ARRAY,
    VAR_ARRAY,
    FUNC,
    NUM
};

enum DataType {
    VOID,
    BOOL,
    INT,
    FLOAT,
    DOUBLE,
};

class Utils {
public:
    static std::string ttos(DataType type) {
        switch (type) {
            case DataType::VOID:
                return "void";
            case DataType::BOOL:
                return "bool";
            case DataType::INT:
                return "int";
            case DataType::FLOAT:
                return "float";
            case DataType::DOUBLE:
                return "double";
            default:
                throw std::runtime_error("CACT.h:" + std::to_string(__LINE__) + " Unknown DataType");
        }
    }
    static DataType stot(const std::string& st) {
        if (st == "int") {
            return DataType::INT;
        } else if (st == "double") {
            return DataType::DOUBLE;
        } else if (st == "float") {
            return DataType::FLOAT;
        } else if (st == "bool") {
            return DataType::BOOL;
        } else if (st == "void") {
            return DataType::VOID;
        } else {
            throw std::runtime_error("CACT.h:" + std::to_string(__LINE__) + " Unknown DataType string");
        }
    }
};
