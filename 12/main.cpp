#include <iostream>
#include <unordered_map>
#include <IO.h>
#include <acstring.h>

namespace Codevent12
{

	class Ship
	{
	public:
		Ship() : xdir(1), ydir(0), xpos(0), ypos(0) {}

		int computeDisplacement()
		{
			return abs(xpos) + abs(ypos);
		}

		void setWaypoint(int x, int y)
		{
			xdir = x;
			ydir = y;
		}

		void reset()
		{
			xdir = 1;
			ydir = 0;
			xpos = 0;
			ypos = 0;
		}

		void move(const std::string& instruction, bool useWaypoint)
		{
			char command = instruction[0];
			int value = stoi(std::string(instruction.begin() + 1, instruction.end()));

			switch (command)
			{
			case 'F':
				move(value);
				break;
			case 'L':
				turnLeft(value);
				break;
			case 'R':
				turnRight(value);
				break;
			default:
				move(value, command, useWaypoint);
				break;
			}
		}

	private:
		void turnLeft(int q)
		{
			for (int i = 0; i < q; i += 90)
			{
				int tmp = xdir;
				xdir = -ydir;
				ydir = tmp;
			}
		}

		void turnRight(int q)
		{
			for (int i = 0; i < q; i += 90)
			{
				int tmp = xdir;
				xdir = ydir;
				ydir = -tmp;
			}
		}

		void move(int q)
		{
			xpos += q * xdir;
			ypos += q * ydir;
		}

		void move(int q, char dir, bool useWaypoint)
		{
			int* x = useWaypoint ? &xdir : &xpos;
			int* y = useWaypoint ? &ydir : &ypos;
			switch (dir)
			{
			case 'E':
				*x += q;
				break;

			case 'W':
				*x -= q;
				break;

			case 'N':
				*y += q;
				break;

			case 'S':
				*y -= q;
				break;

			default:
				std::cout << "Unknown direction: " << dir <<  std::endl;
				break;
			}
		}

		int xdir;
		int ydir;
		int xpos;
		int ypos;
	};
}

int main()
{
	Codevent12::Ship ship;
	std::vector<std::string> input = IO::readLines("input.txt");
	for (const std::string& line : input)
	{
		ship.move(line, false);
	}
	std::cout << "Displacement is: " << ship.computeDisplacement() << std::endl;
	
	ship.reset();
	ship.setWaypoint(10, 1);
	for (const std::string& line : input)
	{
		ship.move(line, true);
	}
	std::cout << "Displacement using waypoint is: " << ship.computeDisplacement() << std::endl;

	return 0;
}