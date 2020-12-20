#include <vector>
#include <algorithm>
#include <string>
#include <IO.h>
#include <iostream>
#include "InfiniteGrid3D.h"
#include "InfiniteGrid4D.h"

namespace Codevent17
{

	InfiniteGrid3D parse(const std::vector<std::string>& input)
	{
		InfiniteGrid3D g;
		for (int i = 0; i < input[0].size(); ++i)
		{
			for (int j = 0; j < input.size(); ++j)
			{
				input[j][i] == '#' ? g.set(i, j, 0, true) : g.set(i, j, 0, false);
			}
		}

		return g;
	}

	InfiniteGrid4D parse4D(const std::vector<std::string>& input)
	{
		InfiniteGrid4D g;
		for (int i = 0; i < input[0].size(); ++i)
		{
			for (int j = 0; j < input.size(); ++j)
			{
				input[j][i] == '#' ? g.set(i, j, 0, 0, true) : g.set(i, j, 0, 0, false);
			}
		}

		return g;
	}
}

int main()
{
	std::vector<std::string> input = IO::readLines("input.txt");
	Codevent17::InfiniteGrid3D g = Codevent17::parse(input);
	for (int i = 0; i < 6; ++i)
	{
		g.cycle();
	}

	std::cout << g.countActive() << std::endl;

	Codevent17::InfiniteGrid4D g2 = Codevent17::parse4D(input);
	for (int i = 0; i < 6; ++i)
	{
		g2.cycle();
	}

	std::cout << g2.countActive() << std::endl;

	return 0;
}