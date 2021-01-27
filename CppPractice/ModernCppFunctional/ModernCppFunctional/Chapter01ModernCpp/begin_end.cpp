#include "pch.h"

#include "begin_end.h"
#include "../Common/util.h"

void begin_end_practice()
{
	print_title("[begin_end]");

	// 배열 선언
	auto arr = std::array{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	const auto size = sizeof arr / sizeof arr[0];
	static_assert(arr.size() == size);

	for (auto i = 0; static_cast<decltype(size)>(i) < size; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	// std::array는 직접 복사 및 대입 가능
	auto clone = arr;
	arr[5] = 0;

	// Error!
	// arr[10] = 1;

	std::for_each(arr.begin(), arr.end(), [](const auto& i)
	{
		std::cout << i << " ";
	});
	std::cout << std::endl;

	for (auto&& i = std::begin(arr); i != std::end(arr); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	for (const auto& i : clone)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}
