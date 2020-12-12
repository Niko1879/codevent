#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <IO.h>
#include <acstring.h>

namespace Codevent2
{
	struct Policy
	{
		Policy(int min, int max, char c) : min(min), max(max), c(c)
		{

		}
		int min;
		int max;
		char c;
	};

	Policy parsePolicy(const std::string& policy)
	{
		std::vector<std::string> tokens = AcString::split(policy, "-");
		std::vector<std::string> tmp = AcString::split(tokens[1], " ");
		tokens[1] = tmp[0];
		tokens.push_back(tmp[1]);

		int min = stoi(tokens[0]);
		int max = stoi(tokens[1]);
		char c = tokens[2][0];
		return Policy(min, max, c);
	}

	bool isValidPassword(const std::string& pw, const std::string& policy)
	{
		Policy p = parsePolicy(policy);
		int count = std::count_if(pw.begin(), pw.end(), [p](char c) {return c == p.c; });
		return count >= p.min && count <= p.max;
	}

	bool isValidPassword2(const std::string& pw, const std::string& policy)
	{
		Policy p = parsePolicy(policy);
		p.max = p.max - 1;
		p.min = p.min - 1;
		return (pw[p.min] == p.c && pw[p.max] != p.c) || (pw[p.min] != p.c && pw[p.max] == p.c);
	}
}

int main()
{
	std::vector<std::string> lines = IO::readLines("input.txt");
	int numValidPasswords = 0;
	for (const std::string& l : lines)
	{
		std::vector<std::string> tokens = AcString::split(l, " ");
		if (Codevent2::isValidPassword2(tokens[2], tokens[0] + " " + tokens[1]))
		{
			numValidPasswords++;
		}
	}
	std::cout << "The number of valid passwords in the file is: " << numValidPasswords << std::endl;
}