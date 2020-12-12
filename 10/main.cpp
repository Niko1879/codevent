#include "shared.h"
#include <algorithm>
#include <unordered_map>
#include <iostream>

namespace Codevent10
{
	std::vector<int> standardise(std::vector<int>& nums)
	{
		std::vector<int> nums_{ 0 };
		nums_.insert(nums_.end(), nums.begin(), nums.end());
		std::sort(nums_.begin(), nums_.end());
		nums_.push_back(nums_.back() + 3);
		return nums_;
	}
	
	std::unordered_map<size_t, int> countDiffs(const std::vector<int>& nums)
	{
		std::unordered_map<size_t, int> diffs;

		for (size_t i = 0; i < nums.size() - 1; ++i)
		{
			size_t diff = nums[i + 1] - nums[i];
			if (diffs.find(diff) == diffs.end())
				diffs.insert(std::make_pair(diff, 1));
			else
				++diffs.at(nums[i + 1] - nums[i]);
		}
	
		return diffs;
	}

	bool isSolvable(const std::vector<int>& nums)
	{
		for (size_t i = 0; i < nums.size() - 1; ++i)
		{
			if (nums[i + 1] - nums[i] > 3)
				return false;
		}

		return true;
	}

	bool isRequired(const std::vector<int>& nums, int num)
	{
		for (size_t i = 0; i < nums.size() - 1; ++i)
		{
			if (nums[i] == num)
				continue;

			if (nums[i + 1] == num)
			{
				if (i + 2 == nums.size())
					return true;

				else if(nums[i + 2] - nums[i] > 3)
					return true;

			}

			if (nums[i + 1] - nums[i] > 3)
				return true;
		}

		return false;
	}

	long long countArrangements(const std::vector<int>& nums)
	{
		std::vector<int> required;
		std::vector<int> notRequired;
		for (int num : nums)
			isRequired(nums, num) ? required.push_back(num) : notRequired.push_back(num);
		
		long long count = 1;
		int prev = 0;

		for (int num : required)
		{
			int options = std::count_if(notRequired.begin(), notRequired.end(), [num, prev](int x) {return prev < x && x < num; });
			if (options > 0)
			{
				long long exp = (long long)(powl(2, options) + 0.1);
				(num - prev > 3) ? count *= (exp - 1) : count *= exp;
			}
			prev = num;
		}

		return count;
	}
}

int main()
{
	std::vector<std::string> input = Shared::readLines("input.txt");
	std::vector<int> nums;
	for (const std::string& line : input)
		nums.push_back(stoi(line));
	nums = Codevent10::standardise(nums);

	std::unordered_map<size_t, int> diffs = Codevent10::countDiffs(nums);
	std::cout << "The number of 1 jolt differences multiplied by the number of 3 jolt differences is: "
		<< diffs.at(1) * diffs.at(3) << std::endl;

	std::cout << "The number of possible arrangements is: " << Codevent10::countArrangements(nums) << std::endl;
	return 0;
}