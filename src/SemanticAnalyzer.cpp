#include "SemanticAnalyzer.h"

#include <cstddef>
#include <string>
#include <vector>

#include "IR/IRArgument.h"
#include "IR/IRDerivedTypes.h"
#include "IR/IRFunction.h"
#include "IR/IRType.h"
#include "IR/IRValue.h"
#include "IR/iMemory.h"
#include "symbolTable.h"
#include "utils/CACT.h"
#include "utils/ReturnValue.h"

SemanticAnalyzer::SemanticAnalyzer(GlobalBlock *globalBlock, IRModule *ir, tree::ParseTree *root)
        : globalBlock(globalBlock),
          ir(ir),
          root(root),
          currentBlock(globalBlock),
          currentFunc(nullptr) {}

SemanticAnalyzer::~SemanticAnalyzer() = default;

std::any SemanticAnalyzer::visitFunctionType(CACTParser::FunctionTypeContext *context) {
    return visitChildren(context);
}

std::any SemanticAnalyzer::visitBasicType(CACTParser::BasicTypeContext *context) {
    return visitChildren(context);
}

std::any SemanticAnalyzer::visitPrimaryExpression(CACTParser::PrimaryExpressionContext *context) {
    if (context->lValue() != nullptr) {
        return this->visit(context->lValue());
    } else if (context->number() != nullptr) {
        return this->visit(context->number());
    } else {
        return this->visit(context->expression());
    }
}

std::any SemanticAnalyzer::visitUnaryExpression(CACTParser::UnaryExpressionContext *context) {
    DataType dataType;
    std::vector<int> arraySize;
    if (context->primaryExpression() != nullptr) {  // primaryExpression
        return visitChildren(context);
    } else if (context->unaryOperator() != nullptr) {  // unaryOperator unaryExpression
        auto unaryExpression = std::any_cast<ReturnValue>(this->visit(context->unaryExpression()));
        dataType = unaryExpression.getDataType();
        if (unaryExpression.getDimension() != 0) {
            ErrorHandler::printErrorContext(context->unaryExpression(), "is array");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        if (context->unaryOperator()->getText() == "!") {
            if (dataType != DataType::BOOL) {
                ErrorHandler::printErrorContext(
                        context->unaryExpression(),
                        "Error data type, expect " + Utils::ttos(DataType::BOOL));
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        } else {
            if (dataType != DataType::DOUBLE && dataType != DataType::FLOAT &&
                dataType != DataType::INT) {
                ErrorHandler::printErrorContext(
                        context->unaryExpression(),
                        "Error data type, expect " + Utils::ttos(DataType::DOUBLE) + "/" +
                        Utils::ttos(DataType::FLOAT) + "/" + Utils::ttos(DataType::INT));
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        }
        return unaryExpression;
    } else {  // function
        auto func = globalBlock->lookUpFunc(context->Identifier()->getText());
        if (func == nullptr) {
            ErrorHandler::printErrorContext(context, "use of undeclared function");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        if (context->functionRParams() != nullptr) {
            context->functionRParams()->func = func;
            this->visit(context->functionRParams());
        } else {
            if (func->getparamNum() != 0) {
                ErrorHandler::printErrorContext(context, "Too few arguments");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        }
        return ReturnValue(func->getDataType(), 0, std::vector<int>(), func->getSymbolType());
    }
}

std::any SemanticAnalyzer::visitFunctionRParams(CACTParser::FunctionRParamsContext *context) {
    auto paramList = context->func->getparamList();

    if (context->func->getparamNum() < context->expression().size()) {
        ErrorHandler::printErrorContext(context, "Too many arguments");
        throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                 std::to_string(__LINE__));
    }
    if (context->func->getparamNum() > context->expression().size()) {
        ErrorHandler::printErrorContext(context, "Too few arguments");
        throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                 std::to_string(__LINE__));
    }

    for (int i = 0; i < paramList.size(); ++i) {
        auto retVal = std::any_cast<ReturnValue>(this->visit(context->expression()[i]));
        if (retVal.getDataType() != paramList[i]->getDataType()) {
            ErrorHandler::printErrorContext(context->expression(i), "Error data type");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        auto arraySize = paramList[i]->getArraySize();
        if (retVal.getDimension() != arraySize.size()) {
            ErrorHandler::printErrorContext(context->expression(i), "Error array dimension");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        for (int j = 0; j < retVal.getDimension(); ++j) {
            if (arraySize[j] == 0) continue;
            if (arraySize[j] != retVal.getArraySize()[j]) {
                ErrorHandler::printErrorContext(context->expression(i), "Error array dimension");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        }
    }
    return {};
}

std::any SemanticAnalyzer::visitUnaryOperator(CACTParser::UnaryOperatorContext *context) {
    return {};
}

std::any SemanticAnalyzer::visitMultiplicativeExpression(
        CACTParser::MultiplicativeExpressionContext *context) {
    std::vector<ReturnValue> expList;
    for (auto unaryExpression: context->unaryExpression()) {
        expList.push_back(std::any_cast<ReturnValue>(this->visit(unaryExpression)));
    }
    if (expList.size() > 1) {
        for (int i = 0; i < expList.size(); ++i) {
            if (expList[i].getDataType() != DataType::INT &&
                expList[i].getDataType() != DataType::DOUBLE &&
                expList[i].getDataType() != DataType::FLOAT) {
                ErrorHandler::printErrorContext(
                        context->unaryExpression(i),
                        "is " + Utils::ttos(expList[i].getDataType()) + ", error data type");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
            if (expList[i].getDimension() != 0) {
                ErrorHandler::printErrorContext(context->unaryExpression(i), "is array");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        }
        for (int i = 1; i < expList.size(); ++i) {
            if (expList[i - 1].getDataType() != expList[i].getDataType()) {
                ErrorHandler::printErrorContext(context->unaryExpression(i - 1),
                                                "is " + Utils::ttos(expList[i - 1].getDataType()));
                ErrorHandler::printErrorContext(context->unaryExpression(i),
                                                "is " + Utils::ttos(expList[i].getDataType()));
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        }
    }
    return expList[0];
}

std::any SemanticAnalyzer::visitAdditiveExpression(CACTParser::AdditiveExpressionContext *context) {
    std::vector<ReturnValue> expList;
    for (auto multiplicativeExpression: context->multiplicativeExpression()) {
        expList.push_back(std::any_cast<ReturnValue>(this->visit(multiplicativeExpression)));
    }

    if (expList.size() > 1) {
        for (int i = 0; i < expList.size(); ++i) {
            if (expList[i].getDataType() != DataType::INT &&
                expList[i].getDataType() != DataType::DOUBLE &&
                expList[i].getDataType() != DataType::FLOAT) {
                ErrorHandler::printErrorContext(
                        context->multiplicativeExpression(i),
                        "is " + Utils::ttos(expList[i].getDataType()) + ", error data type");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
            if (expList[i].getDimension() != 0) {
                ErrorHandler::printErrorContext(context->multiplicativeExpression(i), "is array");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        }
        for (int i = 1; i < expList.size(); ++i) {
            if (expList[i - 1].getDataType() != expList[i].getDataType()) {
                ErrorHandler::printErrorContext(context->multiplicativeExpression(i - 1),
                                                "is " + Utils::ttos(expList[i - 1].getDataType()));
                ErrorHandler::printErrorContext(context->multiplicativeExpression(i),
                                                "is " + Utils::ttos(expList[i].getDataType()));
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        }
    }
    return expList[0];
}

std::any SemanticAnalyzer::visitRelationalExpression(
        CACTParser::RelationalExpressionContext *context) {
    if (context->additiveExpression().size() == 1) {
        auto additiveExpression =
                std::any_cast<ReturnValue>(this->visit(context->additiveExpression(0)));
        if (additiveExpression.getDimension() != 0) {
            ErrorHandler::printErrorContext(context->additiveExpression(0), "is array");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        return additiveExpression;
    } else {
        std::vector<ReturnValue> expList;
        for (auto additiveExpression: context->additiveExpression()) {
            expList.push_back(std::any_cast<ReturnValue>(this->visit(additiveExpression)));
        }
        for (int i = 0; i < expList.size(); ++i) {
            if (expList[i].getDataType() != DataType::INT &&
                expList[i].getDataType() != DataType::DOUBLE &&
                expList[i].getDataType() != DataType::FLOAT) {
                ErrorHandler::printErrorContext(
                        context->additiveExpression(i),
                        "is " + Utils::ttos(expList[i].getDataType()) + ", error data type");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
            if (expList[i].getDimension() != 0) {
                ErrorHandler::printErrorContext(context->additiveExpression(i), "is array");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        }
        if (expList[0].getDataType() != expList[1].getDataType()) {
            ErrorHandler::printErrorContext(context->additiveExpression(0),
                                            "is " + Utils::ttos(expList[0].getDataType()));
            ErrorHandler::printErrorContext(context->additiveExpression(1),
                                            "is " + Utils::ttos(expList[1].getDataType()));
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        return ReturnValue(DataType::BOOL, 0, std::vector<int>(), SymbolType::NUM);
    }
}

std::any SemanticAnalyzer::visitEqualityExpression(CACTParser::EqualityExpressionContext *context) {
    if (context->relationalExpression().size() == 1) {
        auto relationalExpression =
                std::any_cast<ReturnValue>(this->visit(context->relationalExpression(0)));
        if (relationalExpression.getDimension() != 0) {
            ErrorHandler::printErrorContext(context->relationalExpression(0), "is array");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        return relationalExpression;
    } else {
        std::vector<ReturnValue> expList;
        for (auto relationalExpression: context->relationalExpression()) {
            expList.push_back(std::any_cast<ReturnValue>(this->visit(relationalExpression)));
        }
        for (int i = 0; i < expList.size(); ++i) {
            if (expList[i].getDataType() != DataType::INT &&
                expList[i].getDataType() != DataType::DOUBLE &&
                expList[i].getDataType() != DataType::FLOAT &&
                expList[i].getDataType() != DataType::BOOL) {
                ErrorHandler::printErrorContext(
                        context->relationalExpression(i),
                        "is " + Utils::ttos(expList[i].getDataType()) + ", error data type");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
            if (expList[i].getDimension() != 0) {
                ErrorHandler::printErrorContext(context->relationalExpression(i), "is array");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        }
        if (expList[0].getDataType() != expList[1].getDataType()) {
            ErrorHandler::printErrorContext(context->relationalExpression(0),
                                            "is " + Utils::ttos(expList[0].getDataType()));
            ErrorHandler::printErrorContext(context->relationalExpression(1),
                                            "is " + Utils::ttos(expList[1].getDataType()));
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        return ReturnValue(DataType::BOOL, 0, std::vector<int>(), SymbolType::NUM);
    }
}

std::any SemanticAnalyzer::visitLogicalAndExpression(
        CACTParser::LogicalAndExpressionContext *context) {
    std::vector<ReturnValue> expList;
    for (auto equalityExpression: context->equalityExpression()) {
        expList.push_back(std::any_cast<ReturnValue>(this->visit(equalityExpression)));
    }
    for (int i = 0; i < expList.size(); ++i) {
        if (expList[i].getDataType() != DataType::BOOL) {
            ErrorHandler::printErrorContext(
                    context->equalityExpression(i),
                    "is " + Utils::ttos(expList[i].getDataType()) + ", error data type");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        if (expList[i].getDimension() != 0) {
            ErrorHandler::printErrorContext(context->equalityExpression(i), "is array");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
    }
    return expList[0];
}

std::any SemanticAnalyzer::visitLogicalOrExpression(
        CACTParser::LogicalOrExpressionContext *context) {
    std::vector<ReturnValue> expList;
    for (auto equalityExpression: context->logicalAndExpression()) {
        expList.push_back(std::any_cast<ReturnValue>(this->visit(equalityExpression)));
    }
    for (int i = 0; i < expList.size(); ++i) {
        if (expList[i].getDataType() != DataType::BOOL) {
            ErrorHandler::printErrorContext(
                    context->logicalAndExpression(i),
                    "is " + Utils::ttos(expList[i].getDataType()) + ", error data type");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        if (expList[i].getDimension() != 0) {
            ErrorHandler::printErrorContext(context->logicalAndExpression(i), "is array");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
    }
    return expList[0];
}

std::any SemanticAnalyzer::visitExpression(CACTParser::ExpressionContext *context) {
    if (context->additiveExpression() == nullptr) {
        return ReturnValue(DataType::BOOL, 0, std::vector<int>(), SymbolType::NUM);
    } else {
        return this->visit(context->additiveExpression());
    }
}

std::any SemanticAnalyzer::visitConstantExpression(CACTParser::ConstantExpressionContext *context) {
    if (context->number() == nullptr) {
        if (context->dataType != DataType::BOOL) {
            ErrorHandler::printErrorContext(
                    context, "Error value type, expect " + Utils::ttos(context->dataType));
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
    } else {
        auto numberType = std::any_cast<ReturnValue>(this->visit(context->number())).getDataType();
        if (context->dataType != numberType) {
            ErrorHandler::printErrorContext(
                    context, "Error value type, expect " + Utils::ttos(context->dataType));
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
    }
    return {};
}

std::any SemanticAnalyzer::visitCondition(CACTParser::ConditionContext *context) {
    auto retVal = std::any_cast<ReturnValue>(this->visit(context->logicalOrExpression()));
    if (retVal.getDataType() != DataType::BOOL) {
        ErrorHandler::printErrorContext(context, "condition is not bool");
        throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                 std::to_string(__LINE__));
    }
    if (retVal.getDimension() != 0) {
        ErrorHandler::printErrorContext(context, "is array");
        throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                 std::to_string(__LINE__));
    }
    return {};
}

std::any SemanticAnalyzer::visitDeclaration(CACTParser::DeclarationContext *context) {
    return visitChildren(context);
}

std::any SemanticAnalyzer::visitConstantDeclaration(
        CACTParser::ConstantDeclarationContext *context) {
    context->dataType = Utils::stot(context->basicType()->getText());
    for (auto constantDefinition: context->constantDefinition()) {
        constantDefinition->dataType = context->dataType;
        this->visit(constantDefinition);
    }
    return {};
}

std::any SemanticAnalyzer::visitConstantDefinition(CACTParser::ConstantDefinitionContext *context) {
    size_t line = context->Identifier()->getSymbol()->getLine();
    for (auto size: context->IntegerConstant()) {
        context->arraySize.push_back(stoi(size->getText(), nullptr, 0));
    }
    size_t dimension = context->arraySize.size();
    std::string name = context->Identifier()->getText();
    /******先构建玩currentsymbol，再去往下访问******/
    if (dimension == 0) {
        currentSymbol = this->currentBlock->addNewConst(name, line, context->dataType);
    } else {
        currentSymbol = this->currentBlock->addNewConstArray(name, line, context->dataType,
                                                             context->arraySize, dimension);
    }

    context->constantInitValue()->dataType = context->dataType;
    context->constantInitValue()->arraySize = context->arraySize;
    context->constantInitValue()->dimension = dimension;  // 这里必须得传进维数，确定递归层数
    this->visit(context->constantInitValue());
    // return std::make_tuple(name, context->arraySize, dimension, line);

    IRFunction *irCurrentFunc;
    if (dimension == 0) {  // const externaldeclaration
        dynamic_cast<ConstSymbolInfo *>(currentSymbol)->setIRValue();
    } else {  // constarray externaldeclaration
        if (currentBlock != globalBlock) {
            irCurrentFunc = dynamic_cast<IRFunction *>(currentFunc->getIRValue());
            dynamic_cast<ConstArraySymbolInfo *>(currentSymbol)
                    ->setIRValue(ir, irCurrentFunc->getCount(), currentFunc->getName());
            irCurrentFunc->addCount();
        } else {
            dynamic_cast<ConstArraySymbolInfo *>(currentSymbol)->setIRValue(ir);
        }
    }

    return {};
}

std::any SemanticAnalyzer::visitConstantInitValue(CACTParser::ConstantInitValueContext *context) {
    bool zero_dim;
    bool single_dim;  // 确定这个数组的写法，是一维的写法还是多维的写法，由此确定是否需要向下递归

    // 这里有一点，对于嵌套括号的写法，一定要越过single_dim这一层

    /* clang-format off */
    zero_dim = (context->constantExpression() != nullptr) && context->arraySize.empty();
    single_dim = !zero_dim &&
                 (context->dimension >= 1) && (context->LeftBrace() != nullptr && context->RightBrace() != nullptr) &&
                 //确定是一个数组(对应左侧与右侧)(任何数组都可以采用一维的写法)
                 (context->dimension == context->arraySize.size()) &&                        //确定是第一层进入
                 (context->constantInitValue().empty() ||
                  context->constantInitValue().front()->constantExpression() != nullptr);
    //往下多看一层，如果发现已经是constExpression了那么就代表是一维数组(或者啥都没有就是一对大括号);
    /* clang-format on */

    int arraySize = 0;

    /******single_dim直接终止递归，否则往下递归******/
    if (zero_dim) {
        context->constantExpression()->dataType = context->dataType;
        this->visit(context->constantExpression());
        currentSymbol->setInitValue(context->constantExpression()->getText(),
                                    context->constantExpression()->dataType);
    } else if (single_dim) {
        // 遍历每一个一维元素，直接压栈即可
        arraySize = std::accumulate(context->arraySize.begin(), context->arraySize.end(), 1,
                                    std::multiplies<>());

        // 如果有元素，先尝试压栈
        if (!context->constantInitValue().empty()) {  // 这个vector中没有元素
            for (auto constantInitValue: context->constantInitValue()) {
                constantInitValue->dataType = context->dataType;
                constantInitValue->dimension = context->dimension;

                this->visit(constantInitValue);
            }
        }

        // 补零
        for (int i = currentSymbol->getinitValueArraySize(); i < arraySize; i++) {
            currentSymbol->setZero(context->dataType);
        }
    } else {
        int subArraySize = 0;
        int currentSize = 0;

        /******进行array的参数一致性检查******/
        // type MUST BE array

        /******constantExpression不为空已经到底，arraySize还没empty，真实的数组(相比arraySize)少了维度******/
        if (context->constantExpression() != nullptr) {
            ErrorHandler::printErrorContext(context, "less brace for InitValue");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }

        /******constantExpression为空还没到底，arraySize已经empty，真实的数组(相比arraySize)多了维度******/
        if (context->arraySize.empty()) {
            ErrorHandler::printErrorContext(context, "more brace for InitValue");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }

        /******constantInitValue数量得和这一层的array属性值相同******/
        /******如果是最下一层一维的，可以选择不相同然后补零*****/
        if ((context->arraySize.size() != 1) &&
            (context->constantInitValue().size() != context->arraySize.front())) {
            ErrorHandler::printErrorContext(context, "Error number for InitValue");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }

        /******计算arraySize和subArraySize******/
        arraySize = std::accumulate(context->arraySize.begin(), context->arraySize.end(), 1,
                                    std::multiplies<>());
        subArraySize = arraySize / context->arraySize.front();

        for (auto constantInitValue: context->constantInitValue()) {
            // 更新下一级的locals
            constantInitValue->dataType = context->dataType;
            for (auto i = context->arraySize.begin() + 1; i < context->arraySize.end(); ++i) {
                constantInitValue->arraySize.push_back(*i);
            }
            constantInitValue->dimension = context->dimension;
            this->visit(constantInitValue);

            // 上面已经访问了一个子数组，然后将所有的空缺部位全部填上0
            currentSize +=
                    subArraySize;  // 这里与上面参数一致性的第三个判断是对应的；当是一维的时候这里可以选择补零，其他情况均不考虑
            for (int i = currentSymbol->getinitValueArraySize(); i < currentSize; i++) {
                currentSymbol->setZero(context->dataType);
            }
        }
    }

    return {};
}

std::any SemanticAnalyzer::visitVariableDeclaration(
        CACTParser::VariableDeclarationContext *context) {
    context->dataType = Utils::stot(context->basicType()->getText());
    for (auto variableDefinition: context->variableDefinition()) {
        variableDefinition->dataType = context->dataType;
        this->visit(variableDefinition);
    }
    return {};
}

std::any SemanticAnalyzer::visitVariableDefinition(CACTParser::VariableDefinitionContext *context) {
    size_t line = context->Identifier()->getSymbol()->getLine();
    for (auto size: context->IntegerConstant()) {
        context->arraySize.push_back(stoi(size->getText(), nullptr, 0));
    }
    size_t dimension = context->arraySize.size();
    std::string name = context->Identifier()->getText();
    /******先构建完currentsymbol，再去往下访问******/
    if (dimension == 0) {
        currentSymbol = this->currentBlock->addNewVar(name, line, context->dataType);
    } else {
        currentSymbol = this->currentBlock->addNewVarArray(name, line, context->dataType,
                                                           context->arraySize, dimension);
    }

    if (context->constantInitValue() != nullptr) {
        context->constantInitValue()->dataType = context->dataType;
        context->constantInitValue()->arraySize = context->arraySize;
        context->constantInitValue()->dimension = dimension;  // 这里必须得传进维数，确定递归层数
        this->visit(context->constantInitValue());
    } else {
        /*如果没有显式初始化，那么通过一个循环把所有相关初始化为0的数全部压进去*/
        //没有显式初始化，压0,显示这个symbol不显式初始化
        unsigned loop;
        if (context->arraySize.empty()) {
            loop = 1;
            dynamic_cast<VarSymbolInfo*>(currentSymbol)->isinitial = false;
        } else {
            loop = std::accumulate(context->arraySize.begin(), context->arraySize.end(), 1,
                                   std::multiplies());
            dynamic_cast<VarArraySymbolInfo*>(currentSymbol)->isinitial = false;
        }

        for (int i = 0; i < loop; i++) {
            currentSymbol->setZero(context->dataType);  // 如果没有显式初始化
        }
    }
    // return std::make_tuple(name, context->arraySize, dimension, line);

    /******在访问完下面的definition之后根据他们的不同类型进行setIRValue******/
    // 有一个疑问对于每一个symbol而言，有要求他们的basicblock必须是第一个吗？
    /******如果是global的，那么不需要进行currentFunc的getIRValue******/
    IRFunction *irCurrentFunc;
    if (dimension == 0) {
        if (currentBlock != globalBlock) {  // var instruction
            irCurrentFunc = dynamic_cast<IRFunction *>(currentFunc->getIRValue());
            dynamic_cast<VarSymbolInfo *>(currentSymbol)
                    ->setIRValue(IRValue::InstructionVal, irCurrentFunc->getCount(),
                                 irCurrentFunc->getBasicBlockList()[0]);
            irCurrentFunc->addCount();
        } else  // var externaldeclaration
            dynamic_cast<VarSymbolInfo *>(currentSymbol)
                    ->setIRValue(IRValue::GlobalVariableVal, 0, nullptr, nullptr, ir);
    } else {
        if (currentBlock != globalBlock) {  // vararray instruction
            irCurrentFunc = dynamic_cast<IRFunction *>(currentFunc->getIRValue());
            dynamic_cast<VarArraySymbolInfo *>(currentSymbol)
                    ->setIRValue(IRValue::InstructionVal, irCurrentFunc->getCount(),
                                 irCurrentFunc->getBasicBlockList()[0], nullptr, ir);
            irCurrentFunc->addCount();
        } else  // vararray externaldeclaration
            dynamic_cast<VarArraySymbolInfo *>(currentSymbol)
                    ->setIRValue(IRValue::GlobalVariableVal, 0, nullptr, nullptr, ir);
    }

    return {};
}

std::any SemanticAnalyzer::visitStatement(CACTParser::StatementContext *context) {
    if (context->compoundStatement() != nullptr) {
        this->visit(context->compoundStatement());
    } else if (context->expressionStatement() != nullptr) {
        this->visit(context->expressionStatement());
    } else if (context->selectionStatement() != nullptr) {
        this->visit(context->selectionStatement());
    } else if (context->iterationStatement() != nullptr) {
        this->visit(context->iterationStatement());
    } else if (context->jumpStatement() != nullptr) {
        this->visit(context->jumpStatement());
    } else {
        ErrorHandler::printErrorContext(context, "statement error");
        throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                 std::to_string(__LINE__));
    }

    return {};
}

std::any SemanticAnalyzer::visitCompoundStatement(CACTParser::CompoundStatementContext *context) {
    if (context->thisfuncinfo == nullptr) {
        context->thisblockinfo = currentBlock->addNewBlock();  // 更新blockinfo
    } else {
        context->thisblockinfo =
                globalBlock->addNewBlock(context->thisfuncinfo);  // 根据传进的funcinfo更新blockinfo
    }

    currentBlock = context->thisblockinfo;  // 更新currentBlock
    if (context->blockItemList()) {
        this->visit(context->blockItemList());
    }

    currentBlock = context->thisblockinfo->getParentBlock();  // currentBlock回溯
    return {};
}

std::any SemanticAnalyzer::visitBlockItemList(CACTParser::BlockItemListContext *context) {
    for (auto blockitem: context->blockItem()) {
        this->visit(blockitem);
    }
    return {};
}

std::any SemanticAnalyzer::visitBlockItem(CACTParser::BlockItemContext *context) {
    if (context->declaration() != nullptr) {
        this->visit(context->declaration());
    } else if (context->statement() != nullptr) {
        this->visit(context->statement());
    } else {
        ErrorHandler::printErrorContext(context, "blockitem error");
        throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                 std::to_string(__LINE__));
    }

    return {};
}

std::any SemanticAnalyzer::visitExpressionStatement(
        CACTParser::ExpressionStatementContext *context) {
    if (context->lValue() != nullptr) {
        auto lValue = std::any_cast<ReturnValue>(this->visit(context->lValue()));
        auto expression = std::any_cast<ReturnValue>(this->visit(context->expression()));
        if (lValue.getDataType() != expression.getDataType()) {
            ErrorHandler::printErrorContext(context, "data type error");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        if (lValue.getDimension() != 0) {
            ErrorHandler::printErrorContext(context->lValue(), "is array");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        if (expression.getDimension() != 0) {
            ErrorHandler::printErrorContext(context->expression(), "is array");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        if (lValue.getSymbolType() == SymbolType::NUM ||
            lValue.getSymbolType() == SymbolType::CONST_ARRAY ||
            lValue.getSymbolType() == SymbolType::CONST) {
            ErrorHandler::printErrorContext(context->lValue(), "is constant");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        return {};
    } else {
        if (context->expression()) {
            visit(context->expression());
        }
        return {};
    }
}

std::any SemanticAnalyzer::visitLValue(CACTParser::LValueContext *context) {
    SymbolInfo *symbol = this->currentBlock->lookUpSymbol(context->Identifier()->getText());
    if (symbol == nullptr) {
        ErrorHandler::printErrorContext(context, "use of undeclared identifier");
        throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                 std::to_string(__LINE__));
    }
    if (context->expression().empty()) {  // var || const
        if (symbol->getSymbolType() != SymbolType::VAR &&
            symbol->getSymbolType() != SymbolType::CONST) { // array
            return ReturnValue(symbol->getDataType(), symbol->getArraySize().size(), symbol->getArraySize(),
                               symbol->getSymbolType());
        } else {
            return ReturnValue(symbol->getDataType(), 0, std::vector<int>(), symbol->getSymbolType());
        }
    } else {  // array element
        if (symbol->getSymbolType() != SymbolType::VAR_ARRAY &&
            symbol->getSymbolType() != SymbolType::CONST_ARRAY) {
            ErrorHandler::printErrorContext(context, "is not array");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        for (auto expression: context->expression()) {
            auto retVal = std::any_cast<ReturnValue>(this->visit(expression));
            if (retVal.getDataType() != DataType::INT || retVal.getDimension() != 0) {
                ErrorHandler::printErrorContext(expression, "is invalid array index");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        }
        if (context->expression().size() > symbol->getArraySize().size()) {
            ErrorHandler::printErrorContext(context, "too many index");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        std::vector<int> arraySize;
        int dimension = symbol->getArraySize().size() - context->expression().size();
        for (int i = context->expression().size(); i < symbol->getArraySize().size(); ++i) {
            arraySize.push_back(symbol->getArraySize()[i]);
        }
        return ReturnValue(symbol->getDataType(), dimension, arraySize, symbol->getSymbolType());
    }
}

std::any SemanticAnalyzer::visitSelectionStatement(CACTParser::SelectionStatementContext *context) {
    context->thisblockinfo = currentBlock->addNewBlock();  // 更新blockinfo
    if (context->Else() != nullptr) context->ifelseType = true;

    currentBlock = context->thisblockinfo;  // 更新currentBlock
    this->visit(context->condition());

    for (auto statement: context->statement()) {
        this->visit(statement);
    }

    currentBlock = context->thisblockinfo->getParentBlock();  // currentBlock回溯
    return {};
}

std::any SemanticAnalyzer::visitIterationStatement(CACTParser::IterationStatementContext *context) {
    context->thisblockinfo = currentBlock->addNewBlock();  // 更新blockinfo

    currentBlock = context->thisblockinfo;  // 更新currentBlock
    this->visitChildren(context);
    currentBlock = context->thisblockinfo->getParentBlock();  // currentBlock回溯

    // return visitChildren(context);
    return {};
}

std::any SemanticAnalyzer::visitJumpStatement(CACTParser::JumpStatementContext *context) {
    if (context->Return() != nullptr) {
        if (context->expression() != nullptr) {
            auto retVal = std::any_cast<ReturnValue>(this->visit(context->expression()));
            if (retVal.getDimension() != 0) {
                ErrorHandler::printErrorContext(context, "is array");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
            if (retVal.getDataType() != this->currentFunc->getDataType()) {
                ErrorHandler::printErrorContext(context, "Error return type");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        } else {
            if (this->currentFunc->getDataType() != DataType::VOID) {
                ErrorHandler::printErrorContext(context, "miss return value");
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                         ":" + std::to_string(__LINE__));
            }
        }

    } else {
    }
    return {};
}

std::any SemanticAnalyzer::visitCompilationUnit(CACTParser::CompilationUnitContext *context) {
    this->visit(context->translationUnit());  // 直接访问翻译单元即可
    return {};
}

std::any SemanticAnalyzer::visitTranslationUnit(CACTParser::TranslationUnitContext *context) {
    for (auto externalDeclaration: context->externalDeclaration()) {
        this->visit(externalDeclaration);
        // this->globalBlock.addNewBlock()关于globalblock的操作，在初始化block时就放进去//感觉没有必要维护一个block？
    }
    return {};
}

std::any SemanticAnalyzer::visitExternalDeclaration(
        CACTParser::ExternalDeclarationContext *context) {
    if (context->declaration() != nullptr) {
        this->visit(context->declaration());  // visit子节点
    } else if (context->functionDefinition() != nullptr) {
        this->visit(context->functionDefinition());  // visit子节点
    } else {
        ErrorHandler::printErrorContext(context, "externaldeclaration error");
        throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                 std::to_string(__LINE__));
    }
    return {};
}

std::any SemanticAnalyzer::visitFunctionDefinition(CACTParser::FunctionDefinitionContext *context) {
    std::string returnTypeText = context->functionType()->getText();
    DataType returnType;
    returnType = Utils::stot(returnTypeText);

    context->thisfuncinfo =
            globalBlock->addNewFunc(context->Identifier()->getText(),
                                    context->Identifier()->getSymbol()->getLine(), returnType);
    // 全局块中的函数表添加，同时获得这个funcdefinition的funcsymbolinfo，为将来的blockinfo初始化做准备

    currentFunc = context->thisfuncinfo;  // 更新currentFunc
    /******先构建一个basicblock,后续对他的parent进行赋值******/
    IRBasicBlock *irfirstbasicblock;
    irfirstbasicblock = new IRBasicBlock("0");

    /******构建了paramlist,IRArgs(缺少母函数)，IRparams******/
    if (context->functionFParams() != nullptr) {
        if (context->Identifier()->getText() == std::string("main")) {
            ErrorHandler::printErrorContext(
                    context,
                    "main function must be without params");  // main函数不能带有参数
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        } else {
            context->functionFParams()->thisfuncinfo = context->thisfuncinfo;
            context->functionFParams()->irbasicblock = irfirstbasicblock;
            this->visit(
                    context
                            ->functionFParams());  // 先去访问参数，在将参数都访问完之后可以获得一个完整的函数定义，再去定义blockinfo
            // 等待下面的参数层完善这个函数
        }
    }

    /******构建函数,设置basicblock
     * parent,设置irCurrentFunc的basicblocklist,setIRValue中构建IRargs的母函数******/
    currentFunc->setIRValue(ir, IRFunction::Declared);
    irfirstbasicblock->setParent(dynamic_cast<IRFunction *>(currentFunc->getIRValue()));
    dynamic_cast<IRFunction *>(currentFunc->getIRValue())->addBasicBlock(irfirstbasicblock);

    /******从每个函数的(paramList)symbol出发，构建每个symbol的IRValue******/
    for (size_t i = 0; i < currentFunc->getparamList().size(); i++) {
        SymbolInfo *symbol;
        IRValue *arg;
        symbol = currentFunc->getparamList()[i];
        arg = currentFunc->getIRArgs()[i];

        if (dynamic_cast<VarArraySymbolInfo *>(symbol)) {
            dynamic_cast<VarArraySymbolInfo *>(symbol)->setIRValue(
                    IRValue::InstructionVal,
                    dynamic_cast<IRFunction *>(currentFunc->getIRValue())->getCount(),
                    irfirstbasicblock, arg);
        } else if (dynamic_cast<VarSymbolInfo *>(symbol)) {
            dynamic_cast<VarSymbolInfo *>(symbol)->setIRValue(
                    IRValue::InstructionVal,
                    dynamic_cast<IRFunction *>(currentFunc->getIRValue())->getCount(),
                    irfirstbasicblock, arg);
        }
        new IRStoreInst(dynamic_cast<ConstVarArraySymbolInfo *>(symbol)->getirInitailizer(), symbol->getIRValue(),
                        irfirstbasicblock);

        dynamic_cast<IRFunction *>(currentFunc->getIRValue())->addCount();
    }

    context->compoundStatement()->thisfuncinfo = context->thisfuncinfo;

    this->visit(context->compoundStatement());  // 进入函数体
    context->thisblockinfo =
            context->compoundStatement()->thisblockinfo;  // 接收compoundstatement创建的新的blockinfo
    return {nullptr};
}

std::any SemanticAnalyzer::visitFunctionFParams(CACTParser::FunctionFParamsContext *context) {
    unsigned beforeFuncCount = 0;

    /******先构建一个basicblock,后续对他的parent进行赋值******/
    for (auto fparam: context->functionFParam()) {
        fparam->thisfuncinfo = context->thisfuncinfo;  // 继续将函数往下传
        fparam->beforeFuncCount = ++beforeFuncCount;
        fparam->irbasicblock = context->irbasicblock;
        this->visit(fparam);  // 具体参数
    }

    return {nullptr};
}

std::any SemanticAnalyzer::visitFunctionFParam(CACTParser::FunctionFParamContext *context) {
    std::string basicTypeText = context->basicType()->getText();
    DataType basicType;
    basicType = Utils::stot(basicTypeText);
    SymbolInfo *symbolInfo;
    IRArgument *irarg;
    IRType *irElType;
    IRType *irType;

    int dimension;
    dimension = context->LeftBracket().size();  // 计算维数

    switch (basicType) {
        case BOOL:
            irElType = const_cast<IRType *>(IRType::getPrimitiveType(IRType::BoolTyID));
            break;
        case INT:
            irElType = const_cast<IRType *>(IRType::getPrimitiveType(IRType::IntTyID));
            break;
        case FLOAT:
            irElType = const_cast<IRType *>(IRType::getPrimitiveType(IRType::FloatTyID));
            break;
        case DOUBLE:
            irElType = const_cast<IRType *>(IRType::getPrimitiveType(IRType::DoubleTyID));
            break;
    }

    /******new一个basicblock往里面添加******/

    if (!dimension) {
        symbolInfo = context->thisfuncinfo->addParamVar(
                context->Identifier()->getText(), context->Identifier()->getSymbol()->getLine(),
                basicType);

        irType = irElType;
        // 变量设置IRValue
        // dynamic_cast<VarSymbolInfo*>(symbolInfo)->setIRValue(IRValue::InstructionVal, basicType,
        //                                        context->beforeFuncCount, context->irbasicblock);
    } else {
        int valid_size;  // 标记了数字的个数//第一维可能标记为0
        valid_size = context->IntegerConstant().size();
        std::vector<int> param_array;

        if (valid_size == dimension) {
            for (auto integetconstant: context->IntegerConstant()) {
                param_array.push_back(stoi(integetconstant->getText(), nullptr, 0));
            }
        } else if (valid_size == (dimension - 1)) {
            /******如果第一维是空的话那么给0******/
            param_array.push_back(0);
            for (auto integetconstant: context->IntegerConstant()) {
                param_array.push_back(stoi(integetconstant->getText(), nullptr, 0));
            }
        } else {
            ErrorHandler::printErrorContext(context, "array dimension error");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }  // 分析得到paramlist

        symbolInfo = context->thisfuncinfo->addParamArray(
                context->Identifier()->getText(), context->Identifier()->getSymbol()->getLine(),
                basicType, param_array, dimension);

        //unsigned arraysize;  // 记录这个paramarray有多大
        //arraysize = std::accumulate(param_array.begin(), param_array.end(), 1, std::multiplies());
        irType = new IRPointerType(irElType);

        // 变量设置IRValue
        // dynamic_cast<VarArraySymbolInfo*>(symbolInfo)->setIRValue(IRValue::InstructionVal,
        // basicType,
        //                                                 context->beforeFuncCount,
        //                                                 context->irbasicblock);
    }

    /******与paramlist同步构建IRargs与IRparams******/
    irarg = new IRArgument(irType, std::to_string(context->beforeFuncCount));
    currentFunc->getIRArgs().push_back(irarg);
    currentFunc->getIRParams().push_back(irType);
    /******将新加入参数的类型加入到当前函数中******/
    // currentFunc->getIRParams().push_back(symbolInfo->getIRValue()->getType());

    return {nullptr};
}

void SemanticAnalyzer::analyze() {
    this->visit(this->root);
    if (globalBlock->lookUpFunc("main") == nullptr) {
        ErrorHandler::printErrorMessage("Can not find main");
        throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                 std::to_string(__LINE__));
    }
}

std::any SemanticAnalyzer::visitIntegerConstant(CACTParser::IntegerConstantContext *context) {
    return ReturnValue(DataType::INT, 0, std::vector<int>(), SymbolType::NUM);
}

std::any SemanticAnalyzer::visitFloatingConstant(CACTParser::FloatingConstantContext *context) {
    unsigned length = context->FloatingConstant()->getText().size();
    char suffix = context->FloatingConstant()->getText()[length - 1];
    if (suffix == 'f' || suffix == 'F') {
        return ReturnValue(DataType::FLOAT, 0, std::vector<int>(), SymbolType::NUM);
    } else {
        return ReturnValue(DataType::DOUBLE, 0, std::vector<int>(), SymbolType::NUM);
    }
}

std::any SemanticAnalyzer::visitAddOp(CACTParser::AddOpContext *context) {
    return visitChildren(context);
}

std::any SemanticAnalyzer::visitMultiplicativeOp(CACTParser::MultiplicativeOpContext *context) {
    return {};
}

std::any SemanticAnalyzer::visitAdditiveOp(CACTParser::AdditiveOpContext *context) {
    return {};
}

std::any SemanticAnalyzer::visitRelationalOp(CACTParser::RelationalOpContext *context) {
    return {};
}

std::any SemanticAnalyzer::visitEqualityOp(CACTParser::EqualityOpContext *context) {
    return {};
}

std::any SemanticAnalyzer::visitLogicalAndOp(CACTParser::LogicalAndOpContext *context) {
    return {};
}

std::any SemanticAnalyzer::visitLogicalOrOp(CACTParser::LogicalOrOpContext *context) {
    return {};
}
