#pragma once
#include "log.h"

#include <vector>
#include "stack.h"
#include "program.h"
#include "variable.h"

using namespace std;

class vm {
    private:
        stack varstack;
        stack callstack;

        variable ram[100]; //random acces storage for variables

        vector<vector<int> > programObj;
        vector<variable> constant_pool;

        int programPoint; //points to the current operation
        int functionPoint; //points to the current function

        //void push_callstack(int val);
        //int pop_callstack();

        void store_ram(variable reg, variable val);
        variable get_ram(variable reg);
        int fetch();

        //void call_virtual(int n);
    public:
        void load(program prg);
        void run();
};
