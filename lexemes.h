#pragma once
#include <string>
#include <iostream>

using namespace std;
namespace lexemes{

    class node {
    public:
        node(){};
        virtual void eval(){};
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
        void eval(){cout<<"LD 2 "<<value<<endl;};
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
        void eval(){
            r->eval();
            cout<<"MOV 2 0"<<endl;
            l->eval();
            cout<<"MOV 2 1"<<endl;
            cout<<"ADD 0 1 2"<<endl;
        };
    };
}
