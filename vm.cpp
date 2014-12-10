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
                cout<<"PUSH_C"<<endl;
                push_stack(fetch());
                break;
            case instructions::ADD:
                cout<<"ADD"<<endl;

                push_stack(pop_stack()+pop_stack());
                break;
            case instructions::PRINT:
                cout<<"> "<<pop_stack()<<endl;
                break;
            default:
                cout<<"unknown instruction"<<endl;
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
