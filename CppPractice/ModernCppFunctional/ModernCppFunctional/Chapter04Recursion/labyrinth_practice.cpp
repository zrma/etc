#include "pch.h"

#include <boost/range/adaptor/indexed.hpp>
#include <thread>

#include "labyrinth_practice.h"
#include "../Common/util.h"

const int rows = 8;
const int cols = 8;

using labyrinth = std::vector<std::vector<char>>;

auto create_labyrinth()
{
	return labyrinth {
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

void display_labyrinth(const labyrinth labyrinth)
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

auto navigate(labyrinth labyrinth, const int row, const int col)
{
	display_labyrinth(labyrinth);

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

	if (row + 1 < rows && navigate(labyrinth, row + 1, col))
	{
		return true;
	}
	if (col + 1 < cols && navigate(labyrinth, row, col + 1))
	{
		return true;
	}
	if (row - 1 >= 0 && navigate(labyrinth, row - 1, col))
	{
		return true;
	}
	if (col - 1 >= 0 && navigate(labyrinth, row, col - 1))
	{
		return true;
	}

	return false;
}

auto is_labyrinth_solvable(const labyrinth labyrinth)
{
	auto start_row = -1;
	auto start_col = -1;

	for (const auto& row : labyrinth | boost::adaptors::indexed(0))
	{
		for (const auto& col : row.value() | boost::adaptors::indexed(0))
		{
			if (col.value() == 'S')
			{
				start_row = static_cast<int>(row.index());
				start_col = static_cast<int>(col.index());
				break;
			}
		}
	}

	if ( start_row == -1 || start_col == -1 )
	{
		std::cerr << "No valid starting point found!" << std::endl;
		return false;
	}

	std::cout << "Starting at point (" << start_row << ", " << start_col << ")" << std::endl;
	return navigate(labyrinth, start_row, start_col);
}

void labyrinth_practice()
{
	print_title("labyrinth");

	const auto labyrinth = create_labyrinth();
	display_labyrinth(labyrinth);

	std::string line;
	std::cout << std::endl << "Press enter to continue..." << std::endl;
	std::getline(std::cin, line);

	if( is_labyrinth_solvable(labyrinth))
	{
		std::cout << "Labyrinth solved!" << std::endl;
	}
	else
	{
		std::cout << "Labyrinth could not be solved!" << std::endl;
	}
}