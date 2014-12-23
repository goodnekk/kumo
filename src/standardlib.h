#pragma once
#include <iostream>
#include <string>
#include "log.h"
#include "stack.h"
#include "variable.h"

using namespace std;

namespace standardlib{

    void say(stack * s){
        cout<<"> "<<s->pop().get()<<endl;
    };

    void ask(stack * s){
        cout<<"> ";
        int val;
        cin >> val;
        s->push(variable(val));
        cout<<endl;
    };

    void call(int n, stack * s){
        switch (n){
            case 0: say(s); break;
            case 1: ask(s); break;
            default: LOG_ERROR("VM: Unknown virtual function: "<< n);
        }
    };
};
