#include "pch.h"

#include "sort.h"
#include "../Common/util.h"

template<typename T>
auto comparer(const T a, const T b)
{
	return a > b;
}

void sort_practice()
{
	print_title("sort");

	auto vec = std::vector{ 20, 43, 11, 78, 5, 96 };
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

	constexpr auto c = comparer<decltype(vec.at(0))>;
	std::sort(std::begin(vec), std::end(vec), c);
	for (const auto& it : vec)
	{
		std::cout << it << " ";
	}
	std::cout << std::endl;
}
