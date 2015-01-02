#pragma once
#include "lexemetypes.h"
#include "parsenode.h"
#include "log.h"

class desugerer{
private:
    parsenode * analyse(parsenode * node);
public:
    parsenode * desuger(parsenode * root);
};
