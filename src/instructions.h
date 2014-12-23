#pragma once

namespace instructions {

    //stack
    const static int PUSH_C  =  0;
    const static int POP     =  1;

    //push from and pop to ram
    const static int PUSH_R  =  2;
    const static int POP_R   =  3;

    //arithmatic
    const static int ADD     =  4;
    const static int SUB     =  5;
    const static int MULT    =  6;
    const static int DIV     =  7;

    //functions
    const static int CALL    =  8;
    const static int RETURN  =  9;
    const static int V_CALL  =  10;

    //logic
    const static int ISTRUE  =  11;
    const static int GOTO    =  12;
}
