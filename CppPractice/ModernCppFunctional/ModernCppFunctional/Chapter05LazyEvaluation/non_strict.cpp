#include "pch.h"

#include <functional>
#include "strict.h"
#include "non_strict.h"

#include "../Common/util.h"

auto outer_formula_non_strict(
	const int x,
	const int y,
	const int z,
	const std::function<int(int, int)>& yz_func
)
{
	std::cout << "calculate " << x << " + ";
	std::cout << "inner_formula(" << y << ", ";
	std::cout << z << ")" << std::endl;

	return x + yz_func(y, z);
}

void non_strict()
{
	print_title("non-strict");
	constexpr auto x = 4;
	constexpr auto y = 3;
	constexpr auto z = 2;

	std::cout << "calculate " << x << " + ";
	std::cout << "(" << y << " * " << z << ")";
	std::cout << std::endl;
	const auto result = outer_formula_non_strict(x, y, z, inner_formula);

	std::cout << x << " + ";
	std::cout << "(" << y << " * " << z << ")";
	std::cout << " = " << result << std::endl;
}
