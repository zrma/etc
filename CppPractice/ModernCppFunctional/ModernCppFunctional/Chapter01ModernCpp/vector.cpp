#include "pch.h"
#include "vector.h"
#include "../Common/util.h"

void vector_practice()
{
	print_title("vector");

	auto vec = std::vector{ 0, 1, 2 };

	for (const auto& it : vec)
	{
		std::cout << it << " ";
	}
	std::cout << std::endl;

	vec.push_back(3);
	vec.push_back(4);

	vec[2] = 5;
	vec.at(3) = 6;

	for (auto&& it = vec.begin(); it != vec.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	for (auto&& it = std::begin(vec); it != std::end(vec); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	for (auto && it : vec)
	{
		std::cout << it << " ";
	}
}
