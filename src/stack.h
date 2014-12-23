#pragma once
#include "log.h"
#include "variable.h"

class stack{
    private:
        variable stackArray[50];
        int stackPoint;
    public:
        stack();
        void push(variable val);
        variable pop();
};
