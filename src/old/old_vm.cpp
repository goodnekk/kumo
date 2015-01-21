//author: Marcel Goethals
//stack-based virtual machine loads a vector of ints and performs

#include "vm.h"
#include "instructions.h"
#include "standardlib.h"

void vm::load(program prg){
    programObj = prg.get_list();
    constant_pool = prg.get_constants();

    programPoint = 0;
    functionPoint = 0;
    LOG_DEBUG("VM Loaded program with: "<<programObj.size()<<" functions.");
}

void vm::run(){
    //loop through each operation untill the end of the program is reached
    while(programPoint<programObj[functionPoint].size()){
        int instruction = fetch();
        int var = 0;
        switch(instruction){
            case instructions::PUSH_C:
                var = fetch();
                LOG_DEBUG("PUSH_C: "<<var);
                varstack.push(constant_pool.at(var));
                break;
            case instructions::POP: //FIXME: deprecated?
                varstack.pop();
                LOG_DEBUG("POP");
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
                varstack.push(variable(varstack.pop().get()+varstack.pop().get()));
                break;
            case instructions::SUB:
                LOG_DEBUG("SUB");
                varstack.push(variable(varstack.pop().get()-varstack.pop().get()));
                break;
            case instructions::MULT:
                LOG_DEBUG("MULT");
                varstack.push(variable(varstack.pop().get()*varstack.pop().get()));
                break;
            case instructions::DIV:
                LOG_DEBUG("DIV");
                varstack.push(variable(varstack.pop().get()/varstack.pop().get()));
                break;
            case instructions::ISEQ:
                LOG_DEBUG("ISEQ");
                if(varstack.pop().get()==varstack.pop().get()){
                    varstack.push(variable(true));
                } else {
                    varstack.push(variable(false));
                }
                break;
            case instructions::ISHI:
                LOG_DEBUG("ISLO");
                if(varstack.pop().get()>varstack.pop().get()){
                    varstack.push(variable(true));
                } else {
                    varstack.push(variable(false));
                }
                break;
            case instructions::ISLO:
                LOG_DEBUG("ISLO");
                if(varstack.pop().get()<varstack.pop().get()){
                    varstack.push(variable(true));
                } else {
                    varstack.push(variable(false));
                }
                break;
            case instructions::CALL:
                var = varstack.pop().get();
                LOG_DEBUG("CALL "<< var);
                callstack.push(variable(programPoint));
                callstack.push(variable(functionPoint));
                functionPoint = var;
                programPoint = 0;
                break;
            case instructions::RETURN:
                functionPoint = callstack.pop().get();
                programPoint = callstack.pop().get();
                LOG_DEBUG("RETURN "<< functionPoint);
                break;
            case instructions::V_CALL:
                var = varstack.pop().get();
                LOG_DEBUG("V_CALL "<< var);
                standardlib::call(var, &varstack);
                break;
            case instructions::ISTRUE:
                LOG_DEBUG("ISTRUE"); //if not true move fwd by amount
                if(!varstack.pop().get_boolean()){
                    LOG_DEBUG("False");
                    varstack.pop(); //pop off potential link
                    programPoint += fetch();//skip next commands;
                } else {
                    LOG_DEBUG("True");
                    fetch();
                }
                break;
            case instructions::GOTO:
                programPoint = fetch();
                LOG_DEBUG("GOTO "<< programPoint);
                break;
            default:
                LOG_ERROR("VM: Unknown instruction: "<< instruction);
        }
    }
}

int vm::fetch(){
    int a = programObj[functionPoint][programPoint];
    //LOG_DEBUG(functionPoint<<"::"<<programPoint<<"::"<<a);
    programPoint++;
    return a;
}

void vm::store_ram(variable reg, variable val){
    ram[reg.get()]=val;
}

variable vm::get_ram(variable reg){
    return ram[reg.get()];
}
