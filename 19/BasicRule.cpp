#include "BasicRule.h"
#include <iostream>

namespace Codevent19
{
	bool BasicRule::check(const std::string& expression)
	{
		return expression.substr(0, size) == this->expression;
	}
}