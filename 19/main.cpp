#include "IO.h"
#include <iostream>
#include "RuleManager.h"
#include "acstring.h"
#include <string>

int main()
{
	std::vector<std::string> input = IO::readLines("input.txt");
	std::vector<std::vector<std::string>> grps = AcString::group(input);
	Codevent19::RuleManager ruleManager;
	ruleManager.parseRules(grps[0]);
	size_t matched = 0;
	size_t ruleToCheck = 0;
	for (const std::string& line : grps[1])
	{
		if (ruleManager.check(line, ruleToCheck))
		{
			++matched;
		}
	}

	std::cout << "Number of matched rules: " << matched << std::endl;

	matched = 0;
	ruleManager.activateRecursiveRules();

	for (const std::string& line : grps[1])
	{
		if (ruleManager.checkRec(line))
		{
			++matched;
		}
	}

	std::cout << "Number of matched rules: " << matched << std::endl;
}