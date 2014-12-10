#pragma once
#include <iostream>
#include <vector>

#include "lexemes.h"

using namespace std;
class generator{
private:
    vector<int> program; //this will contain the program
public:
    void push(int code);
    vector<int> generate(lexemes::node * a);
};
