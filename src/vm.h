#pragma once
#include "log.h"

#include <vector>
#include "variable.h"

using namespace std;

class vm {
private:

    vector <int> program;
    int programPoint; //points to the current operation

    variable stack[100];
    int stackPoint;

    variable ram[100]; //random acces storage for variables


    int functionPoint; //points to the current function

public:
    void load(vector <int> p);
    void run();
};
