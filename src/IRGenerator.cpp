#include "IRGenerator.h"

#include "IR/IRArgument.h"
#include "IR/IRConstant.h"
#include "IR/iMemory.h"
#include "IR/iOperators.h"
#include "IR/iOther.h"
#include "IR/iTerminators.h"
#include <cstddef>

std::any IRGenerator::visitCompilationUnit(CACTParser::CompilationUnitContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitFunctionType(CACTParser::FunctionTypeContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitBasicType(CACTParser::BasicTypeContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitPrimaryExpression(CACTParser::PrimaryExpressionContext *context) {
    if (context->lValue()) {
        auto ret = std::any_cast<IRValue *>(visit(context->lValue()));
        if (context->lValue()->loadable) {
            ret = dynamic_cast<IRValue *>(new IRLoadInst(
                    ret, std::to_string(currentIRFunc->getCount()), currentIRBasicBlock));
            currentIRFunc->addCount();
        }
        if (context->trueBlock) {
            new IRBranchInst(context->trueBlock, context->falseBlock, ret, currentIRBasicBlock);
        }
        return ret;
    } else if (context->number()) {
        return visit(context->number());
    } else {
        context->expression()->trueBlock = context->trueBlock;
        context->expression()->falseBlock = context->falseBlock;
        return visit(context->expression());
    }
    return {};
}

std::any IRGenerator::visitUnaryExpression(CACTParser::UnaryExpressionContext *context) {
    if (context->primaryExpression()) {
        context->primaryExpression()->trueBlock = context->trueBlock;
        context->primaryExpression()->falseBlock = context->falseBlock;
        return visit(context->primaryExpression());
    } else if (context->unaryOperator()) {
        std::string opSt = context->unaryOperator()->getText();
        if (opSt == "!") {
            context->unaryExpression()->trueBlock = context->falseBlock;
            context->unaryExpression()->falseBlock = context->trueBlock;
        }
        auto val = std::any_cast<IRValue *>(visit(context->unaryExpression()));
        if (opSt == "+") {
            return val;
        } else if (opSt == "-") {
            auto ret = dynamic_cast<IRValue *>(IRBinaryOperator::createNeg(
                    val, std::to_string(currentIRFunc->getCount()), currentIRBasicBlock));
            currentIRFunc->addCount();
            return ret;
        } else {  // "!"
            if (context->unaryExpression()->trueBlock) {
                return val;
            } else {
                auto ret = dynamic_cast<IRValue *>(IRBinaryOperator::createNot(
                        val, std::to_string(currentIRFunc->getCount()), currentIRBasicBlock));
                currentIRFunc->addCount();
                return ret;
            }
        }
    } else {  // function

        std::vector<IRValue *> rParams;
        if (context->functionRParams()) {
            rParams = std::any_cast<std::vector<IRValue *>>(visit(context->functionRParams()));
        }
        auto func = globalBlock->lookUpFunc(context->Identifier()->getText())->getIRValue();
        auto ret = dynamic_cast<IRValue *>(new IRCallInst(
                func, rParams, std::to_string(currentIRFunc->getCount()), currentIRBasicBlock));
        currentIRFunc->addCount();
        if (context->trueBlock) {
            new IRBranchInst(context->trueBlock, context->falseBlock, ret, currentIRBasicBlock);
        }
        return ret;
    }
}

std::any IRGenerator::visitFunctionRParams(CACTParser::FunctionRParamsContext *context) {
    std::vector<IRValue *> rParams;
    for (auto param: context->expression()) {
        rParams.push_back(std::any_cast<IRValue *>(visit(param)));
    }
    return rParams;
}

std::any IRGenerator::visitUnaryOperator(CACTParser::UnaryOperatorContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitMultiplicativeExpression(
        CACTParser::MultiplicativeExpressionContext *context) {
    auto len = context->unaryExpression().size();
    if (len == 1) {
        context->unaryExpression(0)->trueBlock = context->trueBlock;
        context->unaryExpression(0)->falseBlock = context->falseBlock;
    }
    auto ret = std::any_cast<IRValue *>(visit(context->unaryExpression(0)));
    for (int i = 1; i < len; ++i) {
        auto val = std::any_cast<IRValue *>(visit(context->unaryExpression(i)));
        IRInstruction::BinaryOps op;
        std::string opSt = context->multiplicativeOp(i - 1)->getText();
        if (opSt == "*") {
            op = IRInstruction::Mul;
        } else if (opSt == "/") {
            op = IRInstruction::Div;
        } else {  // "%"
            op = IRInstruction::Rem;
        }
        ret = IRBinaryOperator::create(op, ret, val, std::to_string(currentIRFunc->getCount()),
                                       currentIRBasicBlock);
        currentIRFunc->addCount();
    }
    return ret;
}

std::any IRGenerator::visitAdditiveExpression(CACTParser::AdditiveExpressionContext *context) {
    auto len = context->multiplicativeExpression().size();
    if (len == 1) {
        context->multiplicativeExpression(0)->trueBlock = context->trueBlock;
        context->multiplicativeExpression(0)->falseBlock = context->falseBlock;
    }
    auto ret = std::any_cast<IRValue *>(visit(context->multiplicativeExpression(0)));
    for (int i = 1; i < len; ++i) {
        auto val = std::any_cast<IRValue *>(visit(context->multiplicativeExpression(i)));
        IRInstruction::BinaryOps op;
        std::string opSt = context->additiveOp(i - 1)->getText();
        if (opSt == "+") {  // "+"
            op = IRInstruction::Add;
        } else {  // "-"
            op = IRInstruction::Sub;
        }
        ret = IRBinaryOperator::create(op, ret, val, std::to_string(currentIRFunc->getCount()),
                                       currentIRBasicBlock);
        currentIRFunc->addCount();
    }
    return ret;
}

std::any IRGenerator::visitRelationalExpression(CACTParser::RelationalExpressionContext *context) {
    if (context->relationalOp()) {
        auto lVal = std::any_cast<IRValue *>(visit(context->additiveExpression(0)));
        auto rVal = std::any_cast<IRValue *>(visit(context->additiveExpression(1)));
        IRInstruction::BinaryOps op;
        std::string opSt = context->relationalOp()->getText();
        if (opSt == "<") {
            op = IRInstruction::SetLT;
        } else if (opSt == ">") {
            op = IRInstruction::SetGT;
        } else if (opSt == "<=") {
            op = IRInstruction::SetLE;
        } else {
            op = IRInstruction::SetGE;
        }
        auto res = dynamic_cast<IRValue *>(IRBinaryOperator::create(op, lVal, rVal,
                                                                    std::to_string(currentIRFunc->getCount()),
                                                                    currentIRBasicBlock));
        currentIRFunc->addCount();
        if (context->trueBlock) {
            new IRBranchInst(context->trueBlock, context->falseBlock, res, currentIRBasicBlock);
        } else {
            return res;
        }
    } else {
        context->additiveExpression(0)->trueBlock = context->trueBlock;
        context->additiveExpression(0)->falseBlock = context->falseBlock;
        return visit(context->additiveExpression(0));
    }
    return {};
}

std::any IRGenerator::visitEqualityExpression(CACTParser::EqualityExpressionContext *context) {
    if (context->equalityOp()) {
        auto lVal = std::any_cast<IRValue *>(visit(context->relationalExpression(0)));
        auto rVal = std::any_cast<IRValue *>(visit(context->relationalExpression(1)));
        IRInstruction::BinaryOps op = (context->equalityOp()->getText() == "==") ? IRInstruction::SetEQ
                                                                                 : IRInstruction::SetNE;
        auto res = dynamic_cast<IRValue *>(IRBinaryOperator::create(op, lVal, rVal,
                                                                    std::to_string(currentIRFunc->getCount()),
                                                                    currentIRBasicBlock));
        currentIRFunc->addCount();
        new IRBranchInst(context->trueBlock, context->falseBlock, res, currentIRBasicBlock);
    } else {
        context->relationalExpression(0)->trueBlock = context->trueBlock;
        context->relationalExpression(0)->falseBlock = context->falseBlock;
        return visit(context->relationalExpression(0));
    }
    return {};
}

std::any IRGenerator::visitLogicalAndExpression(CACTParser::LogicalAndExpressionContext *context) {
    auto len = context->equalityExpression().size();
    for (int i = 0; i < len - 1; ++i) {
        context->equalityExpression(i)->trueBlock = new IRBasicBlock(std::to_string(currentIRFunc->getCount()),
                                                                     currentIRFunc);
        currentIRFunc->addCount();
        context->equalityExpression(i)->falseBlock = context->falseBlock;
        if (i) {
            currentIRBasicBlock = context->equalityExpression(i - 1)->trueBlock;
        }
        visit(context->equalityExpression(i));
    }
    context->equalityExpression().back()->trueBlock = context->trueBlock;
    context->equalityExpression().back()->falseBlock = context->falseBlock;
    if (len > 1) {
        currentIRBasicBlock = context->equalityExpression(len - 2)->trueBlock;
    }
    visit(context->equalityExpression().back());
    return {};
}

std::any IRGenerator::visitLogicalOrExpression(CACTParser::LogicalOrExpressionContext *context) {
    auto len = context->logicalAndExpression().size();
    for (int i = 0; i < len - 1; ++i) {
        context->logicalAndExpression(i)->trueBlock = context->trueBlock;
        context->logicalAndExpression(i)->falseBlock = new IRBasicBlock(std::to_string(currentIRFunc->getCount()),
                                                                        currentIRFunc);
        currentIRFunc->addCount();
        if (i) {
            currentIRBasicBlock = context->logicalAndExpression(i - 1)->falseBlock;
        }
        visit(context->logicalAndExpression(i));
    }
    context->logicalAndExpression().back()->trueBlock = context->trueBlock;
    context->logicalAndExpression().back()->falseBlock = context->falseBlock;
    if (len > 1) {
        currentIRBasicBlock = context->logicalAndExpression(len - 2)->falseBlock;
    }
    visit(context->logicalAndExpression().back());
    return {};
}

std::any IRGenerator::visitExpression(CACTParser::ExpressionContext *context) {
    IRValue *ret = nullptr;
    if (context->additiveExpression()) {  // 加法
        context->additiveExpression()->trueBlock = context->trueBlock;
        context->additiveExpression()->falseBlock = context->falseBlock;
        ret = std::any_cast<IRValue *>(visit(context->additiveExpression()));
    } else {  // 布尔常量
        if (context->BooleanConstant()->getText() == "true") {
            ret = dynamic_cast<IRValue *>(IRConstantBool::get(true));
            if (context->trueBlock)
                new IRBranchInst(context->trueBlock, nullptr, nullptr, currentIRBasicBlock);
        } else {
            ret = dynamic_cast<IRValue *>(IRConstantBool::get(false));
            if (context->trueBlock)
                new IRBranchInst(context->falseBlock, nullptr, nullptr, currentIRBasicBlock);
        }
    }
    return ret;
}

std::any IRGenerator::visitConstantExpression(CACTParser::ConstantExpressionContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitCondition(CACTParser::ConditionContext *context) {
    context->logicalOrExpression()->trueBlock = context->trueBlock;
    context->logicalOrExpression()->falseBlock = context->falseBlock;
    return visitChildren(context);
}

std::any IRGenerator::visitDeclaration(CACTParser::DeclarationContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitConstantDeclaration(CACTParser::ConstantDeclarationContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitConstantDefinition(CACTParser::ConstantDefinitionContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitConstantInitValue(CACTParser::ConstantInitValueContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitVariableDeclaration(CACTParser::VariableDeclarationContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitVariableDefinition(CACTParser::VariableDefinitionContext *context) {
    size_t dimension = context->arraySize.size();
    std::string name = context->Identifier()->getText();
    auto symbol = currentBlock->lookUpSymbol(name);
    if (currentBlock != globalBlock) {
        if (dimension == 0) {
            if (dynamic_cast<VarSymbolInfo *>(symbol)->isinitial == true) {
                new IRStoreInst(dynamic_cast<VarSymbolInfo *>(symbol)->getirInitailizer(),
                                dynamic_cast<VarSymbolInfo *>(symbol)->getIRValue(), currentIRBasicBlock);
            }
        } else {
            IRValue *srcGlobalVar;
            srcGlobalVar = new IRGlobalVariable
                    (dynamic_cast<VarArraySymbolInfo *>(symbol)->getirInitailizer()->getType(), false,
                     IRGlobalValue::AppendingLinkage,  //这里linkage的意思暂且定为是说附加到某个VarArray上，不是真正的global
                     dynamic_cast<IRConstant *>(dynamic_cast<VarArraySymbolInfo *>(symbol)->getirInitailizer()),
                     "__" + symbol->getName() + std::to_string(currentIRFunc->getCount()) + "_" + "global" + "_" +
                     currentFunc->getName(), ir);
            new IRMemcpyInst(dynamic_cast<VarArraySymbolInfo *>(symbol)->getIRValue(), srcGlobalVar, 
                             currentIRBasicBlock);
        }
    }
    return visitChildren(context);
}

std::any IRGenerator::visitStatement(CACTParser::StatementContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitCompoundStatement(CACTParser::CompoundStatementContext *context) {
    currentBlock = context->thisblockinfo;
    visitChildren(context);
    currentBlock = currentBlock->getParentBlock();
    return {};
}

std::any IRGenerator::visitBlockItemList(CACTParser::BlockItemListContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitBlockItem(CACTParser::BlockItemContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitExpressionStatement(CACTParser::ExpressionStatementContext *context) {
    bool hasLVal = (context->lValue() != nullptr);  // 有一个赋值行为
    if (hasLVal) {
        auto *expVal = std::any_cast<IRValue *>(visit(context->expression()));
        auto *ptr = std::any_cast<IRValue *>(visit(context->lValue()));
        new IRStoreInst(expVal, ptr, currentIRBasicBlock);
    } else {
        visit(context->expression());
    }
    return {};
}

std::any IRGenerator::visitLValue(CACTParser::LValueContext *context) {
    auto symbol = currentBlock->lookUpSymbol(context->Identifier()->getText());
    auto varPtr = symbol->getIRValue();
    if (symbol->getSymbolType() != SymbolType::CONST) {
        unsigned size;
        if (symbol->getSymbolType() == SymbolType::VAR) {
            size = dynamic_cast<IRPointerType *>(varPtr->getType())->getElementType()->getPrimitiveSize();
        } else {
            size = dynamic_cast<IRSequentialType *>(
                    dynamic_cast<IRPointerType *>(varPtr->getType())->getElementType()
            )->getElementType()->getPrimitiveSize();
        }
        if (symbol->getSymbolType() == SymbolType::VAR_ARRAY ||
            symbol->getSymbolType() == SymbolType::CONST_ARRAY) {  // 左值是数组
            varPtr = new IRLoadInst(varPtr, std::to_string(currentIRFunc->getCount()), currentIRBasicBlock);
            currentIRFunc->addCount();
            auto arraySize = symbol->getArraySize();
            for (int i = 0; i < context->expression().size(); ++i) {
                auto idxSize = dynamic_cast<IRValue *>(IRConstantInt::get(std::accumulate(
                        arraySize.begin() + i + 1, arraySize.end(), size, std::multiplies())));
                auto idx = std::any_cast<IRValue *>(visit(context->expression(i)));
                auto offset = dynamic_cast<IRValue *>(IRBinaryOperator::create(
                        IRInstruction::Mul, idx, idxSize, std::to_string(currentIRFunc->getCount()),
                        currentIRBasicBlock));
                currentIRFunc->addCount();
                varPtr = dynamic_cast<IRValue *>(IRBinaryOperator::create(
                        IRInstruction::Add, varPtr, offset, std::to_string(currentIRFunc->getCount()),
                        currentIRBasicBlock));
                currentIRFunc->addCount();
            }
        }
    }
    if (context->expression().size() < symbol->getArraySize().size() ||
        symbol->getSymbolType() == SymbolType::CONST) {
        context->loadable = false;
    } else {
        context->loadable = true;
    }
    return varPtr;
}

std::any IRGenerator::visitSelectionStatement(CACTParser::SelectionStatementContext *context) {
    currentBlock = context->thisblockinfo;

    IRBasicBlock *trueBlock = nullptr;
    IRBasicBlock *falseBlock = nullptr;
    IRBasicBlock *nextBlock = nullptr;
    if (context->Else()) {
        trueBlock = new IRBasicBlock();
        falseBlock = new IRBasicBlock();
        nextBlock = new IRBasicBlock();
    } else {
        trueBlock = new IRBasicBlock();
        falseBlock = new IRBasicBlock();
        nextBlock = falseBlock;
    }
    context->condition()->trueBlock = trueBlock;
    context->condition()->falseBlock = falseBlock;
    visit(context->condition());

    //! visit true statement
    trueBlock->setParent(currentIRFunc);
    currentIRFunc->addBasicBlock(trueBlock);
    trueBlock->setName(std::to_string(currentIRFunc->getCount()));
    currentIRFunc->addCount();
    currentIRBasicBlock = trueBlock;
    visit(context->statement(0));
    new IRBranchInst(nextBlock, nullptr, nullptr, currentIRBasicBlock);

    //! visit false statement
    if (context->Else()) {
        falseBlock->setParent(currentIRFunc);
        currentIRFunc->addBasicBlock(falseBlock);
        falseBlock->setName(std::to_string(currentIRFunc->getCount()));
        currentIRFunc->addCount();
        currentIRBasicBlock = falseBlock;
        visit(context->statement(1));
        new IRBranchInst(nextBlock, nullptr, nullptr, currentIRBasicBlock);
    }

    nextBlock->setParent(currentIRFunc);
    currentIRFunc->addBasicBlock(nextBlock);
    nextBlock->setName(std::to_string(currentIRFunc->getCount()));
    currentIRFunc->addCount();
    currentIRBasicBlock = nextBlock;

    currentBlock = currentBlock->getParentBlock();
    return {};
}

std::any IRGenerator::visitIterationStatement(CACTParser::IterationStatementContext *context) {
    currentBlock = context->thisblockinfo;

    context->preheader = new IRBasicBlock();
    context->nextBlock = new IRBasicBlock();
    context->latch = new IRBasicBlock();
    context->condition()->trueBlock = context->preheader;
    context->condition()->falseBlock = context->nextBlock;
    visit(context->condition());

    context->preheader->setParent(currentIRFunc);
    context->preheader->setName(std::to_string(currentIRFunc->getCount()));
    currentIRFunc->addCount();
    currentIRFunc->addBasicBlock(context->preheader);
    context->bodyBlock = new IRBasicBlock(std::to_string(currentIRFunc->getCount()), currentIRFunc);
    currentIRFunc->addCount();
    new IRBranchInst(context->bodyBlock, nullptr, nullptr, context->preheader);
    currentIRBasicBlock = context->bodyBlock;
    visit(context->statement());
//    context->latch = new IRBasicBlock(std::to_string(currentIRFunc->getCount()), currentIRFunc);
    context->latch->setParent(currentIRFunc);
    context->latch->setName(std::to_string(currentIRFunc->getCount()));
    currentIRFunc->addCount();
    currentIRFunc->addBasicBlock(context->latch);
    new IRBranchInst(context->latch, nullptr, nullptr, currentIRBasicBlock);

    context->condition()->trueBlock = context->bodyBlock;
    context->condition()->falseBlock = context->nextBlock;
    currentIRBasicBlock = context->latch;
    visit(context->condition());

    context->nextBlock->setParent(currentIRFunc);
    context->nextBlock->setName(std::to_string(currentIRFunc->getCount()));
    currentIRFunc->addCount();
    currentIRFunc->addBasicBlock(context->nextBlock);
    currentIRBasicBlock = context->nextBlock;

    currentBlock = currentBlock->getParentBlock();
    return {};
}

std::any IRGenerator::visitJumpStatement(CACTParser::JumpStatementContext *context) {
    if (context->Return()) {
        IRValue *val = nullptr;
        if (context->expression()) {
            val = std::any_cast<IRValue *>(visit(context->expression()));
        }
        new IRReturnInst(val, currentIRBasicBlock);
    } else {
        tree::ParseTree *whileContex = context->parent;
        CACTParser::IterationStatementContext *whilePtr = nullptr;
        for (; whileContex; whileContex = whileContex->parent) {
            if (whilePtr = dynamic_cast<CACTParser::IterationStatementContext *>(whileContex)) {
                break;
            }
        }
        if (whilePtr == nullptr) {
            ErrorHandler::printErrorContext(context, "is not in while");
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) +
                                     ":" + std::to_string(__LINE__));
        }
        if (context->Break()) {
            new IRBranchInst(whilePtr->nextBlock, nullptr, nullptr, currentIRBasicBlock);
        } else { // continue
            new IRBranchInst(whilePtr->latch, nullptr, nullptr, currentIRBasicBlock);
        }
    }
    return {};
}

std::any IRGenerator::visitTranslationUnit(CACTParser::TranslationUnitContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitExternalDeclaration(CACTParser::ExternalDeclarationContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitFunctionDefinition(CACTParser::FunctionDefinitionContext *context) {
    currentFunc = globalBlock->lookUpFunc(context->Identifier()->getText());
    currentIRFunc = dynamic_cast<IRFunction *>(currentFunc->getIRValue());
    currentIRBasicBlock = currentIRFunc->getEntryBlock();
    visitChildren(context);
    if (currentIRFunc->getFunctionType()->getReturnType() == IRType::VoidTy) {
        new IRReturnInst(nullptr, currentIRBasicBlock);
    } else if (currentIRBasicBlock->getInstList().empty()) {
        std::vector<IRBasicBlock *> &BBList = currentIRFunc->getBasicBlockList();
        BBList.erase(BBList.end() - 1, BBList.end());
    }
    return {};
}

std::any IRGenerator::visitFunctionFParams(CACTParser::FunctionFParamsContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitFunctionFParam(CACTParser::FunctionFParamContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitIntegerConstant(CACTParser::IntegerConstantContext *context) {
    return dynamic_cast<IRValue *>(IRConstantInt::get(std::stoi(context->getText(), nullptr, 0)));
}

std::any IRGenerator::visitFloatingConstant(CACTParser::FloatingConstantContext *context) {
    std::string st = context->getText();
    if (st[st.size() - 1] == 'f' || st[st.size() - 1] == 'F') {  // float
        return dynamic_cast<IRValue *>(IRConstantFloat::get(std::stof(st)));
    } else {  // double
        return dynamic_cast<IRValue *>(IRConstantDouble::get(std::stod(st)));
    }
}

IRGenerator::IRGenerator(GlobalBlock *globalBlock, IRModule *ir, tree::ParseTree *root)
        : globalBlock(globalBlock),
          ir(ir),
          root(root),
          currentBlock(globalBlock),
          currentFunc(nullptr),
          currentIRFunc(nullptr),
          currentIRBasicBlock(nullptr) {}

void IRGenerator::generate() { visit(root); }

std::any IRGenerator::visitAddOp(CACTParser::AddOpContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitMultiplicativeOp(CACTParser::MultiplicativeOpContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitAdditiveOp(CACTParser::AdditiveOpContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitRelationalOp(CACTParser::RelationalOpContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitEqualityOp(CACTParser::EqualityOpContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitLogicalAndOp(CACTParser::LogicalAndOpContext *context) {
    return visitChildren(context);
}

std::any IRGenerator::visitLogicalOrOp(CACTParser::LogicalOrOpContext *context) {
    return visitChildren(context);
}
