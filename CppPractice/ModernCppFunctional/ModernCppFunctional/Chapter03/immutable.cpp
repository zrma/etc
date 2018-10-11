#include "pch.h"

#include "immutable.h"
#include "../Common/util.h"

template<typename T, typename U>
class IToString
{
public:
	const U Value;

	explicit IToString(U value) :Value(value) {}
};

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const IToString<T, U>& object)
{
	os << object.Value;
	return os;
}

class Age :public IToString<Age, int>
{
public:
	explicit Age(const int initAge = 20) : IToString<Age, int>(initAge) {}
};

class Integer :public IToString<Integer, int>
{
public:
	explicit Integer(const int n) : IToString<Integer, int>(n) {}
};

class Function
{
public:
	const int X, Y;

	Function(const int x, const int y): X(x), Y(y)
	{		
	}

	auto Addition() const
	{
		return Integer(X + Y);
	}

	auto Subtraction() const
	{
		return Integer(X - Y);
	}

	auto Multiplication() const
	{
		return Integer(X * Y);
	}

	auto Division() const
	{
		return Integer(X / Y);
	}
};

void ConstPractice()
{
	PrintTitle("const");

	const Age ageNow, ageLater(8);
	std::cout << "My current Value is " << ageNow << std::endl;
	std::cout << "My age in eight years later is " << ageLater << std::endl;

	// compile error!
	// ageNow.Value = 10;
}

void FirstClassPureImmutablePractice()
{
	PrintTitle("first_class_pure_immutable");

	const auto a = 100;
	const auto b = 10;

	std::cout << "Initial value" << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;

	Function func(a, b);
	
	const auto callableAdd = std::mem_fn(&Function::Addition);
	const auto callableSub = std::mem_fn(&Function::Subtraction);
	const auto callableMul = std::mem_fn(&Function::Multiplication);
	const auto callableDiv = std::mem_fn(&Function::Division);

	const auto resultAdd = callableAdd(func);
	const auto resultSub = callableSub(func);
	const auto resultMul = callableMul(func);
	const auto resultDiv = callableDiv(func);

	std::cout << "The result" << std::endl;
	std::cout << "add = " << resultAdd << std::endl;
	std::cout << "sub = " << resultSub << std::endl;
	std::cout << "mul = " << resultMul << std::endl;
	std::cout << "div = " << resultDiv << std::endl;
}

void ImmutablePractice()
{
	ConstPractice();
	FirstClassPureImmutablePractice();
}
