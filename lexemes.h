#pragma once
#include <string>
#include <iostream>

using namespace std;
namespace lexemes{

    class node {
        virtual void eval();
    };

    //terminals
    class number: public node {
            int value;
            number(string characters){
                //convert to int
                //stringstream convert(characters);
                //convert >> value;
            }
    };

    //nonterminals
    class addition: public node {
        node l;
        node r;

        addition(node left, node right){
            l = left;
            r = right;
        }
    };
}
