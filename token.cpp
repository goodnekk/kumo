#include "token.h"
#include "tokentypes.h"

token::token(int ty, string tok){
    type = ty;
    tokenstring = tok;
}

void token::print(){
    cout<<tokentypes::names[type]<<"::"<<tokenstring<<endl;
}
