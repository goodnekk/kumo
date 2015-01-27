#pragma once

#include "bytecodes.h"
#include "lexemetypes.h"

#include "parsenode.h"
#include "variable.h"
#include "program.h"

#include "log.h"

#include "libs.h"

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>


using namespace std;

class bytecodegenerator{
private:
    vector <vector <int> > code;
    vector <int> blockStack;

    vector <variable> constants;
    vector <string> variables;

    vector <string> arguments;

    int scopePointer;

    map <string, vector <int> > templateTable;
    libs library;

    void analize(parsenode * node);
    void children(parsenode * node);

    void block(parsenode * node);
    void assignment(parsenode * node);
    void var(parsenode * node);

    void call(parsenode * node);
    void constant(parsenode * node);

    void declaration(parsenode * node);
    void nameslist();
    void name(parsenode * node);

    void loadStdlib();


    void pushCode(int command);
    void pushCode(vector <int> commands);

public:
    program generate(parsenode * root);

};
