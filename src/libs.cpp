#include "libs.h"

libs::libs(){
    LOG_DEBUG("Libs: Loading std lib");

    liblist["+"] = {bytecodes::ADD};
    liblist["-"] = {bytecodes::SUB};
    liblist["*"] = {bytecodes::MULT};
    liblist["/"] = {bytecodes::DIV};
    liblist["say"] = {bytecodes::V_CALL, 0};
    liblist["ask"] = {bytecodes::V_CALL, 1};
}

map <string, vector <int> > libs::get(){
    return liblist;
}
