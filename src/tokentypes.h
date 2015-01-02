#pragma once
#include <string>

namespace tokentypes{
    const static int NOTASGN =  0;
    const static int NEWLINE = 	1;
    const static int NAME = 	2;
    const static int OPERATOR = 3;
    const static int SEPARATOR= 4;
    const static int STRING = 	5;
    const static int NUMBER = 	6;
    static std::string names[7] = {"n/a", "NEWLINE" ,"NAME", "OPERATOR", "SEPARATOR", "STRING", "NUMBER"};
}
