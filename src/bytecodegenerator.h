#pragma once

#include "bytecodes.h"
#include "lexemetypes.h"

#include "parsenode.h"
#include "log.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class bytecodegenerator{
private:
    vector <string> variables;
    vector <int> code;

    void block(parsenode * node);
    void call(parsenode * node);
    void variable(parsenode * node);
    void constant(parsenode * node);

    void loadStdlib();
public:
    void generate(parsenode * root);

};
