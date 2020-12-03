#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

namespace Codevent1
{
	std::vector<int> getData(const std::string& filePath)
	{
		std::vector<int> nums;
		std::ifstream f;
		f.open(filePath);
		if (!f.good()) throw std::runtime_error("Error opening file " + filePath);
		std::string line;
		while (f >> line)
		{
			try
			{
				nums.push_back(stoi(line));
			}
			catch (...)
			{
				f.close();
				throw;
			}
		}
		f.close();
		return nums;
	}

	std::vector<int> getSumPair(std::vector<int>& nums, int target)
	{
		for (int i : nums)
			for (int j : nums)
				if (i + j == target) return std::vector<int>{i, j};
		return std::vector<int>{-1, -1};
	}

	std::vector<int> getSumTriple(std::vector<int>& nums, int target)
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
		std::vector<int> data = Codevent1::getData("input.txt");
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