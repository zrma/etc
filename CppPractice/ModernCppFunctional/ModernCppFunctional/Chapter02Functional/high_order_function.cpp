#include "pch.h"

#include "high_order_function.h"
#include "../Common/util.h"
#include <boost/range/irange.hpp>

using hyperbolic_func = std::function<double(double)>;

std::array<hyperbolic_func, 4> functions = {
	[](const double x) {
		return std::sinh(x);
	},
	[](const double x) {
		return std::cosh(x);
	},
	[](const double x) {
		return std::tanh(x);
	},
	[](const double x)
	{
		return std::pow(x, 2);
	}
};

std::array<hyperbolic_func, 4> inverse_functions = {
	[](const double x) {
		return std::asinh(x);
	},
	[](const double x) {
		return std::acosh(x);
	},
	[](const double x) {
		return std::atanh(x);
	},
	[](const double x)
	{
		return std::exp(std::log(x) / 2);
	}
};

template <typename A, typename B, typename C>
auto compose(std::function<C(B)> f, std::function<B(A)> g)
{
	return [f, g](A x)
	{
		return f(g(x));
	};
}

void high_order_function()
{
	print_title("high_order_function");

	std::vector<hyperbolic_func> composed_functions;
	std::array<double, 4> numbers;
	std::generate(numbers.begin(), numbers.end(), [n = 1]() mutable { return 0.2 * n++; });

	std::transform(
		inverse_functions.begin(),
		inverse_functions.end(),
		functions.begin(),
		std::back_inserter(composed_functions),
		compose<double, double, double>
	);

	for (const auto number : numbers)
	{
		for (const auto& function : composed_functions)
		{
			std::cout << "f(g(" << number << ")) = " << function(number) << std::endl;
		}
		std::cout << "--------------------" << std::endl;
	}
}

void map()
{
	print_title("high_order_function_map");

	std::array<int, 5> arr;
	std::iota(arr.begin(), arr.end(), 0);
	std::vector<int> vec;
	vec.resize(arr.size());

	std::transform(arr.begin(), arr.end(), vec.begin(), [](auto i) { return i * i; });
	std::cout << "before : ";
	print_container(arr);
	std::cout << "after  : ";
	print_container(vec);
}

auto filter_prime_numbers(std::vector<int> src)
{	
	std::vector<int> dest;
	std::copy_if(src.begin(), src.end(), std::back_inserter(dest), [](auto n)
	{
		if (n < 2)
		{
			return n != 0;
		}
		for (auto i : boost::irange(2, n))
		{
			if (n % i == 0)
			{
				return false;
			}
		}

		return true;
	});

	return std::move(dest);
}

auto filter_non_prime_numbers(std::vector<int> src)
{
	std::vector<int> dest;
	std::remove_copy_if(src.begin(), src.end(), std::back_inserter(dest), [](auto n)
	{
		if (n < 2)
		{
			return n != 0;
		}
		for (auto i : boost::irange(2, n))
		{
			if (n % i == 0)
			{
				return false;
			}
		}

		return true;
	});

	return std::move(dest);
}

void filter()
{
	print_title("high_order_function_filter");

	std::vector<int> vec{ 20 };
	std::iota(vec.begin(), vec.end(), 0);

	const auto prime_numbers = filter_prime_numbers(vec);
	const auto non_prime_numbers = filter_non_prime_numbers(vec);
	
	std::cout << "original number  : ";
	print_container(vec);
	std::cout << "the prime number : ";
	print_container(prime_numbers);
	std::cout << "non-prime number : ";
	print_container(non_prime_numbers);
}

void reduce()
{
	print_title("high_order_function_reduce");

	std::array<int, 5> arr;
	std::iota(arr.begin(), arr.end(), 0);

	const auto reduce_op = [](auto lhs, auto rhs)
	{
		std::cout << "lhs(" << lhs << ") + ";
		std::cout << "rhs(" << rhs << ") = ";
		std::cout << lhs + rhs << std::endl;

		return lhs + rhs;
	};
	std::cout << "foldLeft" << std::endl;
	const auto fold_left_result = std::accumulate(arr.begin(), arr.end(), 0, reduce_op);
	std::cout << "foldLeft result = " << fold_left_result;
	std::cout << std::endl;

	std::cout << "foldRight" << std::endl;
	const auto fold_right_result = std::accumulate(arr.rbegin(), arr.rend(), 0, reduce_op);
	std::cout << "foldRight result = " << fold_right_result;
	std::cout << std::endl;
}

void high_order_function_practice()
{
	high_order_function();
	map();
	filter();
	reduce();
}
