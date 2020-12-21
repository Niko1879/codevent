#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include "IO.h"

namespace Codevent18
{
	typedef long long (*fn)(long long, long long);

	enum class TokenType { NUMBER, OPERATION, OPENBRACKET, CLOSEBRACKET };

	const char OPENBRACKET = '(';
	const char CLOSEBRACKET = ')';
	const char PLUS = '+';
	const char TIMES = '*';

	const std::unordered_map<std::string, fn> BINARYOPS(
	{
		{"+", [](long long a, long long b) {return a + b; }},
		{"*", [](long long a, long long b) {return a * b; }},
	});

	const std::unordered_map<char, TokenType> CHARTYPEMAP(
	{
		{OPENBRACKET, TokenType::OPENBRACKET},
		{CLOSEBRACKET, TokenType::CLOSEBRACKET},
		{PLUS, TokenType::OPERATION},
		{TIMES, TokenType::OPERATION},
	});

	const std::unordered_map<std::string, int> PRECEDENCE(
	{
		{"+", 1},
		{"*", 0},
	});

	struct Token
	{
		Token(TokenType type, std::string value) : type(type), value(value) {}

		const TokenType type;
		const std::string value;
	};

	std::vector<Token> tokenise(const std::string& expression)
	{
		std::vector<Token> tokens;
		std::stringstream ss; //to store integers length > 1

		for (size_t i = 0; i < expression.size(); ++i)
		{
			//check for numbers length > 1
			char curr = expression[i];
			while (i < expression.size() && isdigit(curr = expression[i]))
			{
				++i;
				ss << curr;
			}

			//create number tok and clear number buffer
			if (!ss.str().empty())
			{
				tokens.push_back(Token(TokenType::NUMBER, ss.str()));
				ss.str("");
			}

			//in case while loop above flows off the end of the string
			if (i == expression.size()) break;

			if (isspace(curr))
			{
				continue;
			}

			std::string val = std::string(1, curr);
			tokens.push_back(Token(CHARTYPEMAP.at(curr), val));
		}

		return tokens;
	}

	std::vector<Token> toPostfix(const std::vector<Token>& tokens, bool useOperatorPrecedence = false)
	{
		std::vector<Token> outputQueue;
		std::vector<Token> operatorStack;
		for (const Token &t : tokens)
		{
			switch (t.type)
			{
			case TokenType::NUMBER:
				outputQueue.push_back(t);
				break;

			case TokenType::OPERATION:
				while (!operatorStack.empty() && 
					operatorStack.back().type == TokenType::OPERATION &&
					(PRECEDENCE.at(operatorStack.back().value) >= PRECEDENCE.at(t.value) || !useOperatorPrecedence))
				{
					outputQueue.push_back(operatorStack.back());
					operatorStack.pop_back();
				}
				operatorStack.push_back(t);
				break;

			case TokenType::OPENBRACKET:
				operatorStack.push_back(t);
				break;

			case TokenType::CLOSEBRACKET:
				while (!operatorStack.empty() && operatorStack.back().type != TokenType::OPENBRACKET)
				{
					outputQueue.push_back(operatorStack.back());
					operatorStack.pop_back();
				}

				if (!operatorStack.empty())
				{
					operatorStack.pop_back();
				}

				break;

			default:
				std::cout << "unrecognised token: " << t.value << std::endl;
				break;
			}
		}

		while (!operatorStack.empty())
		{
			outputQueue.push_back(operatorStack.back());
			operatorStack.pop_back();
		}

		return outputQueue;
	}

	long long eval(const std::vector<Token>& expression)
	{
		std::vector<long long> stack;

		for (const Token& t : expression)
		{
			switch (t.type)
			{
			case TokenType::NUMBER:
				stack.push_back(stoll(t.value));
				break;

			case TokenType::OPERATION:
				long long l = stack.back();
				stack.pop_back();
				long long r = stack.back();
				stack.pop_back();
				stack.push_back(BINARYOPS.at(t.value)(l, r));
				break;
			}
		}

		return stack.back();
	}
}

int main()
{
	std::vector<std::string> input = IO::readLines("input.txt");
	long long total = 0;
	for (const std::string& line : input)
	{
		std::vector<Codevent18::Token> tokens = Codevent18::tokenise(line);
		std::vector<Codevent18::Token> postfix = Codevent18::toPostfix(tokens);
		total += Codevent18::eval(postfix);
	}

	std::cout << total << std::endl;

	//part 2
	total = 0;
	for (const std::string& line : input)
	{
		std::vector<Codevent18::Token> tokens = Codevent18::tokenise(line);
		std::vector<Codevent18::Token> postfix = Codevent18::toPostfix(tokens, true);
		total += Codevent18::eval(postfix);
	}

	std::cout << total << std::endl;
}