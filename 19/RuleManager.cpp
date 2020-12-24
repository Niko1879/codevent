#include "RuleManager.h"
#include "acstring.h"
#include "OrRule.h"
#include "AndRule.h"
#include "BasicRule.h"
#include "Rule11.h"
#include "Rule8.h"
#include <iostream>

namespace Codevent19
{
	void RuleManager::activateRecursiveRules()
	{
		rule8.reset(new Rule8(ruleBook.at(42)));
		rule11.reset(new Rule11(ruleBook.at(42), ruleBook.at(31)));
	}

	bool RuleManager::checkRec(const std::string& expression)
	{
		bool l = rule8->check(expression);
		while (rule8->getSize() >= expression.size())
		{
			rule8->shrink();
		}
		
		bool r = false;
		while (rule8->getSize() > 0)
		{
			if (rule11->check(expression.substr(rule8->getSize())))
			{
				r = true;
				break;
			}

			else
			{
				rule8->shrink();
				rule11->reset();
			}
		}

		size_t s1 = rule8->getSize();
		size_t s2 = rule11->getSize();
		rule8->reset();
		rule11->reset();
		return s1 + s2 == expression.size() && l && r;
	}

	bool RuleManager::check(const std::string& expression, size_t which)
	{
		RulePtr rule = ruleBook.at(which);
		return expression.size() == rule->getSize() && rule->check(expression);

	}

	void RuleManager::reset()
	{
		ruleBook.clear();
	}

	void RuleManager::parseRules(const std::vector<std::string>& input)
	{
		//parse the first 2 basic rules
		for (const std::string& line : input)
		{
			std::vector<std::string> tokens = AcString::split(line, ": ");
			if (tokens[1] == "\"a\"" || tokens[1] == "\"b\"")
			{
				parseRule(line);
			}
		}

		//map each line to it's corresponding array of numbers (rules).
		//this is so that we can only push rules which depend on rules which
		//already exist in ruleBook
		std::unordered_map<std::string, std::vector<size_t>> lookup;
		for (const std::string& line : input)
		{
			std::vector<size_t> nums;
			std::vector<std::string> tokens = AcString::split(line, ": ");
			if (tokens[1] == "\"a\"" || tokens[1] == "\"b\"")
			{
				continue;
			}

			tokens = AcString::split(tokens[1], " | ");
			for (const std::string& t : tokens)
			{
				std::vector<std::string> subtoks = AcString::split(t, " ");
				for (const std::string& s : subtoks)
				{
					nums.push_back(stoi(s));
				}
			}

			lookup[line] = nums;
		}

		while (lookup.size() > 0)
		{
			for (const std::pair<std::string, std::vector<size_t>> p : lookup)
			{
				bool canPush = true;
				for (size_t i : p.second)
				{
					if (ruleBook.count(i) == 0)
					{
						canPush = false;
						break;
					}
				}

				if (canPush)
				{
					parseRule(p.first);
					lookup.erase(p.first);
					break;
				}
			}
		}
	}

	void RuleManager::parseRule(const std::string& input)
	{
		std::vector<std::string> tokens = AcString::split(input, ": ");
		size_t key = stoi(tokens[0]);
		std::string ruleParams = tokens[1];
		ruleBook[key] = _parseRule(ruleParams);
	}

	RulePtr RuleManager::_parseRule(const std::string& input)
	{
		RulePtr rule(nullptr);
		if (std::find(input.begin(), input.end(), '|') != input.end())
		{
			std::vector<std::string> tokens = AcString::split(input, " | ");
			rule.reset(new OrRule(_parseRule(tokens[0]), _parseRule(tokens[1])));
		}

		else
		{
			std::vector<std::string> tokens = AcString::split(input, " ");
			if (tokens.size() > 1)
			{
				rule.reset(new AndRule(_parseRule(tokens[0]), _parseRule(tokens[1])));
			}

			else
			{
				if (AcString::isInteger(tokens[0]))
				{
					size_t k = stoi(tokens[0]);
					rule = ruleBook.at(k);
				}

				else
				{
					rule.reset(new BasicRule(1, std::string(1, tokens[0][1])));
				}
			}
		}

		return rule;
	}
}