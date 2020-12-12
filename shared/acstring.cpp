#include "acstring.h"

namespace AcString
{
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
		if (last < str.size())
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
}