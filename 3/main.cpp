#include <vector>
#include <string>
#include "shared.h"
#include <iostream>

namespace Codevent3
{
	class Grid
	{
		std::vector<std::vector<bool>> grid;

		size_t getx(size_t x)
		{
			while (x >= grid.size()) x -= grid.size();
			return x;
		}

	public:
		Grid(size_t x, size_t y)
		{
			for (size_t i = 0; i < x; i++)
			{
				std::vector<bool> tmp;
				for (size_t j = 0; j < y; j++)
					tmp.push_back(false);
				grid.push_back(tmp);
			}
		}

		bool at(size_t x, size_t y) 
		{
			return grid[getx(x)][y]; 
		}

		void set(size_t x, size_t y, bool val)
		{
			grid[getx(x)][y] = val;
		}

		size_t ylength()
		{
			return grid[0].size();
		}

	};

	Grid parseGrid(const std::string& filepath, char treeInd)
	{
		std::vector<std::string> lines = Shared::readLines(filepath);
		size_t x = lines[0].length();
		size_t y = lines.size();
		Grid grid(x, y);
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
	Codevent3::Grid g = Codevent3::parseGrid("input.txt", '#');
	int treeCount = 0;
	for (size_t i = 1; i <= g.ylength()/2; i++)
	{
		if (g.at(i, 2*i)) treeCount++;
	}
	std::cout << "The number of trees encountered is: " << treeCount;
}