#include "pch.h"

#include "high_order_function.h"
#include "../Common/util.h"
#include <boost/range/irange.hpp>

using HyperbolicFunc = std::function<double(double)>;

std::array<HyperbolicFunc, 4> Functions = {
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

std::array<HyperbolicFunc, 4> InverseFunctions = {
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
auto Compose(std::function<C(B)> f, std::function<B(A)> g)
{
	return [f, g](A x)
	{
		return f(g(x));
	};
}

void HighOrderFunction()
{
	PrintTitle("high_order_function");

	std::vector<HyperbolicFunc> composedFunctions;
	std::array<double, 4> numbers;
	std::generate(numbers.begin(), numbers.end(), [n = 1]() mutable { return 0.2 * n++; });

	std::transform(
		InverseFunctions.begin(),
		InverseFunctions.end(),
		Functions.begin(),
		std::back_inserter(composedFunctions),
		Compose<double, double, double>
	);

	for (const auto number : numbers)
	{
		for (const auto& function : composedFunctions)
		{
			std::cout << "f(g(" << number << ")) = " << function(number) << std::endl;
		}
		std::cout << "--------------------" << std::endl;
	}
}

void Map()
{
	PrintTitle("high_order_function_map");

	std::array<int, 5> arr;
	std::iota(arr.begin(), arr.end(), 0);
	std::vector<int> vec;
	vec.resize(arr.size());

	std::transform(arr.begin(), arr.end(), vec.begin(), [](auto i) { return i * i; });
	std::cout << "before : ";
	PrintContainer(arr);
	std::cout << "after  : ";
	PrintContainer(vec);
}

auto FilterPrimeNumbers(std::vector<int> src)
{	
	std::vector<int> dest;
	std::copy_if(src.begin(), src.end(), std::back_inserter(dest), [](auto n)
	{
		if (n < 2)
		{
			return n != 0;
		}
		else
		{
			for (auto i : boost::irange(2, n))
			{
				if (n % i == 0)
				{
					return false;
				}
			}
		}

		return true;
	});

	return std::move(dest);
}

auto FilterNonPrimeNumbers(std::vector<int> src)
{
	std::vector<int> dest;
	std::remove_copy_if(src.begin(), src.end(), std::back_inserter(dest), [](auto n)
	{
		if (n < 2)
		{
			return n != 0;
		}
		else
		{
			for (auto i : boost::irange(2, n))
			{
				if (n % i == 0)
				{
					return false;
				}
			}
		}

		return true;
	});

	return std::move(dest);
}

void Filter()
{
	PrintTitle("high_order_function_filter");

	std::vector<int> vec(20);
	std::iota(vec.begin(), vec.end(), 0);

	const auto primeNumbers = FilterPrimeNumbers(vec);
	const auto nonPrimeNumbers = FilterNonPrimeNumbers(vec);
	
	std::cout << "original number  : ";
	PrintContainer(vec);
	std::cout << "the prime number : ";
	PrintContainer(primeNumbers);
	std::cout << "non-prime number : ";
	PrintContainer(nonPrimeNumbers);
}

void Reduce()
{
	PrintTitle("high_order_function_reduce");

	std::array<int, 5> arr;
	std::iota(arr.begin(), arr.end(), 0);

	const auto reduceOp = [](auto lhs, auto rhs)
	{
		std::cout << "lhs(" << lhs << ") + ";
		std::cout << "rhs(" << rhs << ") = ";
		std::cout << lhs + rhs << std::endl;

		return lhs + rhs;
	};
	std::cout << "foldLeft" << std::endl;
	const auto foldLeftResult = std::accumulate(arr.begin(), arr.end(), 0, reduceOp);
	std::cout << "foldLeft result = " << foldLeftResult;
	std::cout << std::endl;

	std::cout << "foldRight" << std::endl;
	const auto foldRightResult = std::accumulate(arr.rbegin(), arr.rend(), 0, reduceOp);
	std::cout << "foldRight result = " << foldRightResult;
	std::cout << std::endl;
}

void HighOrderFunctionPractice()
{
	HighOrderFunction();
	Map();
	Filter();
	Reduce();
}
