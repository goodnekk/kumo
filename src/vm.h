#pragma once
#include "log.h"
#include <vector>

using namespace std;

class vm {
    private:
        int stack[10];
        int stackPoint;

        vector<int> program;
        int programPoint;

        void push_stack(int val);
        int pop_stack();
        int fetch();

    public:
        void load(vector<int> prg);
        void run();

};
