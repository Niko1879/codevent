#include <iostream>
#include <unordered_map>
#include <acstring.h>
#include <IO.h>

namespace Codevent8
{

	struct Instruction
	{
		Instruction(std::string command, int value) : command(command), value(value) {}
		std::string command;
		const int value;
	};

	Instruction parseInstruction(const std::string& input)
	{
		std::vector<std::string> toks = Shared::split(input, " ");
		return Instruction(toks[0], stoi(toks[1]));
	}
	
	class Console
	{
	public:
		Console() : accumulator(0), instructionPointer(0) {}
		bool Boot(const std::vector<Instruction>& instructions) 
		{
			std::vector<size_t> seen;
			while (instructionPointer < instructions.size())
			{
				if (!seen.empty() && std::find(seen.begin(), seen.end(), instructionPointer) != seen.end())
					return false;
				seen.push_back(instructionPointer);
				exec(instructions[instructionPointer]);
			}

			return true;
		}

		void reset()
		{
			accumulator = 0;
			instructionPointer = 0;
		}

		size_t getAccumulator()
		{
			return accumulator;
		}

	private:
		void exec(const Instruction& i)
		{

			if (i.command == "nop")
				++instructionPointer;

			else if (i.command == "jmp")
				instructionPointer += i.value;

			else if (i.command == "acc")
			{
				accumulator += i.value;
				++instructionPointer;
			}

			else
				std::cout << "Unrecognised instruction" << std::endl;
			
		}

		int accumulator;
		size_t instructionPointer;
	};

	void tryReplace(const std::string& toReplace, const std::string& replaceWith, std::vector<Codevent8::Instruction>& instructions)
	{
		Console console;
		for (Instruction& i : instructions)
		{
			if (i.command == toReplace)
			{
				i.command = replaceWith;
				if (console.Boot(instructions))
				{
					std::cout << "Successfully booted with accumulator value: " << console.getAccumulator() << std::endl;
					break;
				}
				console.reset();
				i.command = toReplace;
			}
		}
	}
}

int main()
{
	Codevent8::Console console;
	std::vector<std::string> input = Shared::readLines("input.txt");
	std::vector<Codevent8::Instruction> instructions;
	for (const std::string& s : input)
		instructions.push_back(Codevent8::parseInstruction(s));

	console.Boot(instructions);
	std::cout << "Initial accumulator value upon looping is: " << console.getAccumulator() << std::endl;
	Codevent8::tryReplace("nop", "jmp", instructions);
	Codevent8::tryReplace("jmp", "nop", instructions);
	return 0;
	
}
