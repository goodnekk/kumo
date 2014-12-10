//author: Marcel Goethals
//code generator, parses an abstract syntax tree and generates
//a program in the form of a vector.

#include "generator.h"

vector<int> generator::generate(lexemes::node * a){
    a->eval(&program);
    return program;
}

void generator::push(int code){
    cout<<"code:"<<code<<endl;
    program.push_back(code);
}
