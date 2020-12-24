#pragma once
#include "IRule.h"
#include <iostream>

namespace Codevent19
{

	class AndRule : public IRule
	{
	public:
		AndRule(std::shared_ptr<IRule> a, std::shared_ptr<IRule> b)
			:IRule(a->getSize() + b->getSize()),
			a(a), b(b)
		{}

		bool check(const std::string& expression);

	private:
		std::shared_ptr<IRule> a;
		std::shared_ptr<IRule> b;
	};

}