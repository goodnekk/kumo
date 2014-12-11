//author: Marcel Goethals
//Hand written parser, no lousy parser generators here.
//takes a vector of tokens and builds a parse tree.

#include "parser.h"

lexemes::node * parser::parse(vector<token> list){
    LOG_DEBUG("Parser: Started");
    tokens = list;
    lexemes::node * a = add(0);
    if(a) {
        LOG_DEBUG("Parser: Correctly parsed");
        return a;
    }
    else {
        LOG_ERROR("Parser: Parser failed, incomplete parse.");
    }
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
