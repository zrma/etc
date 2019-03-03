#include "pch.h"
#include "fibonacci.h"

#include "../Common/util.h"

#include <boost/range/irange.hpp>

auto FibonacciForLoop(const int n)
{
	if (n <= 0)
	{
		return 0;
	}

	auto[prev, cur] = std::tuple(0, 1);

	for ([[maybe_unused]] auto _ : boost::irange(n - 1))
	{
		const auto next = prev + cur;
		prev = cur;
		cur = next;
	}

	return cur;
}

auto FibonacciRecursion(const int n)
{
	if (n <= 1)
	{
		return n;
	}

	return FibonacciRecursion(n - 1) + FibonacciRecursion(n - 2);
}

void FibonacciForLoopPractice()
{
	PrintTitle("fibonacci_iteration");

	for (const auto i : boost::irange(10))
	{
		std::cout << FibonacciForLoop(i) << " ";
	}
	std::cout << std::endl;
}

void FibonacciRecursionPractice()
{
	PrintTitle("fibonacci_recursion");

	for (const auto i : boost::irange(10))
	{
		std::cout << FibonacciRecursion(i) << " ";
	}
	std::cout << std::endl;
}

void FibonacciPractice()
{
	FibonacciForLoopPractice();
	FibonacciRecursionPractice();
}
