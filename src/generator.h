#pragma once
#include "log.h"
#include <vector>

#include "lexemes.h"
#include "program.h"

using namespace std;

class generator{
private:
    //vector<int> program; //this will contain the program
    program p;
public:
    vector< vector<int> > generate(lexemes::node * a);
};
