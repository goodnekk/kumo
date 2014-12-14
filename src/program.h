#pragma once

#include <vector>
#include <string>
#include "log.h"

using namespace std;

class program{
private:
    vector<int> list;
    vector<string> variables;
public:
    void push_instruction(int i);
    int get_variable(string n);
    int assign_variable(string n);

    vector<int> get_list();
};
