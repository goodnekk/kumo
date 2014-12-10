#pragma once

namespace tokentypes{
    const static int NOTASGN =  0;
    const static int EOL =      1;
    const static int NEWLINE = 	2;
    const static int NAME = 	3;
    const static int OPERATOR = 4;
    const static int STRING = 	5;
    const static int NUMBER = 	6;
    static string names[7] = {"n/a", "EOL", "NEWLINE" ,"NAME", "OPERATOR", "STRING", "NUMBER"};
}
