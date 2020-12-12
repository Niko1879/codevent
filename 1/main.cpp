#include <IO.h>
#include <acmath.h>
#include <iostream>

int main()
{

	std::vector<std::string> lines = IO::readLines("input.txt");
	std::vector<long long> data;
	for (const std::string& l : lines) data.push_back(stoll(l));
	std::vector<long long> sumTo2020 = AcMath::sumCombination(data, 2, 2020);
	int a = sumTo2020[0];
	int b = sumTo2020[1];
	std::cout << "The two numbers which add up to 2020 are " << a << " and " << b << std::endl;
	std::cout << "Their product is " << a * b << std::endl;

	std::cout << std::endl;

	std::vector<long long> tripleTo2020 = AcMath::sumCombination(data, 3, 2020);
	a = tripleTo2020[0];
	b = tripleTo2020[1];
	int c = tripleTo2020[2];
	std::cout << "The three numbers which add up to 2020 are " << a << " and " << b << " and " << c << std::endl;
	std::cout << "Their product is " << a * b * c;




	return 0;
}