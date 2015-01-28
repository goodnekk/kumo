#include "vm.h"

void vm::load(program p){
    code = p.code;
    constants = p.constants;
    library = p.library;

    codePoint = -1;
    stackPoint = -1;
    framePoint = -1;
    functionPoint = 0;
}

void vm::run(){
    bool running = true;
    while(running){
        codePoint++;
        LOG_DEBUG("VM: "<<functionPoint<<" "<<codePoint<<" "<<bytecodes::names[code[functionPoint][codePoint]]);

        switch(code[functionPoint][codePoint]){
            case bytecodes::END:
                running = false;
                break;

            case bytecodes::PUSH_C:
                codePoint++;
                stackPoint++;
                stack[stackPoint] = constants[code[functionPoint][codePoint]];
                break;

            case bytecodes::POP:
                break;

            case bytecodes::PUSH_R: //push from ram
                codePoint++;
                stackPoint++;
                stack[stackPoint] = ram[code[functionPoint][codePoint]];
                break;

            case bytecodes::POP_R: //pop to ram
                codePoint++;
                ram[code[functionPoint][codePoint]] = stack[stackPoint];
                stackPoint--;
                break;

            case bytecodes::PUSH_L:
                codePoint++;
                stackPoint++;
                stack[stackPoint] = stack[framePoint + code[functionPoint][codePoint]];
                break;

            case bytecodes::POP_L:
                codePoint++;
                stack[framePoint + code[functionPoint][codePoint]] = stack[stackPoint];
                stackPoint--;
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
                //push current position onto the callstack
                stackPoint++;
                stack[stackPoint] = variable(variabletypes::POINTER,functionPoint);

                stackPoint++;
                stack[stackPoint] = variable(variabletypes::POINTER,codePoint+2);

                stackPoint++;
                stack[stackPoint] = variable(variabletypes::POINTER,framePoint);

                framePoint = stackPoint;

                codePoint++;
                codePoint++;
                LOG_DEBUG("VM: Locals: "<<code[functionPoint][codePoint]);
                stackPoint += code[functionPoint][codePoint];
                functionPoint = ram[code[functionPoint][codePoint-1]].get_pointer();

                codePoint = -1;
                //make space for locals
                break;

            case bytecodes::RETURN:
                LOG_DEBUG("VM: RETURN FROM: "<<functionPoint);
                LOG_DEBUG("VM: stack: "<<stackPoint);
                //LOG_DEBUG("VM: frame: "<<framePoint);

                LOG_DEBUG("VM: stack: "<<stackPoint);
                stackPoint = framePoint;

                //pop off arguments
                codePoint++;
                stackPoint -= code[functionPoint][codePoint]+3;
                LOG_DEBUG("VM: stack: "<<stackPoint);
                //return frame
                functionPoint = stack[framePoint-2].get_pointer();
                codePoint = stack[framePoint-1].get_pointer();
                framePoint = stack[framePoint].get_pointer();

                break;

            case bytecodes::V_CALL:
                codePoint++;
                library.call(code[functionPoint][codePoint], stack, &stackPoint);
                break;

            case bytecodes::ISTRUE:
                break;

            case bytecodes::GOTO:
                break;

            default:
                LOG_ERROR("VM: unknown bytecode!");
        }

        LOG_DEBUG("VM: Stack: "<<stackPoint);
    }
}
