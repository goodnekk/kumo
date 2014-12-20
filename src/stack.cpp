#include "stack.h"

stack::stack(){
    stackPoint = 0;
}

void stack::push(int val){
    stackArray[stackPoint] = val;
    stackPoint++;
}

int stack::pop(){
    stackPoint--;
    return stackArray[stackPoint];
}
