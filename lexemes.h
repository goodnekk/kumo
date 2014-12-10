#pragma once
#include <string>
#include <iostream>

using namespace std;
namespace lexemes{

    class node {
    public:
        node(){};
        virtual void eval(int reg){};
    };

    //terminals
    class number: public node {
    public:
        string value;
        number(string characters){
            value = characters;
            //convert to int
            //stringstream convert(characters);
            //convert >> value;
        };
        void eval(int reg){cout<<"LD "<<reg<<" "<<value<<endl;};
    };

    //nonterminals
    class addition: public node {
    public:
        node * r;
        node * l;
        addition(node * left, node * right){
            l = left;
            r = right;
        };
        void eval(int reg){
            r->eval(0);
            l->eval(1);
            cout<<"ADD 0 1 "<<reg<<endl;
        };
    };
}
