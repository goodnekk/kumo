#include "stack.h"

stack::stack(){
    stackPoint = 0;
}

void stack::push(variable val){
    stackArray[stackPoint] = val;
    stackPoint++;
}

variable stack::pop(){
    stackPoint--;
    return stackArray[stackPoint];
}
