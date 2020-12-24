#pragma once
#include <memory>
#include "IRule.h"

namespace Codevent19
{
	class Rule8 : public IRule
	{
	public:
		Rule8(std::shared_ptr<IRule> base) : IRule(0), base(base), ret(false) {}

		bool check(const std::string& expression);

		void reset();

		void shrink();

	private:
		std::shared_ptr<IRule> base;
		bool ret;
	};
}