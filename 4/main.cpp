#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <IO.h>
#include <acstring.h>

namespace Codevent4
{
	typedef std::unordered_map<std::string, std::string> passport;

	const std::vector<std::string> requiredFields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
	const std::vector<char> validc{ '0', '1', '2','3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e' ,'f' };
	const std::vector<std::string> valide{ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };


	passport parseport(const std::vector<std::string>& data)
	{
		passport p;
		for (const std::string& line : data)
		{
			std::vector<std::string> tokens = AcString::split(line, " ");
			for (const std::string& t : tokens)
			{
				std::vector<std::string> tokens_ = AcString::split(t, ":");
				p.insert(std::make_pair(tokens_[0], tokens_[1]));
			}
		}

		return p;
	}

	bool validateRange(int min, int max, int val)
	{
		return min <= val && val <= max;
	}

	bool validateHeight(const std::string& h)
	{
		if (h.length() < 3) return false;
		
		std::string suffix(h.end() - 2, h.end());
		std::string prefix(h.begin(), h.end() - 2);
		
		if (!AcString::isInteger(prefix)) return false;

		if (suffix == "cm") return validateRange(150, 193, stoi(prefix));
		if (suffix == "in") return validateRange(59, 76, stoi(prefix));
		return false;
	}

	bool validateHairColor(const std::string& h)
	{
		if (h[0] != '#') return false;
		if (h.length() != 7) return false;
		for (int i = 1; i<h.length(); i++)
		{
			if (std::find(validc.begin(), validc.end(), h[i]) == validc.end())
				return false;
		}
		return true;
	}

	bool validateEyeColor(const std::string& h)
	{
		return std::find(valide.begin(), valide.end(), h) != valide.end();
	}

	bool validatePid(const std::string& h)
	{
		return AcString::isInteger(h) && h.length() == 9;
	}

	bool isValidPassport(const passport& p)
	{
		for (const std::string& s : requiredFields)
		{
			if (!p.count(s)) return false;
		}

		for (std::pair<std::string, std::string> pr : p)
		{
			if (pr.first == "byr") 
				if (!validateRange(1920, 2002, stoi(pr.second)))
					return false;

			if (pr.first == "iyr")
				if (!validateRange(2010, 2020, stoi(pr.second)))
					return false;

			if (pr.first == "eyr")
				if (!validateRange(2020, 2030, stoi(pr.second)))
					return false;

			if (pr.first == "hgt")
				if (!validateHeight(pr.second))
					return false;

			if (pr.first == "hcl")
				if (!validateHairColor(pr.second))
					return false;

			if (pr.first == "ecl")
				if (!validateEyeColor(pr.second))
					return false;

			if (pr.first == "pid")
				if (!validatePid(pr.second))
					return false;
		}
		return true;
	}
}

int main()
{
	std::vector<std::string> lines = IO::readLines("input.txt");
	auto g = AcString::group(lines);
	std::vector<Codevent4::passport> passports;
	for (const std::vector<std::string>& v: g)
	{
		passports.push_back(Codevent4::parseport(v));
	}
	size_t valid = 0;
	for (const Codevent4::passport& p : passports)
	{
		if (Codevent4::isValidPassport(p))
		{
			valid++;
		}
	}
	

	std::cout << "The number of valid passports is: " << valid << std::endl;
}

