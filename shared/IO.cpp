#include "IO.h"
#include <stdexcept>
#include <fstream>

namespace IO
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
}