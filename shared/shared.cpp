#include "shared.h"
#include "fstream"
#include <sstream>
#include <string>
#include <iostream>

namespace Shared
{
	std::vector<std::string> readLines(const std::string& filePath)
	{
		std::vector<std::string> lines;
		std::ifstream f;
		f.open(filePath);
		if (!f.good()) throw std::runtime_error("Error opening file " + filePath);
		std::string line;
		while (std::getline(f, line))
		{
			try
			{
				lines.push_back(line);
			}
			catch (...)
			{
				f.close();
				throw;
			}
		}
		f.close();
		return lines;
	}

	std::vector<std::string> split(const std::string& str, const std::string& delim)
	{
		std::vector<std::string> strs;
		size_t last = 0;
		size_t next = 0;
		while ((next = str.find(delim, last)) != std::string::npos)
		{
			strs.push_back(str.substr(last, next - last));
			last = next + delim.size();
		}
		if(last < str.size())
			strs.push_back(str.substr(last));
		return strs;
	}

	bool isInteger(const std::string& s)
	{
		for (char c : s)
		{
			if (!isdigit(c)) return false;
		}
		return true;
	}

	std::vector<std::vector<std::string>> group(const std::vector<std::string> lines)
	{
		std::vector<std::vector<std::string>> g;
		std::vector<std::string> tmp;
		for (const std::string& line : lines)
		{
			if (line == "")
			{
				g.push_back(tmp);
				tmp.clear();
			}
			else
			{
				tmp.push_back(line);
			}
		}
		if (!tmp.empty()) g.push_back(tmp);
		return g;
	}

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