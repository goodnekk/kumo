#include "token.h"
#include "tokentypes.h"

token::token(int ty, string tok){
    type = ty;
    tokenstring = tok;
}

void token::print(){
    LOG_DEBUG(tokentypes::names[type]<<"::"<<tokenstring);
}
