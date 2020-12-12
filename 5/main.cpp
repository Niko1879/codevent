#include <cassert>
#include <iostream>
#include <algorithm>
#include <IO.h>

namespace Codevent5
{
	size_t bsp(const std::string& str, size_t min, size_t max, char lkey, char ukey)
	{
		for (char c : str)
		{
			if (c == lkey)
				max = (max + min) / 2;

			else if (c == ukey)
				min = (max + min + 1) / 2;
		}

		if (min == max) return min;
		std::cout << "could not decode: " << str << std::endl;
		return 0;
	}

	std::vector<size_t> getSeatIds(const std::vector<std::string>& input)
	{
		std::vector<size_t> rowNums;
		std::vector<size_t> colNums;

		for (const std::string& s : input)
		{
			std::string rowId(s.begin(), s.begin() + 7);
			std::string colId(s.begin() + 7, s.end());
			rowNums.push_back(Codevent5::bsp(rowId, 0, 127, 'F', 'B'));
			colNums.push_back(Codevent5::bsp(colId, 0, 7, 'L', 'R'));
		}

		std::vector<size_t> seatIds;
		for (size_t i = 0; i < rowNums.size(); i++)
		{
			seatIds.push_back(8 * rowNums[i] + colNums[i]);
		}

		return seatIds;
	}

	void question1(const std::vector<std::string>& input)
	{
		
		std::vector<size_t> seatIds = getSeatIds(input);
		auto it = std::max_element(seatIds.begin(), seatIds.end());
		std::cout << "The highest seat ID is: " << *it << std::endl;
	}

	void question2(const std::vector<std::string>& input)
	{
		std::vector<size_t> seatIds = getSeatIds(input);
		std::sort(seatIds.begin(), seatIds.end());
		for (size_t i = 0; i < seatIds.size()-1; i++)
		{
			if (seatIds[i + 1] - seatIds[i] == 2) 
				std::cout << "Your seat ID is: " << (seatIds[i] + 1) << std::endl;
		}
	}

}

int main()
{
	auto input = IO::readLines("input.txt");
	Codevent5::question1(input);
	Codevent5::question2(input);
	return 0;
}