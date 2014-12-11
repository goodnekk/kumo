//author: Marcel Goethals
//Hand written parser, no lousy parser generators here.
//takes a vector of tokens and builds a parse tree.

#include "parser.h"

lexemes::node * parser::parse(vector<token> list){
    LOG_DEBUG("Parser: Started");
    tokens = list;
    lexemes::node * a = statement(0);
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

lexemes::node * parser::statement(int n){
    //simple statements
    lexemes::node * a = call(n);
    if(a){
        return a;
    }
    lexemes::node * b = expression(n);
    if(b){
        return b;
    }
    return NULL;
    //control structures
}

lexemes::node * parser::call(int n){
    LOG_DEBUG("Parser: try call "<<n);
    //word(statement)
    lexemes::name * a = name(n);
    lexemes::node * b = c_operator(n+1,"(");
    if(a && b){
        lexemes::node * c = c_operator(n+2,")");
        if(c){
            LOG_DEBUG("Parser: simple call ");
            return new lexemes::call(NULL,"");
        }
        lexemes::node * d = statement(n+2);
        if(d){
            lexemes::node * e = c_operator(n+2+(d->length),")");
            if(e){
                return new lexemes::call(d,a->value);
            }
        }
    }
    return NULL;
}

lexemes::node * parser::expression(int n){
    lexemes::node * a = add(n);
    if(a){
        return a;
    }
    return NULL;
}

lexemes::node * parser::add(int n){
    LOG_DEBUG("Parser: try add "<<n);
    lexemes::node * a = number(n);
    lexemes::node * b = c_operator(n+1,"+");
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
    LOG_DEBUG("Parser: try number "<<n);
    if (c_type(n,tokentypes::NUMBER)) {
        return new lexemes::number(getToken(n).tokenstring);
    }
    return NULL;
}

lexemes::name * parser::name(int n){
    LOG_DEBUG("Parser: try name "<<n);
    if(c_type(n,tokentypes::NAME)){
        return new lexemes::name(getToken(n).tokenstring);
    }
    return NULL;
}

lexemes::node * parser::c_operator(int n, string w){
    LOG_DEBUG("Parser: try operator "<<n);
    if (c_type(n,tokentypes::OPERATOR) && c_string(n,w)) {
        return new lexemes::node();
    }
    return NULL;
}

bool parser::c_type(int n, int t){
    if (getToken(n).type == t) {
        return true;
    }
    return false;
}

bool parser::c_string(int n, string w){
    if(getToken(n).tokenstring == w){
        return true;
    }
    return false;
}
