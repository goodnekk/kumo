#pragma once
#include "log.h"

#include <vector>
#include "variable.h"
#include "bytecodes.h"
#include "program.h"
#include "libs.h"

using namespace std;

class vm {
private:

    vector <int> code;
    int codePoint; //points to the current operation

    variable stack[100];
    int stackPoint;

    variable ram[100]; //random acces storage for variables
    int functionPoint; //points to the current function

    vector <variable> constants;

    libs library;
    
public:
    void load(program p);
    void run();
};
