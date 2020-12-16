#include <iostream>
#include <vector>
#include <IO.h>
#include <acstring.h>
#include <numeric>
#include <algorithm>

namespace Codevent14
{
	class SeaportSystem
	{
	public:

		void addInstruction(const std::string& instruction)
		{
			instructions.push_back(instruction);
		}

		void run(bool useAddrMask)
		{
			for (const std::string& instruction : instructions)
			{
				std::vector<std::string> toks = AcString::split(instruction, " = ");
				if (toks[0] == "mask")
					setBitMask(toks[1]);
				else
				{
					std::vector<std::string> subtoks = AcString::split(toks[0], "[");
					std::string strIndex = AcString::split(subtoks[1], "]")[0];
					uint64_t index = stoll(strIndex);
					uint64_t value = stoll(toks[1]);
					if (useAddrMask)
					{
						std::vector<uint64_t> addresses = applyMaskToAddr(index);
						for (uint64_t addr : addresses)
							setMemoryAddress(addr, value, false);
					}

					else
						setMemoryAddress(index, value, true);
				}
			}

			writeBuffers();
		}

		uint64_t memSum()
		{
			return std::accumulate(addressSpace.begin(), addressSpace.end(), (uint64_t)0);
		}

		void reset()
		{
			valueBuffer.clear();
			indexBuffer.clear();
			addressSpace.clear();
			for (size_t i = 0; i < NUM_BITS; ++i)
				bitMask[i] = 0;
		}

	private:
		void setBitMask(const std::string& mask)
		{
			for (int i = 0; i < mask.size(); ++i)
			{
				switch (mask[i])
				{
				case '1':
					bitMask[i] = 1;
					break;

				case '0':
					bitMask[i] = 0;
					break;

				default:
					bitMask[i] = -1;
					break;
				}
			}
		}

		void setMemoryAddress(uint64_t index, uint64_t num, bool useMask = true)
		{
			if (useMask)
				num = applyMask(num);
			indexBuffer.push_back(index);
			valueBuffer.push_back(num);
		}

		uint64_t applyMask(uint64_t num)
		{
			uint64_t value = 0;
			for (uint64_t i = 0; i < NUM_BITS; ++i)
			{
				value = value << 1;
				if (((bitMask[i] == -1) && (num & (uint64_t)1 << (NUM_BITS - i - 1))) || (bitMask[i] == 1))
					++value;

			}
			return value;
		}

		std::vector<uint64_t> applyMaskToAddr(uint64_t index)
		{
			std::vector<uint64_t> values = { (uint64_t)0 };
			for (uint64_t i = 0; i < NUM_BITS; ++i)
			{
				size_t length = values.size();
				for (size_t j = 0; j < length; ++j)
				{
					values[j] = values[j] << 1;

					switch (bitMask[i])
					{
					case 1:
						++values[j];
						break;

					case -1:
						values.push_back(values[j]); 
						++values[j]; 
						break;

					default:
						if (index & (uint64_t)1 << (NUM_BITS - i - 1))
							++values[j];
						break;
					}
				}
			}

			return values;
		}

		void writeBuffers()
		{
			std::vector<uint64_t> checked;
			for (uint64_t index : indexBuffer)
			{
				if (checked.empty() || std::find(checked.begin(), checked.end(), index) == checked.end())
				{
					auto it = std::find(indexBuffer.rbegin(), indexBuffer.rend(), index);
					size_t valIndex = indexBuffer.rend() - it - 1;
					addressSpace.push_back(valueBuffer[valIndex]);
					checked.push_back(index);
				}
			}

			valueBuffer.clear();
			indexBuffer.clear();
		}

		const static size_t NUM_BITS = 36;
		int bitMask[NUM_BITS] = { 0 };
		std::vector<uint64_t> addressSpace;
		std::vector<uint64_t> indexBuffer;
		std::vector<uint64_t> valueBuffer;
		std::vector<std::string> instructions;
	};

}

int main()
{
	std::vector<std::string> input = IO::readLines("input.txt");
	Codevent14::SeaportSystem sys;
	for (const std::string& line : input)
		sys.addInstruction(line);
	
	//part 1
	sys.run(false);
	std::cout << "Sum of memory addresses is: " << sys.memSum() << std::endl;

	//part 2
	sys.reset();
	sys.run(true);
	std::cout << "Sum of memory addresses is: " << sys.memSum() << std::endl;

	return 0;
}