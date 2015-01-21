#pragma once

#include "bytecodes.h"
#include "lexemetypes.h"

#include "parsenode.h"
#include "variable.h"
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
    vector <variable> constants;

    //vector <string> variables;

    map <string, vector <int> > templateTable;

    vector <int> code;

    void analize(parsenode * node);
    void call(parsenode * node);
    void constant(parsenode * node);

    void loadStdlib();
    void pushCode(int command);
    void pushCode(vector <int> commands);

public:
    void generate(parsenode * root);

};
