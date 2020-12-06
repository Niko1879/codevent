#pragma once
#include <vector>
#include <string>

namespace Shared

{
	std::vector<std::string> readLines(const std::string& filePath);
	std::vector<std::string> split(const std::string& str, const std::string& delim);
	bool isInteger(const std::string& s);
	std::vector<std::vector<std::string>> group(const std::vector<std::string> lines);

}