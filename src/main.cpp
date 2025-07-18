#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>

#include "IR/IRModule.h"
#include "FrontEnd.h"
#include "Optimizer.h"
#include "BackEnd.h"
#include "Interpreter/Interpreter.h"
#include "utils/CLParser.h"
#include "utils/ErrorHandler.h"

using namespace antlr4;

class CompilerDriver {
private:
    std::unique_ptr<CLParser> parser_;
    std::unique_ptr<IRModule> ir_module_;
    std::unique_ptr<FrontEnd> frontend_;
    std::unique_ptr<Optimizer> optimizer_;
    std::unique_ptr<Interpreter> interpreter_;
    std::unique_ptr<BackEnd> backend_;

public:
    CompilerDriver() = default;
    ~CompilerDriver() = default;

    bool initialize(int argc, const char* argv[]) {
        try {
            parser_ = std::make_unique<CLParser>();
            setupCommandLineParser();
            
            if (!parser_->parse(argc, argv)) {
                return false;
            }

            return true;
        } catch (const std::exception& e) {
            ErrorHandler::reportError("Failed to initialize compiler: " + std::string(e.what()));
            return false;
        }
    }

    bool compile() {
        try {
            if (!loadSourceFile()) {
                return false;
            }

            if (!performFrontendAnalysis()) {
                return false;
            }

            if (!performOptimization()) {
                return false;
            }

            if (!generateOutput()) {
                return false;
            }

            return true;
        } catch (const std::exception& e) {
            ErrorHandler::reportError("Compilation failed: " + std::string(e.what()));
            return false;
        }
    }

private:
    void setupCommandLineParser() {
        parser_->add("simulate");
        parser_->add("verbose");
        parser_->add("c");
        parser_->add("emit-IR");
    }

    bool loadSourceFile() {
        std::string file_path = parser_->getFilePath();
        std::ifstream source_stream(file_path);
        
        if (!source_stream.is_open()) {
            ErrorHandler::reportError("Failed to open source file: " + file_path);
            return false;
        }

        ir_module_ = std::make_unique<IRModule>(file_path);
        frontend_ = std::make_unique<FrontEnd>(&source_stream, ir_module_.get());
        
        return true;
    }

    bool performFrontendAnalysis() {
        try {
            frontend_->analyze();
            return true;
        } catch (const std::exception& e) {
            ErrorHandler::reportError("Frontend analysis failed: " + std::string(e.what()));
            return false;
        }
    }

    bool performOptimization() {
        try {
            optimizer_ = std::make_unique<Optimizer>(ir_module_.get());
            optimizer_->build();
            optimizer_->setLevel(parser_->getLevel());
            optimizer_->run();
            return true;
        } catch (const std::exception& e) {
            ErrorHandler::reportError("Optimization failed: " + std::string(e.what()));
            return false;
        }
    }

    bool generateOutput() {
        try {
            if (parser_->get("emit-IR")) {
                frontend_->print();
            }

            if (parser_->get("simulate") || parser_->get("verbose")) {
                return executeInterpreter();
            } else {
                return generateTargetCode();
            }
        } catch (const std::exception& e) {
            ErrorHandler::reportError("Code generation failed: " + std::string(e.what()));
            return false;
        }
    }

    bool executeInterpreter() {
        interpreter_ = std::make_unique<Interpreter>(ir_module_.get());
        Interpreter::debugOpt = parser_->get("verbose");
        
        int result = interpreter_->interpret();
        
        if (parser_->get("c")) {
            std::cout << "inst_cnt = " << Interpreter::getInstCnt() << std::endl;
        }
        
        return result == 0;
    }

    bool generateTargetCode() {
        backend_ = std::make_unique<BackEnd>(ir_module_.get());
        backend_->print();
        return true;
    }
};

int main(int argc, const char* argv[]) {
    try {
        CompilerDriver driver;
        
        if (!driver.initialize(argc, argv)) {
            return 1;
        }
        
        if (!driver.compile()) {
            return 1;
        }
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}