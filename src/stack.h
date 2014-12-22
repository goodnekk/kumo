#pragma once

class stack{
    private:
        int stackArray[100];
        int stackPoint;
    public:
        stack();
        void push(int val);
        int pop();
};
