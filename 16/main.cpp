#include <vector>
#include <string>
#include <acstring.h>
#include <IO.h>
#include <iostream>
#include <unordered_map>

namespace Codevent16
{
	class Rule
	{
	public:
		Rule(std::string name, int min1, int max1, int min2, int max2) :
			min1(min1), 
			max1(max1), 
			min2(min2), 
			max2(max2), 
			name(name) 
		{}

		const std::string& getName() const
		{
			return name;
		}

		bool check(int value) const
		{
			return (min1 <= value && value <= max1) ||
				   (min2 <= value && value <= max2);
		}

	private:
		int min1;
		int max1;
		int min2;
		int max2;
		const std::string name;
	};

	Rule parseRule(const std::string& input)
	{
		std::string name = AcString::split(input, ":")[0];
		std::string range1 = AcString::split(input, ": ")[1];
		std::string range2 = AcString::split(input, " or ")[1];

		std::vector<std::string> range1toks = AcString::split(range1, "-");
		std::vector<std::string> range2toks = AcString::split(range2, "-");
		int min1 = stoi(range1toks[0]);
		int max1 = stoi(range1toks[1]);
		int min2 = stoi(range2toks[0]);
		int max2 = stoi(range2toks[1]);

		return Rule(name, min1, max1, min2, max2);
	}

	class Rules
	{
	public:
		std::vector<std::string> getAllNames()
		{
			std::vector<std::string> names;
			for (const std::pair<std::string, Rule>& rule : rules)
				names.push_back(rule.first);
			return names;
		}

		void add(Rule rule)
		{
			rules.insert(std::make_pair(rule.getName(), rule));
		}

		bool check(const std::string& key, int value)
		{
			return rules.at(key).check(value);
		}

		bool checkAny(int value)
		{
			for (const std::pair<std::string, Rule>& rule: rules)
				if (rule.second.check(value))
					return true;
			return false;
		}

		bool checkAll(const std::vector<int>& values)
		{
			for (int v : values)
				if (!checkAny(v))
					return false;
			return true;
		}

	private:
		std::unordered_map<std::string, Rule> rules;
	};
}

int main()
{
	//read input.txt
	std::vector<std::string> input = IO::readLines("input.txt");
	std::vector<std::vector<std::string>> grps = AcString::group(input);
	
	//parse rules
	Codevent16::Rules rules;
	std::vector<std::string> rulesVec = grps[0];
	for (const std::string& rule : rulesVec)
		rules.add(Codevent16::parseRule(rule));

	//parse my ticket
	std::string myTicketStr = grps[1][1];
	std::vector<int> myTicket;
	for (const std::string& s : AcString::split(myTicketStr, ","))
		myTicket.push_back(stoi(s));
	
	//parse tickets
	std::vector<std::vector<int>> tickets;
	std::vector<std::string> ticketsVec = grps[2];
	for (const std::string& ticket : ticketsVec)
	{
		if (ticket == "nearby tickets:")
			continue;
		std::vector<int> t;
		std::vector<std::string> toks = AcString::split(ticket, ",");
		for (const std::string& str : toks)
			t.push_back(stoi(str));
		tickets.push_back(t);
	}

	//compute error rate
	int errorRate = 0;
	for (const std::vector<int>& ticket : tickets)
		for (int field : ticket)
			if (!rules.checkAny(field))
				errorRate += field;

	std::cout << "The error rate is: " << errorRate << std::endl;

	//part 2
	//get valid tickets
	std::vector<std::vector<int>> validTickets;
	for (const std::vector<int>& ticket : tickets)
		if (rules.checkAll(ticket))
			validTickets.push_back(ticket);

	//map rule names to the indices of ticket fields for which they could apply
	std::unordered_map<std::string, std::vector<size_t>> possibleFields;
	std::vector<std::string> fieldNames = rules.getAllNames();
	for (const std::string& fName : fieldNames)
	{
		for (size_t i = 0; i < tickets[0].size(); ++i)
		{
			bool isValid = true;
			for (const std::vector<int>& ticket : validTickets)
			{
				if (!rules.check(fName, ticket[i]))
				{
					isValid = false;
					break;
				}
			}

			if (isValid)
				possibleFields[fName].push_back(i);
		}
	}

	//forward chain inference
	//list of indices which are confirmed to be a given field
	std::vector<size_t> confirmedIndices;
	std::unordered_map<std::string, size_t> definiteFields;

	

	while (confirmedIndices.size() < fieldNames.size())
	{
		for (const auto& p : possibleFields)
		{
			//skip confirmed
			if (definiteFields.count(p.first) > 0)
				continue;
			std::vector<size_t> opts;
			for (size_t i : p.second)
			{
				if (confirmedIndices.empty() || std::find(confirmedIndices.begin(), confirmedIndices.end(), i) == confirmedIndices.end())
					opts.push_back(i);
			}

			if (opts.size() == 1)
			{
				size_t val = opts.back();
				definiteFields[p.first] = val;
				confirmedIndices.push_back(val);
			}
		}
	}

	for (int a : myTicket)
		std::cout << a << " ";
	std::cout << std::endl;

	uint64_t myDepLoc = myTicket[definiteFields["departure location"]];
	uint64_t myDepSta = myTicket[definiteFields["departure station"]];
	uint64_t myDepPla = myTicket[definiteFields["departure platform"]];
	uint64_t myDepTra = myTicket[definiteFields["departure track"]];
	uint64_t myDepDat = myTicket[definiteFields["departure date"]];
	uint64_t myDepTim = myTicket[definiteFields["departure time"]];

	uint64_t magicNo = myDepLoc * myDepSta * myDepPla * myDepTra * myDepDat * myDepTim;
	
	std::cout << magicNo << std::endl;

	return 0;
}