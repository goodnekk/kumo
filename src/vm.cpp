//author: Marcel Goethals
//stack-based virtual machine loads a vector of ints and performs

#include "vm.h"
#include "instructions.h"

void vm::load(vector< vector<int> > prg){
    LOG_DEBUG("VM Loaded program with: "<<prg.size()<<" functions.");
    program = prg;
    programPoint = 0;
    functionPoint = 0;
    stackPoint = 0;
    callstackPoint = 0;
}

void vm::run(){
    //loop through each operation untill the end of the program is reached
    while(programPoint<program[functionPoint].size()){
        int instruction = fetch();
        int var = 0;
        switch(instruction){
            case instructions::PUSH_C:
                var = fetch();
                LOG_DEBUG("PUSH_C: "<<var);
                push_stack(var);
                break;
            case instructions::PUSH_R:
                var = fetch();
                LOG_DEBUG("PUSH_R: "<<var);
                push_stack(get_ram(var));
                break;
            case instructions::POP_R:
                var = fetch();
                LOG_DEBUG("POP_R: "<<var);
                store_ram(var, pop_stack());
                break;
            case instructions::ADD:
                LOG_DEBUG("ADD");
                push_stack(pop_stack()+pop_stack());
                break;
            case instructions::SUB:
                LOG_DEBUG("SUB");
                push_stack(pop_stack()-pop_stack());
                break;
            case instructions::MULT:
                LOG_DEBUG("MULT");
                push_stack(pop_stack()*pop_stack());
                break;
            case instructions::DIV:
                LOG_DEBUG("DIV");
                push_stack(pop_stack()/pop_stack());
                break;
            case instructions::CALL:
                var = pop_stack();
                LOG_DEBUG("CALL "<< var);
                push_callstack(programPoint);
                push_callstack(functionPoint);
                functionPoint = var;
                programPoint = 0;
                break;
            case instructions::RETURN:
                functionPoint = pop_callstack();
                programPoint = pop_callstack();
                LOG_DEBUG("RETURN "<< functionPoint);
                break;
            case instructions::V_CALL:
                var = pop_stack();
                LOG_DEBUG("V_CALL "<< var);
                call_virtual(var);
                break;
            default:
                LOG_ERROR("VM: Unknown instruction: "<< instruction);
        }
    }
}

int vm::fetch(){
    int a = program[functionPoint][programPoint];
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

void vm::push_callstack(int val){
    callstack[callstackPoint] = val;
    callstackPoint++;
}

int vm::pop_callstack(){
    callstackPoint--;
    return callstack[callstackPoint];
}

void vm::store_ram(int reg, int val){
    ram[reg]=val;
}

int vm::get_ram(int reg){
    return ram[reg];
}

void vm::call_virtual(int n){
    switch (n){
        case 0:
            LOG(pop_stack());
            break;
        default:
        LOG_ERROR("VM: Unknown virtual function: "<< n);
    }
}
