#pragma once
#include "Typedefs.h"

namespace Codevent17
{

	class InfiniteGrid3D
	{
	public:
		InfiniteGrid3D();
		bool at(int x, int y, int z);
		void set(int x, int y, int z, bool b);
		void cycle();
		size_t countActive();

	private:
		inline int xMin() { return -xOffset; }
		inline int yMin() { return -yOffset; }
		inline int zMin() { return -zOffset; }
		inline int xMax() { return space.size() - xOffset; }
		inline int yMax() { return space[0].size() - yOffset; }
		inline int zMax() { return space[0][0].size() - zOffset; }
		inline size_t xSize() { return space.size(); }
		inline size_t ySize() { return space[0].size(); }
		inline size_t zSize() { return space[0][0].size(); }
		void resizeBack(size_t x, size_t y, size_t z);
		void resizeFront(size_t x, size_t y, size_t z);
		void resizeIfNeeded(int x, int y, int z);
		bool isWithinCurrentBounds(int x, int y, int z);
		std::vector<bool> getNeighbourStates(int x, int y, int z);
		void applyActivationRules(int x, int y, int z, InfiniteGrid3D& g);
		Space space;
		int xOffset;
		int yOffset;
		int zOffset;
	};
}
