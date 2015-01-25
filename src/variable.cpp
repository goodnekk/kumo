#include "variable.h"
variable::variable(){
}

variable::variable(float n){ //FIXME: ADD type here
    number = n;
    type = variabletypes::NUMBER;
}

variable::variable(variabletypes t, int i){
    type = t;
    switch(type){
        case variabletypes::POINTER:
            pointer = i;
            break;
        default:
            LOG_ERROR("UNKNOWN VARIABLE TYPE");
            STOP();
    }
}

variable::variable(variabletypes t, string s){
    type = t;
    switch(type){
        case variabletypes::NUMBER:
            istringstream(s) >> number;
            break;
        case variabletypes::TEXT:
            text = s;
            break;
        case variabletypes::BOOLEAN:
            if(s=="true"){
                boolean=true;
            } else {
                boolean=false;
            }
            break;
    }
}

variabletypes variable::get_type(){
    return type;
}

float variable::get_number(){
    if(type==variabletypes::NUMBER){
        return number;
    } else {
        LOG_ERROR("variable not of type number");
        STOP();
    }
}

int variable::get_pointer(){
    if(type==variabletypes::POINTER){
        return pointer;
    } else {
        LOG_ERROR("variable not of type pointer");
        STOP();
    }

}

void variable::say(){
    switch(type){
        case variabletypes::NUMBER:
            LOG(number);
            break;
        case variabletypes::TEXT:
            LOG(text);
            break;
        case variabletypes::BOOLEAN:
            LOG("bool");
            break;
    }
}
