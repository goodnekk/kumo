#pragma once

#include <vector>
#include <string>
#include "log.h"
#include "variable.h"

using namespace std;

class program{
private:

    int current_function;
    vector< vector<int> > list;
    vector<string> variables;
    vector<int> call_stack;
    vector<variable> constant_pool;

public:
    program();
    void push_instruction(int i);
    int get_position();

    int push_constant(variable v);
    int get_variable(string n);
    int assign_variable(string n);
    int force_variable(string n);

    int new_scope();
    void pop_scope(int n);

    int new_function();
    void pop_function();

    vector< vector<int> > get_list();
    vector<variable> get_constants();
};
