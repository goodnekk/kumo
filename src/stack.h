#pragma once

class stack{
    private:
        int stackArray[10];
        int stackPoint;
    public:
        stack();
        void push(int val);
        int pop();
};
