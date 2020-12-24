#pragma once
#include <memory>
#include "IRule.h"

namespace Codevent19
{
	class Rule11 : public IRule
	{
	public:
		Rule11(std::shared_ptr<IRule> lBase, std::shared_ptr<IRule> rBase) : IRule(0), lBase(lBase), rBase(rBase) {}

		bool check(const std::string& expression);

		void reset();

	private:
		std::shared_ptr<IRule> lBase;
		std::shared_ptr<IRule> rBase;
	};
}