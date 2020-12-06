#include "shared.h"
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

namespace Codevent6
{
	size_t countAny(const std::vector<std::string>& lines)
	{
		std::vector<char> seen;
		for (const std::string& line : lines)
			for (char c : line)
				if (seen.empty() || std::find(seen.begin(), seen.end(), c) == seen.end())
					seen.push_back(c);
		return seen.size();
	}

	size_t countAll(const std::vector<std::string>& lines)
	{
		std::vector<char> seen;
		size_t count = 0;
		std::string fullstr;
		for (const std::string& line : lines)
			fullstr += line;
		for (char c : fullstr)
			if (std::find(seen.begin(), seen.end(), c) == seen.end() &&
				std::count(fullstr.begin(), fullstr.end(), c) == lines.size())
			{
				count++;
				seen.push_back(c);
			}
		return count;
	}

	void question(const std::vector<std::string>& input, size_t (*count)(const std::vector<std::string>&))
	{
		auto grps = Shared::group(input);
		std::vector<size_t> counts;
		for (const auto& g : grps)
			counts.push_back(count(g));
		size_t sumOfCounts = std::accumulate(counts.begin(), counts.end(), 0);
		std::cout << "The sum of counts is: " << sumOfCounts << std::endl;
	}

}

int main()
{
	std::vector<std::string> input = Shared::readLines("input.txt");
	Codevent6::question(input, Codevent6::countAny);
	Codevent6::question(input, Codevent6::countAll);

	return 0;
}