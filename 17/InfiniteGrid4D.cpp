#include "InfiniteGrid4D.h"

namespace Codevent17
{
	InfiniteGrid4D::InfiniteGrid4D()
	{
		resizeBack(1, 1, 1, 1);
	}

	bool InfiniteGrid4D::at(int x, int y, int z, int w)
	{
		resizeIfNeeded(x, y, z, w);
		return space[x + xOffset][y + yOffset][z + zOffset][w + wOffset];
	}

	void InfiniteGrid4D::set(int x, int y, int z, int w, bool b)
	{
		resizeIfNeeded(x, y, z, w);
		space[x + xOffset][y + yOffset][z + zOffset][w + wOffset] = b;
	}

	void InfiniteGrid4D::cycle()
	{
		resizeBack(xSize() + 1, ySize() + 1, zSize() + 1, wSize() + 1);
		resizeFront(xSize() + 1, ySize() + 1, zSize() + 1, wSize() + 1);
		InfiniteGrid4D g = *this;
		for (int x = xMin(); x < xMax(); ++x)
		{
			for (int y = yMin(); y < yMax(); ++y)
			{
				for (int z = zMin(); z < zMax(); ++z)
				{
					for (int w = wMin(); w < wMax(); ++w)
					{
						applyActivationRules(x, y, z, w, g);
					}
				}
			}
		}
	}

	size_t InfiniteGrid4D::countActive()
	{
		size_t count = 0;
		for (int x = xMin(); x < xMax(); ++x)
		{
			for (int y = yMin(); y < yMax(); ++y)
			{
				for (int z = zMin(); z < zMax(); ++z)
				{
					for (int w = wMin(); w < wMax(); ++w)
					{
						if (at(x, y, z, w))
						{
							++count;
						}
					}
				}
			}
		}

		return count;
	}

	void InfiniteGrid4D::resizeBack(size_t x, size_t y, size_t z, size_t w)
	{
		space.resize(x);
		for (Space& s : space)
		{
			s.resize(y);
			for (Plane& p : s)
			{
				p.resize(z);

				for (Line& l : p)
				{
					l.resize(w);
				}
			}
		}
	}

	void InfiniteGrid4D::resizeFront(size_t x, size_t y, size_t z, size_t w)
	{
		int xSizeIncrease = x - xSize();
		int ySizeIncrease = y - ySize();
		int zSizeIncrease = z - zSize();
		int wSizeIncrease = w - wSize();
		xOffset += xSizeIncrease;
		yOffset += ySizeIncrease;
		zOffset += zSizeIncrease;
		wOffset += wSizeIncrease;

		space.insert(space.begin(), xSizeIncrease, Space());

		for (Space& s : space)
		{
			s.insert(s.begin(), y - s.size(), Plane());
			for (Plane& p : s)
			{
				p.insert(p.begin(), z - p.size(), Line());
				for (Line& l : p)
				{
					l.insert(l.begin(), w - l.size(), false);
				}
			}
		}

	}

	void InfiniteGrid4D::resizeIfNeeded(int x, int y, int z, int w)
	{
		if (x < xMin())
		{
			resizeFront(xSize() + (xMin() - x), ySize(), zSize(), wSize());
		}

		if (y < yMin())
		{
			resizeFront(xSize(), ySize() + (yMin() - y), zSize(), wSize());
		}

		if (z < zMin())
		{
			resizeFront(xSize(), ySize(), zSize() + (zMin() - z), wSize());
		}

		if (w < wMin())
		{
			resizeFront(xSize(), ySize(), zSize(), wSize() + (wMin() - w));
		}

		if (x >= xMax())
		{
			resizeBack(xSize() + (x - xMax() + 1), ySize(), zSize(), wSize());
		}

		if (y >= yMax())
		{
			resizeBack(xSize(), ySize() + (y - yMax() + 1), zSize(), wSize());
		}

		if (z >= zMax())
		{
			resizeBack(xSize(), ySize(), zSize() + (z - zMax() + 1), wSize());
		}

		if (w >= wMax())
		{
			resizeBack(xSize(), ySize(), zSize(), wSize() + (w - wMax() + 1));
		}
	}

	bool InfiniteGrid4D::isWithinCurrentBounds(int x, int y, int z, int w)
	{
		return x >= xMin() && y >= yMin() && z >= zMin() && w >= wMin() &&
			x < xMax() && y < yMax() && z < zMax() && w < wMax();
	}

	std::vector<bool> InfiniteGrid4D::getNeighbourStates(int x, int y, int z, int w)
	{
		std::vector<bool> neighbourStates;
		for (int i = -1; i < 2; ++i)
		{
			for (int j = -1; j < 2; ++j)
			{
				for (int k = -1; k < 2; ++k)
				{
					for (int l = -1; l < 2; ++l)
					{
						if (i == 0 && j == 0 && k == 0 && l == 0)
						{
							continue;
						}

						if (isWithinCurrentBounds(x + i, y + j, z + k, w + l))
						{
							neighbourStates.push_back(at(x + i, y + j, z + k, w + l));
						}
					}
				}
			}
		}

		return neighbourStates;
	}

	void InfiniteGrid4D::applyActivationRules(int x, int y, int z, int w, InfiniteGrid4D& g)
	{
		std::vector<bool> neighbourStates = g.getNeighbourStates(x, y, z, w);
		size_t numActiveNeighbours = std::count(neighbourStates.begin(), neighbourStates.end(), true);

		if (g.at(x, y, z, w) && !(2 <= numActiveNeighbours && numActiveNeighbours <= 3))
		{
			set(x, y, z, w, false);
		}

		else if (numActiveNeighbours == 3)
		{
			set(x, y, z, w, true);
		}
	}
}