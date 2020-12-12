#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <acstring.h>
#include <IO.h>

namespace Codevent7
{
	typedef std::unordered_map<std::string, size_t> BagContents;
	typedef std::unordered_map<std::string, BagContents> Bags;

	Bags parseBags(const std::vector<std::string>& input)
	{
		Bags bags;
		for (const std::string& line : input)
		{
			BagContents contents;
			std::vector<std::string> toks = AcString::split(line, " contain ");
			std::vector<std::string> colorQs = AcString::split(toks[0], " ");
			std::string color = colorQs[0] + " " + colorQs[1];
			toks[1] = AcString::split(toks[1], ".")[0];
			std::vector<std::string> bagParamList = AcString::split(toks[1], ", ");

			bags.insert(std::make_pair(color, contents));

			for (const std::string& params : bagParamList)
			{
				std::vector<std::string> bagParams = AcString::split(params, " ");
				if (bagParams[0] == "no") break; //lol
				size_t qty = stoi(bagParams[0]);
				std::string color_ = bagParams[1] + " " + bagParams[2];
				auto it = bags.at(color).insert(std::make_pair(color_, qty));
			}
		}
		return bags;
	}

	bool canContain(const Bags& b, const std::string& key, const std::string& bColor)
	{

		if (key == bColor)
			return true;

		BagContents cont = b.at(key);
		
		if (cont.empty())
			return false;

		for (const std::pair<std::string, size_t>& p : cont)
		{
			if (canContain(b, p.first, bColor))
				return true;
		}

		return false;
	}

	std::vector<std::string> getUniqueColors(const Bags& b)
	{
		std::vector<std::string> cols;
		for (const std::pair<std::string, BagContents>& bag : b)
		{
			if (cols.empty() || std::find(cols.begin(), cols.end(), bag.first) == cols.end())
			cols.push_back(bag.first);
		}
		return cols;
	}

	size_t sumContents(const Bags& b, const std::string& key)
	{
		BagContents contents = b.at(key);
		if (contents.empty())
			return 0;

		size_t sum = 0;
		for (const std::pair<std::string, size_t>& bag : contents)
		{
			sum += bag.second + bag.second * sumContents(b, bag.first);
		}
		return sum;
	}

	void question1(const std::vector<std::string>& input)
	{
		auto bags = Codevent7::parseBags(input);
		auto cols = Codevent7::getUniqueColors(bags);
		size_t ans = 0;
		for (const auto& c : cols)
		{
			if (Codevent7::canContain(bags, c, "shiny gold"))
				++ans;
		}
		--ans;
		std::cout << "The number of bags which can contain shiny golds bags is: " << ans << std::endl;
	}

	void question2(const std::vector<std::string>& input)
	{
		auto bags = Codevent7::parseBags(input);
		std::cout << "The number of bags a shiny gold bag must contain is: " << sumContents(bags, "shiny gold") << std::endl;
	}
}

int main()
{
	std::vector<std::string> lines = IO::readLines("input.txt");
	//Codevent7::question1(lines);
	Codevent7::question2(lines);
	return 0;
}