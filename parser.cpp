//author: Marcel Goethals
//Hand written parser, no lousy parser generators here.
//takes a vector of tokens and builds a parse tree.

#include "parser.h"

void parser::parse(vector<token> list){
    tokens = list;
    lexemes::node * a = add(0);
    if(a) {
        cout<<"parsed"<<endl;
        a->eval(2);
    }
    else {
        cout<<"parser failed"<<endl;
    }
}

lexemes::node * parser::test(){
    lexemes::node * a;
    a = new lexemes::node();
    return NULL;
}

token parser::getToken(int n){
    if (n<tokens.size())
        return tokens[n];
    else
        return token(tokentypes::NOTASGN,"");
}

lexemes::node * parser::add(int n){
    lexemes::node * a = number(n);
    bool b = plus(n+1);
    if (a && b){
        lexemes::node * c = add(n+2);
        if (c) {
            return new lexemes::addition(a,c);
        }

        lexemes::node * d = number(n+2);
        if (d){
            return new lexemes::addition(a,d);
        }
    }
    return NULL;
}

lexemes::node * parser::number(int n){
    if (getToken(n).type == tokentypes::NUMBER) {
        return new lexemes::number(getToken(n).tokenstring);
    }
    return NULL;
}

bool parser::plus(int n){
    if (getToken(n).type == tokentypes::OPERATOR) {
        if(getToken(n).tokenstring == "+"){
            return true;
        }
    }
    return false;
}
