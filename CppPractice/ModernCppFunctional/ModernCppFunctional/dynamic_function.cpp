#include "pch.h"

#include "dynamic_function.h"
#include "util.h"

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
	
void DynamicFunction()
{
	PrintTitle("dynamic_function");

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
