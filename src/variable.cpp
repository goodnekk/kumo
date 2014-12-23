#include "variable.h"

//NULL
variable::variable(){
    type = 0;
}

//Number
variable::variable(int n){
    type = 1;
    number = n;
}

//Boolean
variable::variable(bool n){
    type = 2;
    boolean = n;
}

//Text
variable::variable(string n){
    type = 3;
    text = n;
}

int variable::get(){
    return number;
}
