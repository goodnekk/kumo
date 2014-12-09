#include "parser.h"

void parser::parse(vector<token> list){
    tokens = list;
    if(add(0) == true)
        cout<<"parsed"<<endl;
    else
        cout<<"parser failed"<<endl;
}

token parser::getToken(int n){
    if (n<tokens.size())
        return tokens[n];
    else
        return token(tokentypes::NOTASGN,"");
}

bool parser::add(int n){
    bool a = number(n);
    bool b = plus(n+1);
    if (a==true && b==true){
        bool c = add(n+2);
        if (c==true) {
            return true;
        }

        c = number(n+2);
        if (c==true){
            return true;
        }
    }
    return false;
}

bool parser::number(int n){
    if (getToken(n).type == tokentypes::NUMBER) {
        return true;
    }
    return false;
}

bool parser::plus(int n){
    if (getToken(n).type == tokentypes::OPERATOR) {
        if(getToken(n).tokenstring == "+"){
            return true;
        }
    }
    return false;
}
