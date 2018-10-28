#include "pch.h"

#include "factorial.h"
#include "../Common/util.h"

#include <boost/range/irange.hpp>

auto FactorialWhileLoop(const int n)
{
	auto result = 1;
	auto i = 1;

	do
	{
		result *= i;
	} while (++i <= n);

	return result;
}

auto FactorialForLoop(const int n)
{
	auto result = 1;

	for (const auto i : boost::irange(n))
	{
		result *= (i + 1);
	}
	
	return result;
}

auto FactorialRecursion(const int n)
{
	if ( n == 0 )
	{
		return 1;
	}

	return n * FactorialRecursion(n - 1);
}

void FactorialWhileLoopPractice()
{
	PrintTitle("factorial_iteration_do_while");

	for(const auto i : boost::irange(10))
	{
		std::cout << i << "! = " << FactorialWhileLoop(i) << std::endl;
	}
}

void FactorialForLoopPractice()
{
	PrintTitle("factorial_iteration_for_loop");

	for (const auto i : boost::irange(10))
	{
		std::cout << i << "! = " << FactorialWhileLoop(i) << std::endl;
	}
}

void FactorialRecursionPractice()
{
	PrintTitle("factorial_recursion");

	for (const auto i : boost::irange(10))
	{
		std::cout << i << "! = " << FactorialWhileLoop(i) << std::endl;
	}
}

void FactorialPractice()
{
	FactorialWhileLoopPractice();
	FactorialForLoopPractice();
	FactorialRecursionPractice();
}