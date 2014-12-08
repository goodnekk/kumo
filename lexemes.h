#pragma once
#include <string>
#include <iostream>

using namespace std;

//terminals
class number {
        int value;
        number(string characters){
            //convert to int
            stringstream convert(characters);
            convert >> value;
        }
}

//nonterminals
class addition {
    number l;
    number r;

    addition(number left, number right){
        l = left;
        r = right;
    }
}
