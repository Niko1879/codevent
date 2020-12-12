#pragma once
#include <vector>

namespace Dstruct

{

	template<class T>
	class Grid
	{
		std::vector<std::vector<T>> grid;

		size_t getx(size_t x) const
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

		T at(size_t x, size_t y) const
		{
			return grid[getx(x)][y];
		}

		void set(size_t x, size_t y, T val)
		{
			grid[getx(x)][y] = val;
		}

		size_t ylength() const
		{
			return grid[0].size();
		}

	};

}