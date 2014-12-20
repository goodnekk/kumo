#include "token.h"
#include "tokentypes.h"

token::token(int ty, string tok){
    type = ty;
    tokenstring = tok;
}

void token::print(int i){
    LOG_DEBUG(i<<"  "<<tokentypes::names[type]<<"::"<<tokenstring);
}
