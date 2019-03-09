#include "pch.h"
#include "exponential.h"
#include <boost/range/irange.hpp>
#include "../Common/util.h"

auto power(const int base, const int exp)
{
	auto result = 1;

	for([[maybe_unused]] auto _ : boost::irange(0, exp))
	{
		result *= base;
	}

	return result;
}

auto power_recursion(const int base, const int exp)
{
	if (exp == 0)
	{
		return 1;
	}
	return base * power_recursion(base, exp - 1);
}

void exponential_iteration_practice()
{
	print_title("exponential_iteration");

	for( const auto i : boost::irange(0, 6))
	{
		std::cout << "power (2, " << i << ") = " << power(2, i) << std::endl;
	}
}

void exponential_recursion_practice()
{
	print_title("exponential_recursion");

	for (const auto i : boost::irange(0, 6))
	{
		std::cout << "power (2, " << i << ") = " << power_recursion(2, i) << std::endl;
	}
}

void exponential_practice()
{
	exponential_iteration_practice();
}
