#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

#include <cstddef>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

#include "IR/IRArgument.h"
#include "IR/IRConstant.h"
#include "IR/IRValue.h"
#include "IR/IRType.h"
#include "IR/IRModule.h"
#include "IR/IRFunction.h"
#include "utils/CACT.h"
#include "utils/ErrorHandler.h"

// Forward declarations
class IROperand;
class IRModule;

/**
 * @brief Converts DataType enum to string representation
 * @param data_type Data type to convert
 * @return String representation of the data type
 */
std::string toString(DataType data_type);

/**
 * @brief Gets the size of a data type in bytes
 * @param data_type Data type to get size for
 * @return Size in bytes
 */
int getDataTypeSize(DataType data_type);

/**
 * @brief Base class for all symbol table entries
 * 
 * This class provides the common interface for all symbols in the symbol table,
 * including variables, constants, arrays, and functions.
 */
class SymbolInfo {
public:
    /**
     * @brief Constructs a SymbolInfo
     * @param symbol_name Name of the symbol
     * @param line_number Line number where symbol is declared
     */
    SymbolInfo(const std::string& symbol_name, int line_number);

    /**
     * @brief Virtual destructor
     */
    virtual ~SymbolInfo() = default;

    /**
     * @brief Gets the symbol name
     * @return Symbol name
     */
    const std::string& getName() const { return name_; }

    /**
     * @brief Gets the line number where symbol is declared
     * @return Line number
     */
    int getLineNumber() const { return line_number_; }

    /**
     * @brief Sets the IR operand for this symbol
     * @param operand IR operand to set
     */
    void setOperand(IROperand* operand);

    /**
     * @brief Gets the IR operand for this symbol
     * @return Pointer to IR operand
     */
    IROperand* getOperand() const { return operand_; }

    /**
     * @brief Gets the IR value for this symbol
     * @return Pointer to IR value
     */
    IRValue* getIRValue() const { return ir_value_; }

    /**
     * @brief Sets the IR value for this symbol
     * @param ir_value IR value to set
     */
    void setIRValue(IRValue* ir_value) { ir_value_ = ir_value; }

    // Pure virtual methods that must be implemented by derived classes
    /**
     * @brief Gets the data type of this symbol
     * @return Data type
     */
    virtual DataType getDataType() const = 0;

    /**
     * @brief Gets the array length (returns -1 for non-arrays)
     * @return Array length or -1 for non-arrays
     */
    virtual int getArrayLength() const = 0;

    /**
     * @brief Gets the array dimensions (empty vector for non-arrays)
     * @return Vector of array dimensions
     */
    virtual std::vector<int> getArrayDimensions() const = 0;

    /**
     * @brief Gets the symbol type
     * @return Symbol type
     */
    virtual SymbolType getSymbolType() const = 0;

protected:
    int line_number_;           ///< Line number where symbol is declared
    std::string name_;          ///< Symbol name
    IROperand* operand_;        ///< Associated IR operand
    IRValue* ir_value_;         ///< Associated IR value
};

/**
 * @brief Represents initialization values for symbols
 * 
 * This class manages the initialization values for constants and variables,
 * supporting both scalar and array initialization.
 */
class InitializationValue {
public:
    /**
     * @brief Default constructor
     */
    InitializationValue() = default;

    /**
     * @brief Destructor
     */
    ~InitializationValue() = default;

    /**
     * @brief Sets an initialization value from string
     * @param value_string String representation of the value
     * @param data_type Data type of the value
     */
    void setValue(const std::string& value_string, DataType data_type);

    /**
     * @brief Sets a zero initialization value
     * @param data_type Data type for the zero value
     */
    void setZero(DataType data_type);

    /**
     * @brief Gets the number of initialization values
     * @return Number of values
     */
    size_t getValueCount() const { return init_values_.size(); }

    /**
     * @brief Gets the initialization values
     * @return Vector of IR constants
     */
    const std::vector<IRConstant*>& getValues() const { return init_values_; }

    /**
     * @brief Clears all initialization values
     */
    void clear() { init_values_.clear(); }

private:
    std::vector<IRConstant*> init_values_;  ///< Array of initialization values
};

/**
 * @brief Base class for constant, variable, and array symbols
 * 
 * This class provides common functionality for symbols that can have
 * initialization values and can be either global or local.
 */
class ConstVarArraySymbolInfo : public SymbolInfo, public InitializationValue {
public:
    /**
     * @brief Constructs a ConstVarArraySymbolInfo
     * @param symbol_name Name of the symbol
     * @param line_number Line number where symbol is declared
     * @param data_type Data type of the symbol
     * @param is_global Whether the symbol is global
     */
    ConstVarArraySymbolInfo(const std::string& symbol_name, int line_number, 
                           DataType data_type, bool is_global);

    /**
     * @brief Destructor
     */
    ~ConstVarArraySymbolInfo() override = default;

    /**
     * @brief Gets the data type
     * @return Data type
     */
    DataType getDataType() const override { return data_type_; }

    /**
     * @brief Checks if the symbol is global
     * @return True if global, false if local
     */
    bool isGlobal() const { return is_global_; }

    /**
     * @brief Sets the IR initializer
     * @param initializer IR value to use as initializer
     */
    void setIRInitializer(IRValue* initializer) { ir_initializer_ = initializer; }

    /**
     * @brief Gets the IR initializer
     * @return Pointer to IR initializer
     */
    IRValue* getIRInitializer() const { return ir_initializer_; }

protected:
    DataType data_type_;        ///< Data type of the symbol
    bool is_global_;            ///< Whether the symbol is global
    IRValue* ir_initializer_;   ///< IR value used for initialization
};

/**
 * @brief Represents a constant symbol
 */
class ConstSymbolInfo : public ConstVarArraySymbolInfo {
public:
    /**
     * @brief Constructs a ConstSymbolInfo
     * @param symbol_name Name of the constant
     * @param line_number Line number where constant is declared
     * @param data_type Data type of the constant
     * @param is_global Whether the constant is global
     */
    ConstSymbolInfo(const std::string& symbol_name, int line_number, 
                   DataType data_type, bool is_global);

    /**
     * @brief Destructor
     */
    ~ConstSymbolInfo() override = default;

    /**
     * @brief Gets array length (always -1 for constants)
     * @return -1 (constants are not arrays)
     */
    int getArrayLength() const override { return -1; }

    /**
     * @brief Gets array dimensions (empty for constants)
     * @return Empty vector
     */
    std::vector<int> getArrayDimensions() const override { return std::vector<int>(); }

    /**
     * @brief Gets symbol type
     * @return CONST symbol type
     */
    SymbolType getSymbolType() const override { return SymbolType::CONST; }

    /**
     * @brief Sets the IR value for this constant
     */
    void setIRValue();
};

/**
 * @brief Represents a variable symbol
 */
class VarSymbolInfo : public ConstVarArraySymbolInfo {
public:
    /**
     * @brief Constructs a VarSymbolInfo
     * @param symbol_name Name of the variable
     * @param line_number Line number where variable is declared
     * @param data_type Data type of the variable
     * @param is_global Whether the variable is global
     */
    VarSymbolInfo(const std::string& symbol_name, int line_number, 
                 DataType data_type, bool is_global);

    /**
     * @brief Destructor
     */
    ~VarSymbolInfo() override = default;

    /**
     * @brief Checks if the variable is initialized
     * @return True if initialized
     */
    bool isInitialized() const { return is_initialized_; }

    /**
     * @brief Sets the initialization status
     * @param initialized Whether the variable is initialized
     */
    void setInitialized(bool initialized) { is_initialized_ = initialized; }

    /**
     * @brief Gets array length (always -1 for variables)
     * @return -1 (variables are not arrays)
     */
    int getArrayLength() const override { return -1; }

    /**
     * @brief Gets array dimensions (empty for variables)
     * @return Empty vector
     */
    std::vector<int> getArrayDimensions() const override { return std::vector<int>(); }

    /**
     * @brief Gets symbol type
     * @return VAR symbol type
     */
    SymbolType getSymbolType() const override { return SymbolType::VAR; }

    /**
     * @brief Sets the IR value for this variable
     * @param ir_value IR value to set
     */
    void setIRValue(IRValue* ir_value);

    /**
     * @brief Sets the IR value with additional parameters
     * @param value_type Value type
     * @param symbol_count Symbol count
     * @param parent_basic_block Parent basic block
     * @param initializer IR initializer
     * @param ir_module IR module
     */
    void setIRValue(IRValue::ValueTy value_type, unsigned symbol_count = 0,
                   IRBasicBlock* parent_basic_block = nullptr,
                   IRValue* initializer = nullptr,
                   IRModule* ir_module = nullptr);

private:
    bool is_initialized_;  ///< Whether the variable is initialized
};


/**
 * @brief Represents a constant array symbol
 */
class ConstArraySymbolInfo : public ConstVarArraySymbolInfo {
public:
    /**
     * @brief Constructs a ConstArraySymbolInfo
     * @param symbol_name Name of the constant array
     * @param line_number Line number where constant array is declared
     * @param data_type Data type of the array elements
     * @param is_global Whether the constant array is global
     * @param array_dimensions Dimensions of the array
     * @param dimension_count Number of dimensions
     */
    ConstArraySymbolInfo(const std::string& symbol_name, int line_number, DataType data_type, 
                        bool is_global, const std::vector<int>& array_dimensions, int dimension_count);

    /**
     * @brief Destructor
     */
    ~ConstArraySymbolInfo() override = default;

    /**
     * @brief Gets array dimensions
     * @return Vector of array dimensions
     */
    std::vector<int> getArrayDimensions() const override { return array_dimensions_; }

    /**
     * @brief Gets the number of dimensions
     * @return Number of dimensions
     */
    int getDimensionCount() const { return dimension_count_; }

    /**
     * @brief Gets the total array length
     * @return Total number of elements in the array
     */
    int getArrayLength() const override { 
        return std::accumulate(array_dimensions_.begin(), array_dimensions_.end(), 1, std::multiplies<int>()); 
    }

    /**
     * @brief Gets symbol type
     * @return CONST_ARRAY symbol type
     */
    SymbolType getSymbolType() const override { return SymbolType::CONST_ARRAY; }

    /**
     * @brief Sets the IR value for this constant array
     * @param ir_module IR module
     * @param symbol_count Symbol count
     * @param function_name Function name
     */
    void setIRValue(IRModule* ir_module = nullptr, unsigned symbol_count = 0, 
                   const std::string& function_name = "");

private:
    std::vector<int> array_dimensions_;  ///< Array dimensions
    int dimension_count_;                ///< Number of dimensions
};

/**
 * @brief Represents a variable array symbol
 */
class VarArraySymbolInfo : public ConstVarArraySymbolInfo {
public:
    /**
     * @brief Constructs a VarArraySymbolInfo
     * @param symbol_name Name of the variable array
     * @param line_number Line number where variable array is declared
     * @param data_type Data type of the array elements
     * @param is_global Whether the variable array is global
     * @param array_dimensions Dimensions of the array
     * @param dimension_count Number of dimensions
     */
    VarArraySymbolInfo(const std::string& symbol_name, int line_number, DataType data_type, 
                      bool is_global, const std::vector<int>& array_dimensions, int dimension_count);

    /**
     * @brief Destructor
     */
    ~VarArraySymbolInfo() override = default;

    /**
     * @brief Checks if the array is initialized
     * @return True if initialized
     */
    bool isInitialized() const { return is_initialized_; }

    /**
     * @brief Sets the initialization status
     * @param initialized Whether the array is initialized
     */
    void setInitialized(bool initialized) { is_initialized_ = initialized; }

    /**
     * @brief Gets the number of dimensions
     * @return Number of dimensions
     */
    int getDimensionCount() const { return dimension_count_; }

    /**
     * @brief Gets the total array length
     * @return Total number of elements in the array
     */
    int getArrayLength() const override { 
        return std::accumulate(array_dimensions_.begin(), array_dimensions_.end(), 1, std::multiplies<int>()); 
    }

    /**
     * @brief Gets array dimensions
     * @return Vector of array dimensions
     */
    std::vector<int> getArrayDimensions() const override { return array_dimensions_; }

    /**
     * @brief Gets symbol type
     * @return VAR_ARRAY symbol type
     */
    SymbolType getSymbolType() const override { return SymbolType::VAR_ARRAY; }

    /**
     * @brief Sets the IR value for this variable array
     * @param ir_value IR value to set
     */
    void setIRValue(IRValue* ir_value);

    /**
     * @brief Sets the IR value with additional parameters
     * @param value_type Value type
     * @param symbol_count Symbol count
     * @param parent_basic_block Parent basic block
     * @param initializer IR initializer
     * @param ir_module IR module
     */
    void setIRValue(IRValue::ValueTy value_type, unsigned symbol_count = 0,
                   IRBasicBlock* parent_basic_block = nullptr,
                   IRValue* initializer = nullptr,
                   IRModule* ir_module = nullptr);

private:
    std::vector<int> array_dimensions_;  ///< Array dimensions
    int dimension_count_;                ///< Number of dimensions
    bool is_initialized_;                ///< Whether the array is initialized
};

/*相对于徐泽凡学长做的改动：
  1)对于符号表加入了行号的属性
  2)对于常量变量数组符号加入了是否为全局变量的属性
  3)多做了一级继承，以上四个类全部继承自ConstVarArraySymbolInfo*/


class BlockInfo;//为了funcsymbolinfo的定义
class GlobalBlock;
class IRFunction;


/**
 * @brief Represents a function symbol
 */
class FuncSymbolInfo : public SymbolInfo {
public:
    /**
     * @brief Constructs a FuncSymbolInfo
     * @param function_name Name of the function
     * @param line_number Line number where function is declared
     * @param return_type Return type of the function
     */
    FuncSymbolInfo(const std::string& function_name, int line_number, DataType return_type);

    /**
     * @brief Destructor
     */
    ~FuncSymbolInfo() override;

    /**
     * @brief Gets the stack size required by the function
     * @return Stack size in bytes
     */
    int getStackSize() const { return stack_size_; }

    /**
     * @brief Sets the stack size required by the function
     * @param stack_size Stack size in bytes
     */
    void setStackSize(int stack_size) { stack_size_ = stack_size; }

    /**
     * @brief Gets the return type of the function
     * @return Return type
     */
    DataType getDataType() const override { return return_type_; }

    /**
     * @brief Gets the number of parameters (array length for function)
     * @return Number of parameters
     */
    int getArrayLength() const override { return param_list_.size(); }

    /**
     * @brief Gets array dimensions (empty for functions)
     * @return Empty vector
     */
    std::vector<int> getArrayDimensions() const override { return std::vector<int>(); }

    /**
     * @brief Gets symbol type
     * @return FUNC symbol type
     */
    SymbolType getSymbolType() const override { return SymbolType::FUNC; }

    /**
     * @brief Gets the number of parameters
     * @return Number of parameters
     */
    size_t getParameterCount() const { return param_list_.size(); }

    /**
     * @brief Gets the parameter list
     * @return Vector of parameter symbols
     */
    const std::vector<SymbolInfo*>& getParameterList() const { return param_list_; }

    /**
     * @brief Gets the IR parameter types
     * @return Vector of IR parameter types
     */
    const std::vector<IRType*>& getIRParameterTypes() const { return ir_param_types_; }

    /**
     * @brief Gets the IR arguments
     * @return Vector of IR arguments
     */
    const std::vector<IRArgument*>& getIRArguments() const { return ir_arguments_; }

    /**
     * @brief Gets the base block of the function
     * @return Pointer to the base block
     */
    BlockInfo* getBaseBlock() const { return base_block_; }

    /**
     * @brief Sets the base block of the function
     * @param base_block Base block to set
     */
    void setBaseBlock(BlockInfo* base_block) { base_block_ = base_block; }

    /**
     * @brief Adds a variable parameter to the function
     * @param param_name Parameter name
     * @param line_number Line number where parameter is declared
     * @param data_type Parameter data type
     * @return Pointer to the created parameter symbol
     */
    SymbolInfo* addParameterVariable(const std::string& param_name, int line_number, DataType data_type);

    /**
     * @brief Adds an array parameter to the function
     * @param param_name Parameter name
     * @param line_number Line number where parameter is declared
     * @param data_type Parameter data type
     * @param array_dimensions Array dimensions
     * @param dimension_count Number of dimensions
     * @return Pointer to the created parameter symbol
     */
    SymbolInfo* addParameterArray(const std::string& param_name, int line_number, DataType data_type,
                                 const std::vector<int>& array_dimensions, int dimension_count);

    /**
     * @brief Sets the IR value for this function
     * @param ir_module IR module
     * @param function_type Function type
     */
    void setIRValue(IRModule* ir_module, IRFunction::FuncTy function_type);

private:
    int stack_size_;                           ///< Stack size required by the function
    DataType return_type_;                     ///< Return type of the function
    std::vector<SymbolInfo*> param_list_;      ///< Parameter symbols
    std::vector<IRType*> ir_param_types_;      ///< IR parameter types
    std::vector<IRArgument*> ir_arguments_;    ///< IR arguments
    BlockInfo* base_block_;                    ///< Base block of the function
};


/**
 * @brief Function table for managing function symbols
 */
class FuncTable {
public:
    /**
     * @brief Default constructor
     */
    FuncTable() = default;

    /**
     * @brief Destructor
     */
    ~FuncTable();

    /**
     * @brief Gets the function list
     * @return Map of function names to function symbols
     */
    const std::map<std::string, FuncSymbolInfo*>& getFunctionList() const { return function_list_; }

    /**
     * @brief Gets the current function name
     * @return Current function name
     */
    const std::string& getCurrentFunction() const { return current_function_; }

    /**
     * @brief Sets the current function name
     * @param function_name Function name to set
     */
    void setCurrentFunction(const std::string& function_name) { current_function_ = function_name; }

    /**
     * @brief Gets the stack size for functions
     * @return Stack size in bytes
     */
    int getStackSize() const { return stack_size_; }

    /**
     * @brief Sets the stack size for functions
     * @param stack_size Stack size in bytes
     */
    void setStackSize(int stack_size) { stack_size_ = stack_size; }

    /**
     * @brief Adds a function to the table
     * @param function_name Function name
     * @param function_symbol Function symbol
     */
    void addFunction(const std::string& function_name, FuncSymbolInfo* function_symbol);

    /**
     * @brief Looks up a function by name
     * @param function_name Function name to look up
     * @return Pointer to function symbol or nullptr if not found
     */
    FuncSymbolInfo* lookupFunction(const std::string& function_name) const;

private:
    std::map<std::string, FuncSymbolInfo*> function_list_;  ///< Function symbols
    std::string current_function_;                          ///< Current function name
    int stack_size_;                                        ///< Stack size for functions
};

/**
 * @brief Symbol table for managing variable and constant symbols
 */
class SymbolTable {
public:
    /**
     * @brief Default constructor
     */
    SymbolTable() = default;

    /**
     * @brief Destructor
     */
    ~SymbolTable() = default;

    /**
     * @brief Gets the symbol list
     * @return Map of symbol names to symbols
     */
    const std::map<std::string, SymbolInfo*>& getSymbolList() const { return symbol_list_; }

    /**
     * @brief Gets the current symbol name
     * @return Current symbol name
     */
    const std::string& getCurrentSymbol() const { return current_symbol_; }

    /**
     * @brief Sets the current symbol name
     * @param symbol_name Symbol name to set
     */
    void setCurrentSymbol(const std::string& symbol_name) { current_symbol_ = symbol_name; }

    /**
     * @brief Gets the stack size for symbols
     * @return Stack size in bytes
     */
    int getStackSize() const { return stack_size_; }

    /**
     * @brief Sets the stack size for symbols
     * @param stack_size Stack size in bytes
     */
    void setStackSize(int stack_size) { stack_size_ = stack_size; }

    /**
     * @brief Adds a symbol to the table
     * @param symbol_name Symbol name
     * @param symbol_info Symbol info
     */
    void addSymbol(const std::string& symbol_name, SymbolInfo* symbol_info);

    /**
     * @brief Looks up a symbol by name
     * @param symbol_name Symbol name to look up
     * @return Pointer to symbol or nullptr if not found
     */
    SymbolInfo* lookupSymbol(const std::string& symbol_name) const;

private:
    std::map<std::string, SymbolInfo*> symbol_list_;  ///< Symbol list
    std::string current_symbol_;                      ///< Current symbol name
    int stack_size_;                                  ///< Stack size for symbols
};

/**
 * @brief Block table for managing block information
 */
class BlockTable {
public:
    /**
     * @brief Default constructor
     */
    BlockTable() = default;

    /**
     * @brief Destructor
     */
    ~BlockTable();

    /**
     * @brief Gets the block list
     * @return Vector of block info pointers
     */
    const std::vector<BlockInfo*>& getBlockList() const { return block_list_; }

    /**
     * @brief Gets the stack size for blocks
     * @return Stack size in bytes
     */
    int getStackSize() const { return stack_size_; }

    /**
     * @brief Sets the stack size for blocks
     * @param stack_size Stack size in bytes
     */
    void setStackSize(int stack_size) { stack_size_ = stack_size; }

    /**
     * @brief Adds a block to the table
     * @param block_info Block info to add
     */
    void addBlock(BlockInfo* block_info);

private:
    std::vector<BlockInfo*> block_list_;  ///< Block list
    int stack_size_;                      ///< Stack size for blocks
};


/**
 * @brief Block information for managing symbol scopes
 * 
 * BlockInfo represents a scope in the program and manages the symbol table,
 * block table, and function relationships for that scope.
 */
class BlockInfo {
public:
    /**
     * @brief Constructs a BlockInfo
     * @param parent_block Parent block (nullptr for global scope)
     */
    explicit BlockInfo(BlockInfo* parent_block = nullptr);

    /**
     * @brief Destructor
     */
    virtual ~BlockInfo() = default;

    /**
     * @brief Gets the parent block
     * @return Pointer to parent block
     */
    BlockInfo* getParentBlock() const { return parent_block_; }

    /**
     * @brief Sets the parent block
     * @param parent_block Parent block to set
     */
    void setParentBlock(BlockInfo* parent_block) { parent_block_ = parent_block; }

    /**
     * @brief Gets the function this block belongs to
     * @return Pointer to function symbol
     */
    FuncSymbolInfo* getBelongingFunction() const { return belonging_function_; }

    /**
     * @brief Sets the function this block belongs to
     * @param function Function symbol to set
     */
    void setBelongingFunction(FuncSymbolInfo* function) { belonging_function_ = function; }

    /**
     * @brief Gets the symbol table
     * @return Reference to symbol table
     */
    SymbolTable& getSymbolTable() { return symbol_table_; }

    /**
     * @brief Gets the symbol table (const version)
     * @return Const reference to symbol table
     */
    const SymbolTable& getSymbolTable() const { return symbol_table_; }

    /**
     * @brief Gets the block table
     * @return Reference to block table
     */
    BlockTable& getBlockTable() { return block_table_; }

    /**
     * @brief Gets the block table (const version)
     * @return Const reference to block table
     */
    const BlockTable& getBlockTable() const { return block_table_; }

    /**
     * @brief Looks up a symbol in this block and parent blocks
     * @param symbol_name Symbol name to look up
     * @return Pointer to symbol or nullptr if not found
     */
    SymbolInfo* lookupSymbol(const std::string& symbol_name) const;

    /**
     * @brief Adds a symbol to this block's symbol table
     * @param symbol_name Symbol name
     * @param symbol_info Symbol info
     */
    void addSymbol(const std::string& symbol_name, SymbolInfo* symbol_info);

    /**
     * @brief Adds a sub-block to this block
     * @param block_info Block info to add
     */
    void addSubBlock(BlockInfo* block_info);

protected:
    BlockInfo* parent_block_;                    ///< Parent block
    FuncSymbolInfo* belonging_function_;         ///< Function this block belongs to
    SymbolTable symbol_table_;                   ///< Symbol table for this block
    BlockTable block_table_;                     ///< Block table for sub-blocks
};

    virtual ConstSymbolInfo *addNewConst(const std::string &name, int line, DataType dataType);

    virtual VarSymbolInfo *addNewVar(const std::string &name, int line, DataType dataType);

    virtual ConstArraySymbolInfo *
    addNewConstArray(const std::string &name, int line, DataType dataType, const std::vector<int> arraySize,
                     int dimension);

    virtual VarArraySymbolInfo *
    addNewVarArray(const std::string &name, int line, DataType dataType, const std::vector<int> arraySize,
                   int dimension);

    BlockInfo *addNewBlock();

    BlockInfo *addNewBlock(FuncSymbolInfo *belongTo);
    //两个addNewBlock，主要是看这个block是不是函数
    //如果说是一个函数，那么在new一个新块的时候，自然的这个函数的形参就要加到这个块的符号表里面去

    BlockInfo(BlockInfo *parentBlock);

    BlockInfo(BlockInfo *parentBlock, FuncSymbolInfo *belongTo, const std::vector<SymbolInfo *> &paramList);

    ~BlockInfo(){};
    //如果说是直接隶属于函数的块，则需要记录belongto,同时所有函数的形参都作为这个块的符号表而存在
};

class GlobalBlock : public BlockInfo {
private:
    FuncTable funcTable;

public:
    FuncSymbolInfo *lookUpFunc(std::string symbolName);

    FuncSymbolInfo *addNewFunc(const std::string &name, int line, DataType returnType);

    ConstSymbolInfo *addNewConst(const std::string &name, int line, DataType dataType) override;

    VarSymbolInfo *addNewVar(const std::string &name, int line, DataType dataType) override;

    ConstArraySymbolInfo *
    addNewConstArray(const std::string &name, int line, DataType dataType, const std::vector<int> arraySize,
                     int dimension) override;

    VarArraySymbolInfo *
    addNewVarArray(const std::string &name, int line, DataType dataType, const std::vector<int> arraySize,
                   int dimension) override;

    void initIOFunction(IRModule* irmodule);

    GlobalBlock();

    ~GlobalBlock() = default;
};

/*在初始化一个块的时候，本来应该这个块的符号表和子块都是空的·*/

#endif