#pragma once
#include <string>

namespace bytecodes {

    //stack
    const static int END     =  0;
    const static int PUSH_C  =  1;
    const static int POP     =  2;

    //push from and pop to ram
    const static int PUSH_R  =  3;
    const static int POP_R   =  4;

    //arithmatic
    const static int ADD     =  5;
    const static int SUB     =  6;
    const static int MULT    =  7;
    const static int DIV     =  8;

    //boolean
    const static int ISEQ    =  9;
    const static int ISHI    =  10;
    const static int ISLO    =  11;

    //functions
    const static int CALL    = 12;
    const static int RETURN  = 13;
    const static int V_CALL  = 14;

    //flow control
    const static int ISTRUE  = 15;
    const static int GOTO    = 16;

    const static std::string names[17] = {
        "END",
        "PUSH_C",
        "POP",
        "PUSH_R",
        "POP_R",
        "ADD",
        "SUB",
        "MULT",
        "DIV",
        "ISEQ",
        "ISHI",
        "ISLO",
        "CALL",
        "RETURN",
        "V_CALL",
        "ISTRUE",
        "GOTO"
        };
}
