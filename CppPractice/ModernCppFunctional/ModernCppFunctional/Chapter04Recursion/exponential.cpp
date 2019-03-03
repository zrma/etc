#include "pch.h"
#include "exponential.h"
#include <boost/range/irange.hpp>
#include "../Common/util.h"

auto Power(const int base, const int exp)
{
	auto result = 1;

	for([[maybe_unused]] auto _ : boost::irange(exp))
	{
		result *= base;
	}

	return result;
}

auto PowerRecursion(const int base, const int exp)
{
	if (exp == 0)
	{
		return 1;
	}
	return base * PowerRecursion(base, exp - 1);
}

void ExponentialIterationPractice()
{
	PrintTitle("exponential_iteration");

	for( const auto i : boost::irange(6))
	{
		std::cout << "power (2, " << i << ") = " << Power(2, i) << std::endl;
	}
}

void ExponentialRecursionPractice()
{
	PrintTitle("exponential_recursion");

	for (const auto i : boost::irange(6))
	{
		std::cout << "power (2, " << i << ") = " << PowerRecursion(2, i) << std::endl;
	}
}

void ExponentialPractice()
{
	ExponentialIterationPractice();
}
