#include "pch.h"

#include "strict.h"
#include "../Common/util.h"

auto outer_formula(const int x, const int yz)
{
	std::cout << "calculate " << x << " + ";
	std::cout << "inner_formula(" << yz << ")";
	std::cout << std::endl;

	return x + yz;
}

int inner_formula(const int y, const int z)
{
	std::cout << "calculate " << y << " * ";
	std::cout << z << std::endl;

	return y * z;
}

void strict()
{
	print_title("strict");
	constexpr auto x = 4;
	constexpr auto y = 3;
	constexpr auto z = 2;

	std::cout << "calculate " << x << " + ";
	std::cout << "(" << y << " * " << z << ")";
	std::cout << std::endl;
	const auto result = outer_formula(x, inner_formula(y, z));

	std::cout << x << " + ";
	std::cout << "(" << y << " * " << z << ")";
	std::cout << " = " << result << std::endl;
}
