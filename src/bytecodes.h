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

    //push from and pop to local
    const static int PUSH_L  =  5;
    const static int POP_L   =  6;

    //arithmatic
    const static int ADD     =  7;
    const static int SUB     =  8;
    const static int MULT    =  9;
    const static int DIV     =  10;

    //boolean
    const static int ISEQ    =  11;
    const static int ISHI    =  12;
    const static int ISLO    =  13;

    //functions
    const static int CALL    = 14;
    const static int RETURN  = 15;
    const static int V_CALL  = 16;

    //flow control
    const static int ISTRUE  = 17;
    const static int GOTO    = 18;

    const static std::string names[19] = {
        "END",
        "PUSH_C",
        "POP",
        "PUSH_R",
        "POP_R",
        "PUSH_L",
        "POP_L",
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
