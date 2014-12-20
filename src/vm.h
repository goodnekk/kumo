#pragma once
#include "log.h"

#include <vector>
#include "stack.h"

using namespace std;

class vm {
    private:
        stack varstack;
        stack callstack;

        int ram[10]; //random acces storage for local variables

        vector< vector<int> > program;
        int programPoint; //points to the current operation
        int functionPoint; //points to the current function

        //void push_callstack(int val);
        //int pop_callstack();

        void store_ram(int reg, int val);
        int get_ram(int reg);
        int fetch();

        //void call_virtual(int n);
    public:
        void load(vector< vector<int> > prg);
        void run();
};
