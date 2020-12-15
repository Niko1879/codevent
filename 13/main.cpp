#include <IO.h>
#include <acstring.h>
#include <algorithm>
#include <iostream>


int main()
{
	std::vector<std::string> input = IO::readLines("input.txt");
	int arrivalTime = stoi(input[0]);
	std::vector<std::string> toks = AcString::split(input[1], ",");
	std::vector<int> shuttleNumbers;

	for (const std::string& line : toks)
	{
		if (line != "x")
			shuttleNumbers.push_back(stoi(line));
	}
	//wait time = shuttleNumber - arrivalTime % shuttleNumber

	std::sort(shuttleNumbers.begin(), shuttleNumbers.end(), [arrivalTime](int x, int y) {return x - arrivalTime % x < y - arrivalTime % y; });
	int shuttleId = shuttleNumbers[0];
	int waitTime = shuttleId - (arrivalTime % shuttleId);
	std::cout << "Earliest shuttle ID multiplied by wait time is: " << shuttleId * waitTime << std::endl;

	//part 2

	std::vector<long long> longShuttleNums;
	std::vector<long long> offsets;
	for (int i = 0; i < toks.size(); ++i)
	{
		if (toks[i] != "x")
		{
			longShuttleNums.push_back(stoll(toks[i]));
			offsets.push_back((long long)i);
		}
	}

	long long inc = 1;
	long long t = 0;
	size_t index = 0;
	while (index < longShuttleNums.size())
	{
		t += inc;
		
		if ((t + offsets[index]) % longShuttleNums[index] == 0)
		{
			inc *= longShuttleNums[index];
			++index;
		}
	}

	std::cout << t << std::endl;

	return 0;
}