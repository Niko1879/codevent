#pragma once
#include "Typedefs.h"

namespace Codevent17
{
	class InfiniteGrid4D
	{
	public:
		InfiniteGrid4D();
		bool at(int x, int y, int z, int w);
		void set(int x, int y, int z, int w, bool b);
		void cycle();
		size_t countActive();

	private:
		inline int xMin() { return -xOffset; }
		inline int yMin() { return -yOffset; }
		inline int zMin() { return -zOffset; }
		inline int wMin() { return -wOffset; }
		inline int xMax() { return space.size() - xOffset; }
		inline int yMax() { return space[0].size() - yOffset; }
		inline int zMax() { return space[0][0].size() - zOffset; }
		inline int wMax() { return space[0][0][0].size() - wOffset; }
		inline size_t xSize() { return space.size(); }
		inline size_t ySize() { return space[0].size(); }
		inline size_t zSize() { return space[0][0].size(); }
		inline size_t wSize() { return space[0][0][0].size(); }
		void resizeBack(size_t x, size_t y, size_t z, size_t w);
		void resizeFront(size_t x, size_t y, size_t z, size_t w);
		void resizeIfNeeded(int x, int y, int z, int w);
		bool isWithinCurrentBounds(int x, int y, int z, int w);
		std::vector<bool> getNeighbourStates(int x, int y, int z, int w);
		void applyActivationRules(int x, int y, int z, int w, InfiniteGrid4D& g);

		HyperSpace space;
		int xOffset;
		int yOffset;
		int zOffset;
		int wOffset;
	};

}