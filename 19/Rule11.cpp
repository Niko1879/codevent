#include "Rule11.h"
#include <iostream>

namespace Codevent19
{
    bool Rule11::check(const std::string& expression)
    {
        std::string expr(expression.begin(), expression.end());
        bool matchedFirst = false;
        bool matchedSecond = false;
        size_t numLeft = 0;
        size_t numRight = 0;

        while (expr.size() >= lBase->getSize() && 
            lBase->check(expr.substr(0, lBase->getSize())))
        {
            matchedFirst = true;
            size += lBase->getSize();
            expr = expr.substr(lBase->getSize());
            ++numLeft;
        }

        if (size >= expression.size())
        {
            return false;
        }

        std::string expr2(expression.begin() + size , expression.end());
        while (matchedFirst && expr2.size() >= rBase->getSize() &&
            rBase->check(expr2.substr(0, rBase->getSize())))
        {
            matchedSecond = true;
            size += rBase->getSize();
            expr2 = expr2.substr(rBase->getSize());
            ++numRight;
        }
        return matchedFirst && matchedSecond && (numLeft == numRight);
    }

    void Rule11::reset()
    {
        size = 0;
    }
}