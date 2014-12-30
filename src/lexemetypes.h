#pragma once
#include <string>

enum class lexemetypes {
    //convenience(not used in tree)
    OPERATOR,

    //block of code
    BLOCK,
    ASSIGNMENT,
    DECLARATION,
    //constants
    NUMBER,
    TEXT,
    BOOLEAN,

    //names
    CALL,
    VARIABLE,

    //lists
    ARGUMENTLIST,

    //EXPRESSIONS
    ARITHMATIC,
};
