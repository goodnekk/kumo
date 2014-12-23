#pragma once
#include <iostream>
#include <string>
#include "log.h"
#include "stack.h"
#include "variable.h"

using namespace std;

namespace standardlib{

    void say(stack * s){
        variable v = s->pop();
        switch(v.get_type()){
            case 1:
                cout<<"> "<<v.get()<<endl;
                break;
            case 3:
                cout<<"> "<<v.get_text()<<endl;
                break;
        }
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
