#include "InfiniteGrid3D.h"

namespace Codevent17
{

	InfiniteGrid3D::InfiniteGrid3D()
	{
		resizeBack(1, 1, 1);
	}

	bool InfiniteGrid3D::at(int x, int y, int z)
	{
		resizeIfNeeded(x, y, z);
		return space[x + xOffset][y + yOffset][z + zOffset];
	}

	void InfiniteGrid3D::set(int x, int y, int z, bool b)
	{
		resizeIfNeeded(x, y, z);
		space[x + xOffset][y + yOffset][z + zOffset] = b;
	}

	void InfiniteGrid3D::cycle()
	{
		resizeBack(xSize() + 1, ySize() + 1, zSize() + 1);
		resizeFront(xSize() + 1, ySize() + 1, zSize() + 1);
		InfiniteGrid3D g = *this;
		for (int x = xMin(); x < xMax(); ++x)
		{
			for (int y = yMin(); y < yMax(); ++y)
			{
				for (int z = zMin(); z < zMax(); ++z)
				{
					applyActivationRules(x, y, z, g);
				}
			}
		}
	}

	size_t InfiniteGrid3D::countActive()
	{
		size_t count = 0;
		for (int x = xMin(); x < xMax(); ++x)
		{
			for (int y = yMin(); y < yMax(); ++y)
			{
				for (int z = zMin(); z < zMax(); ++z)
				{
					if (at(x, y, z))
					{
						++count;
					}
				}
			}
		}

		return count;
	}

	void InfiniteGrid3D::resizeBack(size_t x, size_t y, size_t z)
	{
		space.resize(x);
		for (Plane& p : space)
		{
			p.resize(y);
			for (Line& l : p)
			{
				l.resize(z);
			}
		}
	}

	void InfiniteGrid3D::resizeFront(size_t x, size_t y, size_t z)
	{
		int xSizeIncrease = x - xSize();
		int ySizeIncrease = y - ySize();
		int zSizeIncrease = z - zSize();
		xOffset += xSizeIncrease;
		yOffset += ySizeIncrease;
		zOffset += zSizeIncrease;

		space.insert(space.begin(), xSizeIncrease, Plane());

		for (Plane& p : space)
		{

			p.insert(p.begin(), y - p.size(), Line());
			for (Line& l : p)
			{
				l.insert(l.begin(), z - l.size(), false);
			}
		}
	}

	void InfiniteGrid3D::resizeIfNeeded(int x, int y, int z)
	{
		if (x < xMin())
		{
			resizeFront(xSize() + (xMin() - x), ySize(), zSize());
		}

		if (y < yMin())
		{
			resizeFront(xSize(), ySize() + (yMin() - y), zSize());
		}

		if (z < zMin())
		{
			resizeFront(xSize(), ySize(), zSize() + (zMin() - z));
		}

		if (x >= xMax())
		{
			resizeBack(xSize() + (x - xMax() + 1), ySize(), zSize());
		}

		if (y >= yMax())
		{
			resizeBack(xSize(), ySize() + (y - yMax() + 1), zSize());
		}

		if (z >= zMax())
		{
			resizeBack(xSize(), ySize(), zSize() + (z - zMax() + 1));
		}

	}

	bool InfiniteGrid3D::isWithinCurrentBounds(int x, int y, int z)
	{
		return x >= xMin() && y >= yMin() && z >= zMin() &&
			x < xMax() && y < yMax() && z < zMax();
	}

	std::vector<bool> InfiniteGrid3D::getNeighbourStates(int x, int y, int z)
	{
		std::vector<bool> neighbourStates;
		for (int i = -1; i < 2; ++i)
		{
			for (int j = -1; j < 2; ++j)
			{
				for (int k = -1; k < 2; ++k)
				{
					//dont check the actual coordinate; just surrounding ones
					if (i == 0 && j == 0 && k == 0)
					{
						continue;
					}

					if (isWithinCurrentBounds(x + i, y + j, z + k))
					{
						neighbourStates.push_back(at(x + i, y + j, z + k));
					}
				}
			}
		}

		return neighbourStates;
	}

	void InfiniteGrid3D::applyActivationRules(int x, int y, int z, InfiniteGrid3D& g)
	{
		std::vector<bool> neighbourStates = g.getNeighbourStates(x, y, z);
		size_t numActiveNeighbours = std::count(neighbourStates.begin(), neighbourStates.end(), true);

		if (g.at(x, y, z) && !(2 <= numActiveNeighbours && numActiveNeighbours <= 3))
		{
			set(x, y, z, false);
		}

		else if (numActiveNeighbours == 3)
		{
			set(x, y, z, true);
		}
	}

	Space space;
	int xOffset;
	int yOffset;
	int zOffset;
}