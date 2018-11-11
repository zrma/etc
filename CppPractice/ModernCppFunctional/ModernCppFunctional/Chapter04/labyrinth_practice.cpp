#include "pch.h"

#include <boost/range/adaptor/indexed.hpp>
#include <thread>

#include "labyrinth_practice.h"
#include "../Common/util.h"

const int ROWS = 8;
const int COLS = 8;

using Labyrinth = std::vector<std::vector<char>>;

auto CreateLabyrinth()
{
	return Labyrinth {
		{ '#', '#', '#', '#', '#', '#', '#', '#' },
		{ '#', 'S', ' ', ' ', ' ', ' ', ' ', '#' },
		{ '#', '#', '#', ' ', '#', '#', '#', '#' },
		{ '#', ' ', '#', ' ', '#', '#', '#', '#' },
		{ '#', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
		{ '#', ' ', '#', '#', '#', '#', '#', '#' },
		{ '#', ' ', ' ', ' ', ' ', ' ', 'F', '#' },
		{ '#', '#', '#', '#', '#', '#', '#', '#' },
	};
}

void DisplayLabyrinth(const Labyrinth labyrinth)
{
	std::cout << std::endl;
	std::cout << "========================" << std::endl;
	std::cout << "The Labyrinth" << std::endl;
	std::cout << "========================" << std::endl;

	for (const auto& row : labyrinth)
	{
		for (const auto& col : row)
		{
			std::cout << col << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "========================" << std::endl << std::endl;
}

auto Navigate(Labyrinth labyrinth, const int row, const int col)
{
	DisplayLabyrinth(labyrinth);

	std::cout << "Checking cell (" << col << ", " << row << ")" << std::endl;

	const std::chrono::milliseconds duration(10);
	std::this_thread::sleep_for(duration);

	auto& cur = labyrinth.at(row).at(col);
	if (cur == 'F')
	{
		std::cout << "Found the finish flag at point (" << row << ", " << col << ")" << std::endl;
		return true;
	}
	if (cur == '#' || cur == '*')
	{
		return false;
	}
	if (cur == ' ')
	{
		cur = '*';
	}

	if (row + 1 < ROWS && Navigate(labyrinth, row + 1, col))
	{
		return true;
	}
	if (col + 1 < COLS && Navigate(labyrinth, row, col + 1))
	{
		return true;
	}
	if (row - 1 >= 0 && Navigate(labyrinth, row - 1, col))
	{
		return true;
	}
	if (col - 1 >= 0 && Navigate(labyrinth, row, col - 1))
	{
		return true;
	}

	return false;
}

auto IsLabyrinthSolvable(const Labyrinth labyrinth)
{
	auto startRow = -1;
	auto startCol = -1;

	for (const auto& row : labyrinth | boost::adaptors::indexed(0))
	{
		for (const auto& col : row.value() | boost::adaptors::indexed(0))
		{
			if (col.value() == 'S')
			{
				startRow = static_cast<int>(row.index());
				startCol = static_cast<int>(col.index());
				break;
			}
		}
	}

	if ( startRow == -1 || startCol == -1 )
	{
		std::cerr << "No valid starting point found!" << std::endl;
		return false;
	}

	std::cout << "Starting at point (" << startRow << ", " << startCol << ")" << std::endl;
	return Navigate(labyrinth, startRow, startCol);
}

void LabyrinthPractice()
{
	PrintTitle("labyrinth");

	const auto labyrinth = CreateLabyrinth();
	DisplayLabyrinth(labyrinth);

	std::string line;
	std::cout << std::endl << "Press enter to continue..." << std::endl;
	std::getline(std::cin, line);

	if( IsLabyrinthSolvable(labyrinth))
	{
		std::cout << "Labyrinth solved!" << std::endl;
	}
	else
	{
		std::cout << "Labyrinth could not be solved!" << std::endl;
	}
}