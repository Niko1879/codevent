#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include "shared.h"

namespace Codevent1
{
	std::vector<int> getSumPair(const std::vector<int>& nums, int target)
	{
		for (int i : nums)
			for (int j : nums)
				if (i + j == target) return std::vector<int>{i, j};
		return std::vector<int>{-1, -1};
	}

	std::vector<int> getSumTriple(const std::vector<int>& nums, int target)
	{
		for (int i : nums)
			for (int j : nums)
				for (int k : nums)
					if (i + j + k == target) return std::vector<int>{i, j, k};
		return std::vector<int>{-1, -1, -1};
	}

}

int main()
{
	try
	{
		std::vector<std::string> lines = Shared::readLines("input.txt");
		std::vector<int> data;
		for (std::string& l : lines) data.push_back(stoi(l));
		std::vector<int> sumTo2020 = Codevent1::getSumPair(data, 2020);
		int a = sumTo2020[0];
		int b = sumTo2020[1];
		std::cout << "The two numbers which add up to 2020 are " << a << " and " << b << std::endl;
		std::cout << "Their product is " << a * b << std::endl;

		std::cout << std::endl;

		std::vector<int> tripleTo2020 = Codevent1::getSumTriple(data, 2020);
		a = tripleTo2020[0];
		b = tripleTo2020[1];
		int c = tripleTo2020[2];
		std::cout << "The three numbers which add up to 2020 are " << a << " and " << b << " and " << c << std::endl;
		std::cout << "Their product is " << a * b * c;

	}
	catch (std::runtime_error e)
	{
		std::cout << e.what();
	}

	return 0;
}