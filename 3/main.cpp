#include <vector>
#include <string>
#include <iostream>
#include <IO.h>
#include <Grid.h>

namespace Codevent3
{
	Dstruct::Grid<bool> parseGrid(const std::string& filepath, char treeInd)
	{
		std::vector<std::string> lines = IO::readLines(filepath);
		size_t x = lines[0].length();
		size_t y = lines.size();
		Dstruct::Grid<bool> grid(x, y);
		for (size_t i = 0; i < lines.size(); i++)
		{
			for (size_t j = 0; j < lines[0].size(); j++)
			{
				grid.set(j, i, lines[i][j] == treeInd);
			}
		}
		return grid;
	}
}

int main()
{
	Dstruct::Grid<bool> g = Codevent3::parseGrid("input.txt", '#');
	int treeCount = 0;
	for (size_t i = 1; i <= g.ylength()/2; i++)
	{
		if (g.at(i, 2*i)) treeCount++;
	}
	std::cout << "The number of trees encountered is: " << treeCount;
}