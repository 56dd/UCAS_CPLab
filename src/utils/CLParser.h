#ifndef COMPILER_CLPARSER_H
#define COMPILER_CLPARSER_H


#include <map>
#include <string>
#include <any>

class CLParser {
public:
    void add(const std::string &name);

    bool get(const std::string &name);

    void parse(int argc, const char *argv[]);

    const std::string &getFilePath() const;

    int getLevel() const;

private:
    std::map<std::string, bool> argTable;
    std::string filePath;
    int level = -1;
};


#endif //COMPILER_CLPARSER_H
