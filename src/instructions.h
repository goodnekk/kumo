#pragma once

namespace instructions{
    //stack
    const static int PUSH_C =  0;

    //push from and pop to ram
    const static int PUSH_R =  1;
    const static int POP_R  =  2;
    //arithmatic
    const static int ADD    =  3;
    const static int SUB    =  4;
    const static int MULT   =  5;
    const static int DIV    =  6;

    //std lib
    const static int PRINT  =  7;
}
