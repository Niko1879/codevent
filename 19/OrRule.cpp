#include "OrRule.h"
#include <iostream>

namespace Codevent19
{
	bool OrRule::check(const std::string& expression)
	{
		return a->check(expression) || b->check(expression);
	}
}