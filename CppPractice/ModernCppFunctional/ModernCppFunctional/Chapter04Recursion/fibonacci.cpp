#include "pch.h"
#include "fibonacci.h"

#include "../Common/util.h"

#include <boost/range/irange.hpp>

auto fibonacci_for_loop(const int n)
{
	if (n <= 0)
	{
		return 0;
	}

	auto[prev, cur] = std::tuple(0, 1);

	for ([[maybe_unused]] auto _ : boost::irange(0, n - 1))
	{
		const auto next = prev + cur;
		prev = cur;
		cur = next;
	}

	return cur;
}

auto fibonacci_recursion(const int n)
{
	if (n <= 1)
	{
		return n;
	}

	return fibonacci_recursion(n - 1) + fibonacci_recursion(n - 2);
}

void fibonacci_for_loop_practice()
{
	print_title("fibonacci_iteration");

	for (const auto i : boost::irange(0, 10))
	{
		std::cout << fibonacci_for_loop(i) << " ";
	}
	std::cout << std::endl;
}

void fibonacci_recursion_practice()
{
	print_title("fibonacci_recursion");

	for (const auto i : boost::irange(0, 10))
	{
		std::cout << fibonacci_recursion(i) << " ";
	}
	std::cout << std::endl;
}

void fibonacci_practice()
{
	fibonacci_for_loop_practice();
	fibonacci_recursion_practice();
}
