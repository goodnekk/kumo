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
            case instructions::RETURNTO: //return and call the same instruction
                functionPoint = callstack.pop();
                programPoint = callstack.pop()-7;
                LOG_DEBUG("RETURNTO "<< functionPoint);
                break;
            case instructions::V_CALL:
                var = varstack.pop();
                LOG_DEBUG("V_CALL "<< var);
                standardlib::call(var, &varstack);
                break;
            case instructions::ISTRUE:
                var = varstack.pop();
                LOG_DEBUG("ISTRUE "<< var); //if not true goto
                if(var!=1){
                    programPoint += fetch();//skip next command;
                } else {
                    fetch();
                }
                break;
            case instructions::GOTO:
                programPoint = fetch();
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

void vm::store_ram(int reg, int val){
    ram[reg]=val;
}

int vm::get_ram(int reg){
    return ram[reg];
}
