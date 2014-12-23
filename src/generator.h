#pragma once
#include "log.h"
#include <vector>
#include <string>

#include "lexemes.h"
#include "program.h"

using namespace std;

class generator{
private:
    //vector<int> program; //this will contain the program
    program p;
    void standardfunctions();
    void virtual_function(string name, int virtualpointer);

public:
    vector< vector<int> > generate(lexemes::node * a);
};
