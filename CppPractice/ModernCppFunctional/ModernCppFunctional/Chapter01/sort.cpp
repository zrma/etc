#include "pch.h"

#include "sort.h"
#include "../Common/util.h"

auto Comparer(int a, int b)
{
	return a > b;
}

void SortPractice()
{
	PrintTitle("sort");

	std::vector<int> vec = { 20, 43, 11, 78, 5, 96 };
	for (const auto& it : vec)
	{
		std::cout << it << " ";
	}
	std::cout << std::endl;

	std::sort(vec.begin(), vec.end());
	for (const auto& it : vec)
	{
		std::cout << it << " ";
	}
	std::cout << std::endl;

	std::sort(std::begin(vec), std::end(vec), Comparer);
	for (const auto& it : vec)
	{
		std::cout << it << " ";
	}
	std::cout << std::endl;
}
