#include "acmath.h"

namespace AcMath
{
	std::vector<long long> sumCombination(const std::vector<long long>& nums, size_t count, long long goal)
	{
		if (nums.size() < count)
			return std::vector<long long>();

		std::vector<size_t> indices;
		for (size_t i = 0; i < count; ++i)
			indices.push_back(0);

		size_t indicesInd = 0;
		size_t indicesIndMax = indices.size();
		size_t indexMax = nums.size();
		bool stop = false;

		while (!stop) //see exit cond below. Bad practice but oh well *shrug*
		{
			long long sum = 0;
			for (size_t i : indices)
				sum += nums[i];

			if (sum == goal)
			{
				std::vector<long long> goalVals;
				for (size_t i : indices)
					goalVals.push_back(nums[i]);
				return goalVals;
			}

			while (++indices[indicesInd] == indexMax)
			{
				indices[indicesInd++] = 0;
				if (indicesInd == indicesIndMax) //exit condition
				{
					stop = true;
					break;
				}
			}

			if (indicesInd > 0) indicesInd = 0;
		}

		return std::vector<long long>();
	}
}
