#include "AndRule.h"

namespace Codevent19
{
	bool AndRule::check(const std::string& expression)
	{
		return a->check(expression.substr(0, a->getSize())) &&
			b->check(expression.substr(a->getSize(), b->getSize()));
	}
}