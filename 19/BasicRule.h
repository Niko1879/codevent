#pragma once
#include "IRule.h"

namespace Codevent19
{
	class BasicRule : public IRule
	{
	public:
		BasicRule(size_t size, std::string expression) : IRule(size), expression(expression) {}

		bool check(const std::string& expression);

	private:
		const std::string expression;
	};

}