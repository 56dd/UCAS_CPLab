#include <cassert>
#include "CLParser.h"


void CLParser::add(const std::string &name) {
    if (argTable.count(name) > 0) {
        assert(0 && "add same arg to parser");
    }
    argTable[name] = false;
}


bool CLParser::get(const std::string &name) {
    if (argTable.count(name) == 0) {
        assert(0 && "arg does not exist");
    }
    return argTable[name];
}

void CLParser::parse(int argc, const char **argv) {
    for (int i = 1; i < argc; ++i) {
        std::string st(argv[i]);
        if (st[0] == '-') {
            st = st.substr(1);
            if (argTable.count(st) == 0 && st[0] != 'O')
                assert(0 && "arg does not exist");
            if (st[0] == 'O') {
                if (level != -1)
                    assert(0 && "arg redefine");
                if (st == "O0")
                    level = 0;
                else if (st == "O1")
                    level = 1;
                else if (st == "O2")
                    level = 2;
                else
                    assert(0 && "arg does not exist");
            } else
                argTable[st] = true;
        } else {
            if (filePath.empty()) {
                if (st[0] != '/' && st[0] != '.')
                    st = "./" + st;
                filePath = st;
            } else
                assert(0 && "too many files");
        }
    }
    if (level == -1)
        level = 0;
}

const std::string &CLParser::getFilePath() const {
    return filePath;
}

int CLParser::getLevel() const {
    return level;
}
