#pragma once

namespace bytecodes {

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

    //boolean
    const static int ISEQ    =  8;
    const static int ISHI    =  9;
    const static int ISLO    = 10;

    //functions
    const static int CALL    = 11;
    const static int RETURN  = 12;
    const static int V_CALL  = 13;

    //flow control
    const static int ISTRUE  = 14;
    const static int GOTO    = 15;
}
