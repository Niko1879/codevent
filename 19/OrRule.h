#pragma once
#include "IRule.h"
#include <memory>

namespace Codevent19
{
	class OrRule : public IRule
	{
	public:
		OrRule(std::shared_ptr<IRule> a, std::shared_ptr<IRule> b)
			:IRule(a->getSize()),
			a(a), b(b)
		{}

		bool check(const std::string& expression);

	private:
		std::shared_ptr<IRule> a;
		std::shared_ptr<IRule> b;
	};
}