#pragma once
#include "IRule.h"
#include <memory>
#include <unordered_map>
#include "Rule11.h"
#include "Rule8.h"

namespace Codevent19
{
	typedef std::shared_ptr<IRule> RulePtr;

	class RuleManager
	{
	public:
		RuleManager() : rule8(nullptr), rule11(nullptr) {}

		void parseRules(const std::vector<std::string>& input);
		bool check(const std::string& expression, size_t which);
		bool checkRec(const std::string& expression);
		void reset();
		void activateRecursiveRules();

	private:
		void parseRule(const std::string& input);
		RulePtr _parseRule(const std::string& input);

		std::unordered_map<size_t, RulePtr> ruleBook;

		std::unique_ptr<Rule8> rule8;
		std::unique_ptr<Rule11> rule11;
	};

}

