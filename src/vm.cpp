#include "vm.h"

void vm::load(program p){
    code = p.code;
    constants = p.constants;
    library = p.library;

    codePoint = -1;
    stackPoint = -1;
}

void vm::run(){
    bool running = true;
    while(running){
        codePoint++;
        LOG_DEBUG("VM: "<<codePoint<<" "<<bytecodes::names[code[codePoint]]);

        switch(code[codePoint]){
            case bytecodes::END:
                running = false;
                break;
            case bytecodes::PUSH_C:
                codePoint++;
                stackPoint++;
                stack[stackPoint] = constants[code[codePoint]];
                break;
            case bytecodes::POP:
                break;
            case bytecodes::PUSH_R:
                break;
            case bytecodes::POP_R:
                break;
            case bytecodes::ADD:
                stackPoint--;
                stack[stackPoint] = variable(stack[stackPoint].get_number() + stack[stackPoint+1].get_number());
                break;
            case bytecodes::SUB:
                stackPoint--;
                stack[stackPoint] = variable(stack[stackPoint].get_number() - stack[stackPoint+1].get_number());
                break;
            case bytecodes::MULT:
                stackPoint--;
                stack[stackPoint] = variable(stack[stackPoint].get_number() * stack[stackPoint+1].get_number());
                break;
            case bytecodes::DIV:
                stackPoint--;
                stack[stackPoint] = variable(stack[stackPoint].get_number() / stack[stackPoint+1].get_number());
                break;
            case bytecodes::ISEQ:
                break;
            case bytecodes::ISHI:
                break;
            case bytecodes::ISLO:
                break;
            case bytecodes::CALL:
                break;
            case bytecodes::RETURN:
                break;
            case bytecodes::V_CALL:
                codePoint++;
                library.call(code[codePoint], stack, stackPoint);
                break;
            case bytecodes::ISTRUE:
                break;
            case bytecodes::GOTO:
                break;
            default:
                LOG_DEBUG("VM: unknown bytecode!");
        }


        if(codePoint>=code.size()){
            running = false;
        }
    }
}
