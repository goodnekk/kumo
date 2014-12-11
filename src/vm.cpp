//author: Marcel Goethals
//stack-based virtual machine loads a vector of ints and performs

#include "vm.h"
#include "instructions.h"

void vm::load(vector<int> prg){
    program = prg;
    programPoint = 0;
    stackPoint = 0;
}

void vm::run(){
    while(programPoint<program.size()){
        int instruction = fetch();

        switch(instruction){
            case instructions::PUSH_C:
                LOG_DEBUG("PUSH_C");
                push_stack(fetch());
                break;
            case instructions::ADD:
                LOG_DEBUG("ADD");

                push_stack(pop_stack()+pop_stack());
                break;
            case instructions::PRINT:
                LOG(pop_stack());
                break;
            default:
                LOG_ERROR("VM: Unknown instruction: "<< instruction);
        }
    }
}

int vm::fetch(){
    int a = program[programPoint];
    programPoint++;
    return a;
}

void vm::push_stack(int val){
    stack[stackPoint] = val;
    stackPoint++;
}

int vm::pop_stack(){
    stackPoint--;
    return stack[stackPoint];
}
