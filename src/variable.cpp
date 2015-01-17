#include "variable.h"
variable::variable(){

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
