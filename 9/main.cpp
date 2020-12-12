#include <algorithm>
#include <iostream>
#include <numeric>
#include <deque>
#include <IO.h>
#include <acmath.h>

namespace Codevent9
{
	long long findOutlier(const std::vector<long long>& nums, size_t preambleLength)
	{
		for (size_t i = 0; i < nums.size() - preambleLength; ++i)
		{
			std::vector<long long> sub(nums.begin() + i, nums.begin() + i + preambleLength);
			std::vector<long long> sumComb = AcMath::sumCombination(sub, 2, nums[i + preambleLength]);

			if (sumComb.empty())
				return nums[i + preambleLength];
		}
	}

	std::vector<long long> findContiguousSum(const std::vector<long long>& nums, long long goal)
	{
		std::deque<long long> contiguousSet;
		long long sum = 0;
		size_t index = 0;
		while (sum != goal)
		{
			contiguousSet.push_back(nums[index]);
			sum += nums[index];
			while (sum > goal)
			{
				sum -= contiguousSet[0];
				contiguousSet.erase(contiguousSet.begin());
			}
			++index;
			if (index > nums.size())
				return std::vector<long long>();
		}

		return std::vector<long long>(contiguousSet.begin(), contiguousSet.end());
	}
}

int main()
{
	std::vector<std::string> input = IO::readLines("input.txt");
	std::vector<long long> nums;

	for (const std::string& line : input)
		nums.push_back(stoll(line));

	long long outlier = Codevent9::findOutlier(nums, 25);
	std::cout << "Outlier is : " << outlier << std::endl;
	std::vector<long long> contiguousSet = Codevent9::findContiguousSum(nums, outlier);
	std::sort(contiguousSet.begin(), contiguousSet.end());
	std::cout << "Sum of min and max of contigious set is: " << contiguousSet.back() + contiguousSet.front() << std::endl;
	return 0;
}