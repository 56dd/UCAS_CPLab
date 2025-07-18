#ifndef COMPILER_BACKEND_H
#define COMPILER_BACKEND_H

#include <memory>
#include <string>
#include <ostream>

#include "RISC-V/Module.h"

class IRModule;

/**
 * @brief Backend compiler component responsible for target code generation
 */
class BackEnd {
public:
    /**
     * @brief Constructs a BackEnd with IR module
     * @param ir_module Pointer to the IR module to translate
     */
    explicit BackEnd(IRModule* ir_module);

    /**
     * @brief Destructor
     */
    ~BackEnd() = default;

    /**
     * @brief Generates and prints target code to standard output
     */
    void print();

    /**
     * @brief Generates target code to specified output stream
     * @param output_stream Output stream to write target code to
     */
    void print(std::ostream& output_stream);

    /**
     * @brief Gets the generated RISC-V module
     * @return Reference to the RISC-V module
     */
    const RISCV::Module& getRISCVModule() const { return riscv_module_; }

    /**
     * @brief Gets the source file name
     * @return Source file name
     */
    std::string getSourceFileName() const { return source_file_name_; }

private:
    IRModule* ir_module_;
    RISCV::Module riscv_module_;
    std::string source_file_name_;

    /**
     * @brief Generates target code from IR module
     * @throws std::runtime_error if code generation fails
     */
    void generateTargetCode();

    /**
     * @brief Prints the generated target code to output stream
     * @param output_stream Output stream to write to
     * @param source_file_name Name of the source file
     */
    void printTargetCode(std::ostream& output_stream, const std::string& source_file_name);

    /**
     * @brief Prints file header information
     * @param output_stream Output stream to write to
     * @param source_file_name Name of the source file
     */
    static void printFileHeader(std::ostream& output_stream, const std::string& source_file_name);

    /**
     * @brief Prints environment setup code
     * @param output_stream Output stream to write to
     */
    static void printEnvironmentSetup(std::ostream& output_stream);

    /**
     * @brief Validates the internal state
     * @throws std::runtime_error if validation fails
     */
    void validateState() const;
};

#endif // COMPILER_BACKEND_H
