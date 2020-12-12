#include <IO.h>
#include <Grid.h>
#include <iostream>

namespace Codevent11
{
	typedef Dstruct::Grid<char> Seats;

	Seats parseGrid(const std::vector<std::string>& input)
	{
		size_t lineLength = input[0].size();
		Seats g(lineLength, input.size());
		for (size_t i = 0; i < input.size(); ++i)
			for (size_t j = 0; j < lineLength; ++j)
				g.set(j, i, input[i][j]);

		return g;
	}


	size_t countAdjacent(int x, int y, char c, const Seats& grid)
	{
		size_t count = 0;
		
		for (int i = -1; i < 2; ++i)
		{
			for (int j = -1; j < 2; ++j)
			{
				size_t x_adj = x + i;
				size_t y_adj = y + j;
				if (0 <= x_adj && x_adj < grid.xlength() && 
					0 <= y_adj && y_adj < grid.ylength() && 
					!(i == 0 && j == 0) &&
					grid.at(x_adj, y_adj) == c)
					++count;
			}
		}

		return count;
	}

	size_t countAnyAdjacent(int x, int y, char c, const Seats& grid)
	{
		size_t count = 0;
		for (int i = x - 1; i >= 0; --i)
		{
			if (grid.at(i, y) == c)
			{
				++count;
				break;
			}

			if (grid.at(i, y) == 'L')
				break;
		}

		for (int i = x + 1; i < grid.xlength(); ++i)
		{
			if (grid.at(i, y) == c)
			{
				++count;
				break;
			}

			if (grid.at(i, y) == 'L')
				break;
		}

		for (int i = y - 1; i >= 0; --i)
		{
			if (grid.at(x, i) == c)
			{
				++count;
				break;
			}

			if (grid.at(x, i) == 'L')
				break;
		}

		for (int i = y + 1; i < grid.ylength(); ++i)
		{
			if (grid.at(x, i) == c)
			{
				++count;
				break;
			}

			if (grid.at(x, i) == 'L')
				break;
		}

		for (int i = 1; x + i < grid.xlength() && y + i < grid.ylength(); ++i)
		{
			if (grid.at(x + i, y + i) == c)
			{
				++count;
				break;
			}

			if (grid.at(x + i, y + i) == 'L')
				break;
		}

		for (int i = 1; x + i < grid.xlength() && y - i >= 0; ++i)
		{
			if (grid.at(x + i, y - i) == c)
			{
				++count;
				break;
			}

			if (grid.at(x + i, y - i) == 'L')
				break;
		}

		for (int i = 1; x - i >= 0 && y + i < grid.ylength(); ++i)
		{
			if (grid.at(x - i, y + i) == c)
			{
				++count;
				break;
			}

			if (grid.at(x - i, y + i) == 'L')
				break;
		}

		for (int i = 1; x - i >= 0 && y - i >= 0; ++i)
		{
			if (grid.at(x - i, y - i) == c)
			{
				++count;
				break;
			}

			if (grid.at(x - i, y - i) == 'L')
				break;
		}

		return count;
	}

	Seats applyRules(const Seats& grid, size_t (*fn)(int x, int y, char c, const Seats& grid), int maxAdjAllowed)
	{
		Seats applied = grid;
		for (int i = 0; i < grid.xlength(); ++i)
		{
			for (int j = 0; j < grid.ylength(); ++j)
			{
				switch (grid.at(i, j))
				{
				case 'L':
					if (fn(i, j, '#', grid) == 0)
						applied.set(i, j, '#');
					break;

				case '#':
					if (fn(i, j, '#', grid) >= maxAdjAllowed)
						applied.set(i, j, 'L');
					break;

				default:
					break;
				}
			}
		}
		return applied;
	}

	Seats converge(const Seats& grid, size_t(*fn)(int x, int y, char c, const Seats& grid), int maxAdjAllowed)
	{
		Seats grid_ = grid;
		while (grid_ != applyRules(grid_, fn, maxAdjAllowed))
			grid_ = applyRules(grid_, fn, maxAdjAllowed);
		return grid_;
	}

	size_t count(const Seats& grid, char c)
	{
		size_t count = 0;
		for (size_t i = 0; i < grid.xlength(); ++i)
		{
			for (size_t j = 0; j < grid.ylength(); ++j)
			{
				if (grid.at(i, j) == c)
					++count;
			}
		}
		return count;
	}

}

int main()
{
	std::vector<std::string> input = IO::readLines("input.txt");
	Codevent11::Seats g = Codevent11::parseGrid(input);
	
	std::cout << "Using the first set of rules, the number of occupied seats is: "
		<< Codevent11::count(Codevent11::converge(g, Codevent11::countAdjacent, 4), '#')
		<< std::endl;

	std::cout << "Using the second set of rules, the number of occupied seats is: "
		<< Codevent11::count(Codevent11::converge(g, Codevent11::countAnyAdjacent, 5), '#')
		<<std::endl;

	return 0;
}