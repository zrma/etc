#include "pch.h"

#include "begin_end.h"
#include "util.h"

void BeginEndPractice()
{
	PrintTitle("[begin_end]");

	// 배열 선언
	std::array<int, 10> arr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	const auto size = sizeof(arr) / sizeof(arr[0]);
	static_assert(arr.size() == size);

	for(auto i = 0; i < size; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	// std::array는 직접 복사 및 대입 가능
	auto clone = arr;
	arr[5] = 0;

	// Compile Error!
	// arr[10] = 1;

	for(auto i = std::begin(arr); i != std::end(arr); ++i)
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
