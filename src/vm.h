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

    vector <vector <int> > code;
    int codePoint; //points to the current operation

    variable stack[100];
    int stackPoint;
    int framePoint;

    //int callStack[100];
    //int callStackPoint;

    int functionPoint; //points to the current function

    variable ram[100]; //random acces storage for global variables


    vector <variable> constants;

    libs library;

public:
    void load(program p);
    void run();
};
