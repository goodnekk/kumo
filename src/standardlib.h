#pragma once
#include <iostream>
#include <string>
#include "log.h"
#include "stack.h"

using namespace std;

namespace standardlib{

    //string names[1]={"say"};

    int check(string n){
        if(n=="say"){
            return 0;
        }
        return -1;
    };

    void say(stack * s){
        cout<<"> "<<s->pop()<<endl;
    };

    void call(int n, stack * s){
        switch (n){
            case 0: say(s); break;
            default: LOG_ERROR("VM: Unknown virtual function: "<< n);
        }
    };
};
