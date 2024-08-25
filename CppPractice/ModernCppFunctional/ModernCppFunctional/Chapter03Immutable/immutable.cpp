#include "pch.h"

#include "immutable.h"
#include "../Common/util.h"
#include "mutable.h"

template <typename T, typename U>
class to_string
{
public:
	const U value;

	explicit to_string(U value) : value(value)
	{
	}
};

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const to_string<T, U>& object)
{
	os << object.value;
	return os;
}

class age : public to_string<age, int>
{
public:
	explicit age(const int init_age = 20) : to_string<age, int>(init_age)
	{
	}
};

class integer : public to_string<integer, int>
{
public:
	explicit integer(const int n) : to_string<integer, int>(n)
	{
	}
};

class function
{
public:
	const int x, y;

	function(const int x, const int y) : x(x), y(y)
	{
	}

	[[nodiscard]] auto addition() const
	{
		return integer(x + y);
	}

	[[nodiscard]] auto subtraction() const
	{
		return integer(x - y);
	}

	[[nodiscard]] auto multiplication() const
	{
		return integer(x * y);
	}

	[[nodiscard]] auto division() const
	{
		return integer(x / y);
	}
};

void const_practice()
{
	print_title("const");

	const auto age_now = age();
	const auto age_later = age(8);
	std::cout << "My current Value is " << age_now << std::endl;
	std::cout << "My age in eight years later is " << age_later << std::endl;

	// compile error!
	// ageNow.Value = 10;
}

void first_class_pure_immutable_practice()
{
	print_title("first_class_pure_immutable");

	constexpr auto a = 100;
	constexpr auto b = 10;

	std::cout << "Initial value" << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;

	function func(a, b);

	const auto callable_add = std::mem_fn(&function::addition);
	const auto callable_sub = std::mem_fn(&function::subtraction);
	const auto callable_mul = std::mem_fn(&function::multiplication);
	const auto callable_div = std::mem_fn(&function::division);

	const auto result_add = callable_add(func);
	const auto result_sub = callable_sub(func);
	const auto result_mul = callable_mul(func);
	const auto result_div = callable_div(func);

	std::cout << "The result" << std::endl;
	std::cout << "add = " << result_add << std::endl;
	std::cout << "sub = " << result_sub << std::endl;
	std::cout << "mul = " << result_mul << std::endl;
	std::cout << "div = " << result_div << std::endl;
}

void immutable_practice()
{
	const_practice();
	first_class_pure_immutable_practice();
	mutable_practice();
}
