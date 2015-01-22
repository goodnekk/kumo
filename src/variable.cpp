#include "variable.h"
variable::variable(){

}

variable::variable(float n){
    number = n;
    type = variabletypes::NUMBER;
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
    return number;
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
