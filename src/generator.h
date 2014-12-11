#pragma once
#include "log.h"
#include <vector>

#include "lexemes.h"

using namespace std;
class generator{
private:
    vector<int> program; //this will contain the program
public:
    vector<int> generate(lexemes::node * a);
};
