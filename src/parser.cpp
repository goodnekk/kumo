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

//get the next token from the vector
token parser::getToken(int n){
    if (n<tokens.size())
        return tokens[n];
    else
        return token(tokentypes::NOTASGN,"");
}

//start by parsing statements
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
            LOG_DEBUG("Parser: found simple call");
            return new lexemes::call(NULL,"");
        }
        lexemes::node * d = statement(n+2);
        if(d){
            lexemes::node * e = c_operator(n+2+(d->length),")");
            if(e){
                LOG_DEBUG("Parser: found call");
                return new lexemes::call(d,a->value);
            }
        }
    }
    return NULL;
}

lexemes::node * parser::expression(int n){
    LOG_DEBUG("Parser: try expression "<<n);
    lexemes::node * a = addsub(n);
    if(a){
        return a;
    }

    lexemes::node * b = parenthesized(n);
    if(b){
        return b;
    }

    return NULL;
}

lexemes::node * parser::addsub(int n){
    LOG_DEBUG("Parser: try add/subtract "<<n);
    lexemes::node * a = multdiv(n);
    if(!a){
        a = parenthesized(n);
    }
    if(a){
        //check for plus or minus
        bool minus = false;
        lexemes::node * b = c_operator(n+(a->length),"+");
        if(!b){
            minus = true;
            b = c_operator(n+(a->length),"-");
        }

        if (b){
            lexemes::node * c = addsub(n+(a->length)+1);
            if (c) {
                if (minus){
                    return new lexemes::arithmetic(a,c,"-");
                } else{
                    return new lexemes::arithmetic(a,c,"+");
                }

            }
            return NULL;
        }
        return a;
    }
    return NULL;
}

lexemes::node * parser::multdiv(int n){
    LOG_DEBUG("Parser: try multiply/divide "<<n);
    lexemes::node * a = number(n);
    if(!a){
        a = parenthesized(n);
    }
    if (a){
        bool divide = false;
        lexemes::node * b = c_operator(n+(a->length),"*");
        if(!b){
            divide = true;
            b = c_operator(n+(a->length),"/");
        }
        if(b){
            lexemes::node * c = multdiv(n+(a->length)+1);
            if (c) {
                if(divide){
                    return new lexemes::arithmetic(a,c,"/");
                } else{
                    return new lexemes::arithmetic(a,c,"*");
                }

            }
            return NULL;
        }
        return a;
    }
    return NULL;
}

lexemes::node * parser::parenthesized(int n){
    LOG_DEBUG("Parser: try parenthesized "<<n);
    lexemes::node * a = c_operator(n,"(");
    if(a){
        lexemes::node * b = addsub(n+1);
        if(b){
            lexemes::node * c = c_operator(n+1+b->length,")");
            if(c){
                LOG_DEBUG("Parser: found parethesized");
                b->length+=2;
                return b;
            } else {
                LOG_COMPILE_ERROR("Unballanced parenthesis, expected ')'");
                return NULL;
            }
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
    LOG_DEBUG("Parser: try operator '"<<w<<"' "<<n);
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
