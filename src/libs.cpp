#include "libs.h"

libfunction::libfunction(){
    //empty constructor needed for map
}

libfunction::libfunction(string n, vector <int> b){
    bytecode = b;
    name = n;
}

void lib::add(libfunction f){
    elements[f.name] = f;
}

libs::libs(){
    lib std;

    //standard functions
    std.add(libfunction("+", {bytecodes::ADD}));
    std.add(libfunction("-", {bytecodes::SUB}));
    std.add(libfunction("*", {bytecodes::MULT}));
    std.add(libfunction("/", {bytecodes::DIV}));
}

map <string, vector <int> > libs::get(){
    map <string, vector <int> > total;
    for(int i=0; i<liblist.size(); i++){
        total.insert(liblist[i].elements.begin(), liblist[i].elements.end());
    }
    return total;
}
