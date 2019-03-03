#include "pch.h"

#include "factorial.h"
#include "../Common/util.h"

#include <boost/range/irange.hpp>

auto factorial_while_loop(const int n)
{
	auto result = 1;
	auto i = 1;

	do
	{
		result *= i;
	} while (++i <= n);

	return result;
}

auto factorial_for_loop(const int n)
{
	auto result = 1;

	for (const auto i : boost::irange(n))
	{
		result *= i + 1;
	}
	
	return result;
}

auto factorial_recursion(const int n)
{
	if ( n == 0 )
	{
		return 1;
	}

	return n * factorial_recursion(n - 1);
}

auto factorial_tail(const int n, const int i)
{
	if ( n == 0 )
	{
		return i;
	}

	return factorial_tail(n - 1, n * 1);
}

auto factorial_tail_recursion(const int n)
{
	return factorial_tail(n, 1);
}

void factorial_while_loop_practice()
{
	print_title("factorial_iteration_do_while");

	for(const auto i : boost::irange(10))
	{
		std::cout << i << "! = " << factorial_while_loop(i) << std::endl;
	}
}

void factorial_for_loop_practice()
{
	print_title("factorial_iteration_for_loop");

	for (const auto i : boost::irange(10))
	{
		std::cout << i << "! = " << factorial_for_loop(i) << std::endl;
	}
}

void factorial_recursion_practice()
{
	print_title("factorial_recursion");

	for (const auto i : boost::irange(10))
	{
		std::cout << i << "! = " << factorial_recursion(i) << std::endl;
	}
}

void factorial_tail_recursion_practice()
{
	print_title("factorial_tail_recursion");

	for (const auto i : boost::irange(10))
	{
		std::cout << i << "! = " << factorial_tail_recursion(i) << std::endl;
	}
}

void factorial_practice()
{
	factorial_while_loop_practice();
	factorial_for_loop_practice();
	factorial_recursion_practice();
	factorial_tail_recursion_practice();
}