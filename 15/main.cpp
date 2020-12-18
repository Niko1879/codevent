#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

namespace Codevent15
{
	class NumberGame
	{
	public:
		NumberGame(const std::vector<int>& init) : lastSpoken(0)
		{
			turnNo = 1;
			for (int i : init)
				mLastSpoken.insert(std::make_pair(i, turnNo++));

			original = mLastSpoken;
		}

		void runUntil(size_t maxTurn)
		{
			while (turnNo < maxTurn)
				next();
		}

		int getLastSpoken()
		{
			return lastSpoken;
		}

		void reset()
		{
			mLastSpoken = original;
			turnNo = mLastSpoken.size();
		}
	
	private:
		void next()
		{
			if (mLastSpoken.count(lastSpoken) > 0)
			{
				int tmp = lastSpoken;
				lastSpoken = turnNo - mLastSpoken[lastSpoken];
				mLastSpoken[tmp] = turnNo;
			}

			else
			{
				mLastSpoken[lastSpoken] = turnNo;
				lastSpoken = 0;
			}

			++turnNo;

		}

		std::unordered_map<int, size_t> mLastSpoken;
		size_t turnNo;
		int lastSpoken;
		std::unordered_map<int, size_t> original;
	};
}

int main()
{
	Codevent15::NumberGame game(std::vector<int>{0, 14, 1, 3, 7, 9});
	game.runUntil(2020);
	std::cout << "The 2020th number spoken is: " << game.getLastSpoken() << std::endl;

	//part 2
	game.runUntil(30000000);
	std::cout << "The 30000000th number spoken is: " << game.getLastSpoken() << std::endl;

	
}