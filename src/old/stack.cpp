#include "stack.h"

stack::stack(){
    stackPoint = 0;
}

void stack::push(variable val){
    if(stackPoint==50){
        LOG_ERROR("Stack overflow!");
        STOP();
    }
    stackArray[stackPoint] = val;
    stackPoint++;
}

variable stack::pop(){
    stackPoint--;
    return stackArray[stackPoint];
}
