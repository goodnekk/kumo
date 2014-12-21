#pragma once
#include <string>
#include "log.h"

using namespace std;

namespace standardlib{

    const string names[2]={"say","ask"};

    int check(string n){
        for(int i=0; i<(sizeof(names)/sizeof(names[0])); i++){
            if(n==names[i]){
                return i;
            }
        }
        return -1;
    };
};
