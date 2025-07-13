#include "BackEnd.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <utility>
#include "IR/IRModule.h"

BackEnd::BackEnd(IRModule *ir) : ir(ir), module(ir) {

}

void BackEnd::print() {
    std::string strsrc = ir->getName();
    std::filesystem::path inputFilePath(strsrc);
    /**替换test**/
    std::string strTest = "test";
    std::string strIRgen = "Codegen";
    size_t pos1 = strsrc.find(strTest);  // 查找目标子串的位置
    if (pos1 != std::string::npos) {
        strsrc.replace(pos1, strTest.length(), strIRgen);  // 替换子串
    }

    /**替换cact**/
    std::string strCact = ".cact";
    std::string strIr = ".s";
    size_t pos2 = strsrc.find(strCact);
    if (pos2 != std::string::npos) {
        strsrc.replace(pos2, strCact.length(), strIr);  // 替换子串
    }

    std::filesystem::path outputFilePath(strsrc);
    std::string dirPath = outputFilePath.parent_path().string();
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }
    std::ofstream outputFile(outputFilePath.string());

    internalPrint(outputFile, inputFilePath.filename().string());

    outputFile.close();
}

void BackEnd::internalPrint(std::ostream &O, const std::string &srcFileName) {
    printFileName(O, srcFileName);
    printEnv(O);
    module.print(O);
}

void BackEnd::printFileName(std::ostream &O, const std::string &srcFileName) {
    O << "\t.file";
    O << "\t\"" << srcFileName << "\"" << std::endl;
}

void BackEnd::printEnv(std::ostream &O) {
    O << "\t.option nopic" << std::endl;
    O << "\t.attribute arch, \"rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0\"" << std::endl;
    O << "\t.attribute unaligned_access, 0" << std::endl;
    O << "\t.attribute stack_align, 16" << std::endl;
    O << std::endl;
}
