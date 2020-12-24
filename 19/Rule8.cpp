#include "Rule8.h"
#include <iostream>

namespace Codevent19
{ 
    bool Rule8::check(const std::string& expression)
    {  
        std::string expr(expression.begin(), expression.end());
        while (expr.size() >= base->getSize() && base->check(expr.substr(0, base->getSize())))
        {
            size += base->getSize();
            ret = true;
            expr = expr.substr(base->getSize());      
        }
        return ret;
    }

    void Rule8::reset()
    {
        ret = false;
        size = 0;
    }

    void Rule8::shrink()
    {
        size -= base->getSize();
    }
}