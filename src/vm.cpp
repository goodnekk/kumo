//author: Marcel Goethals
//stack-based virtual machine loads a vector of ints and performs

#include "vm.h"
#include "instructions.h"
#include "standardlib.h"

void vm::load(vector< vector<int> > prg){
    LOG_DEBUG("VM Loaded program with: "<<prg.size()<<" functions.");
    program = prg;
    programPoint = 0;
    functionPoint = 0;
    //stackPoint = 0;
    //callstackPoint = 0;
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
                varstack.push(var);
                break;
            case instructions::PUSH_R:
                var = fetch();
                LOG_DEBUG("PUSH_R: "<<var);
                varstack.push(get_ram(var));
                break;
            case instructions::POP_R:
                var = fetch();
                LOG_DEBUG("POP_R: "<<var);
                store_ram(var, varstack.pop());
                break;
            case instructions::ADD:
                LOG_DEBUG("ADD");
                varstack.push(varstack.pop()+varstack.pop());
                break;
            case instructions::SUB:
                LOG_DEBUG("SUB");
                varstack.push(varstack.pop()-varstack.pop());
                break;
            case instructions::MULT:
                LOG_DEBUG("MULT");
                varstack.push(varstack.pop()*varstack.pop());
                break;
            case instructions::DIV:
                LOG_DEBUG("DIV");
                varstack.push(varstack.pop()/varstack.pop());
                break;
            case instructions::CALL:
                var = varstack.pop();
                LOG_DEBUG("CALL "<< var);
                callstack.push(programPoint);
                callstack.push(functionPoint);
                functionPoint = var;
                programPoint = 0;
                break;
            case instructions::RETURN:
                functionPoint = callstack.pop();
                programPoint = callstack.pop();
                LOG_DEBUG("RETURN "<< functionPoint);
                break;
            case instructions::V_CALL:
                var = varstack.pop();
                LOG_DEBUG("V_CALL "<< var);
                standardlib::call(var, &varstack);
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

/*
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
*/

void vm::store_ram(int reg, int val){
    ram[reg]=val;
}

int vm::get_ram(int reg){
    return ram[reg];
}
