#include "pch.h"

#include "lambda.h"
#include "../Common/util.h"

#include <boost/array.hpp>
#include <boost/range/irange.hpp>

void multi_line_lambda()
{
	print_title("lambda_multiline_func");

	std::array<int, 10> arr{};
	std::generate(arr.begin(), arr.end(), [n = 0]() mutable { return n++; });
	std::for_each(arr.begin(), arr.end(), [](const int n)
	{
		std::cout << n << " is";

		if (n < 2)
		{
			if (n == 0)
			{
				std::cout << " not";
			}
		}
		else
		{
			for (auto i = 2; i < n; ++i)
			{
				if (n % i == 0)
				{
					std::cout << " not";
				}
			}
		}

		std::cout << " prime number" << std::endl;
	});

	for (const auto i : boost::irange(0, 10))
	{
		std::cout << i << " is";

		if (i < 2)
		{
			if (i == 0)
			{
				std::cout << " not";
			}
		}
		else
		{
			for (auto j = 2; j < i; ++j)
			{
				if (i % j == 0)
				{
					std::cout << " not";
				}
			}
		}

		std::cout << " prime number" << std::endl;
	}
}

void return_value_lambda()
{
	print_title("lambda_return_value");

	std::array<int, 10> arr{};
	std::iota(arr.begin(), arr.end(), 0);
	print_container(arr);

	std::vector<int> vec;
	vec.reserve(arr.size());
	std::transform(arr.begin(), arr.end(), std::back_inserter(vec),
	               [](auto n) { return static_cast<int>(std::pow(n, 2)); });
	print_container(vec);

	std::list<double> list;
	list.assign(arr.begin(), arr.end());
	print_container(list);

	std::transform(vec.begin(), vec.end(), list.begin(), [](auto n) -> double { return n / 2.0; });
	print_container(list);
}

void lambda_capture_by_value()
{
	print_title("lambda_capture_by_value");

	std::array<int, 10> arr{};
	std::iota(arr.begin(), arr.end(), 0);

	auto a = 2;
	auto b = 8;
	std::for_each(arr.begin(), arr.end(), [a, b](auto n)
	{
		if (n >= a && n <= b) std::cout << n << " ";
	});
	std::cout << std::endl;

	a = 3;
	b = 7;
	std::for_each(arr.begin(), arr.end(), [=](auto n)
	{
		if (n >= a && n <= b) std::cout << n << " ";
	});
	std::cout << std::endl;

	a = 1;
	b = 1;
	std::for_each(arr.begin(), arr.end(), [=](auto& n) mutable
	{
		const int old = n;
		n *= 2;
		a = b;
		b = old;
	});
	print_container(arr);
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
}

void lambda_capture_by_reference()
{
	print_title("lambda_capture_by_reference");

	std::array<int, 10> arr{};
	std::iota(arr.begin(), arr.end(), 0);

	auto a = 1;
	auto b = 1;
	std::for_each(arr.begin(), arr.end(), [&a, &b](auto& n)
	{
		const int old = n;
		n *= 2;
		a = b;
		b = old;
	});
	print_container(arr);
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
}

void lambda_initialization_capture()
{
	print_title("lambda_initialization_capture");
	auto a = 5;
	const auto lambda = [&x = a]() { x += 2; };

	std::cout << "old a = " << a << std::endl;
	lambda();
	std::cout << "new a = " << a << std::endl;
}

void lambda_expression_generic()
{
	print_title("lambda_expression_generic");

	const auto find_max = [](auto& x, auto& y)
	{
		return std::max(x, y);
	};

	const auto i1 = 5, i2 = 3;
	const auto f1 = 2.5f, f2 = 2.05f;
	std::cout << find_max(i1, i2) << std::endl;
	std::cout << find_max(f1, f2) << std::endl;
}

void lambda_practice()
{
	multi_line_lambda();
	return_value_lambda();
	lambda_capture_by_value();
	lambda_capture_by_reference();
	lambda_initialization_capture();
	lambda_expression_generic();
}
