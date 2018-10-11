#include "pch.h"

#include "first_class.h"
#include "../Common/util.h"

using FuncType = std::function<int(int, int)>;

auto Addition(const int x, const int y)
{
	return x + y;
}

auto Subtraction(const int x, const int y)
{
	return x - y;
}

auto Multiplication(const int x, const int y)
{
	return x * y;
}

auto Division(const int x, const int y)
{
	return x / y;
}

void PassingFunc(const FuncType fn, const int x, const int y)
{
	std::cout << "Result = " << fn(x, y) << std::endl;
}

void FirstClass()
{
	PrintTitle("fist_class");
	std::array<FuncType, 4> functions = {Addition, Subtraction, Multiplication, Division};

	while(true)
	{
		auto i = 0, a = 0, b = 0;
		FuncType func;

		std::cout << "Select mode : " << std::endl;
		std::cout << "  1. Addition" << std::endl;
		std::cout << "  2. Subtraction" << std::endl;
		std::cout << "  3. Multiplication" << std::endl;
		std::cout << "  4. Division" << std::endl;
		std::cout << "  5. Exit" << std::endl;
		std::cout << "Choice : ";
		std::cin >> i;

		if ( i == 5 )
		{
			break;
		}
		if (i < 1 || i > 4)
		{
			std::cout << "Please select available mode!" << std::endl;
			continue;
		}

		std::cout << " a : ";
		std::cin >> a;

		// a값 유효성 확인
		while(std::cin.fail())
		{
			// std::cin 에러 플래그를 초기화 해 std::cin 을 사용 가능한 상태로 변경
			std::cin.clear();

			// 마지막 입력 무시
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "You can only enter numbers." << std::endl;
			std::cout << "Enter a number for variable a : ";
			std::cin >> a;
		}

		std::cout << " b : ";
		std::cin >> b;

		// a값 유효성 확인
		while (std::cin.fail())
		{
			// std::cin 에러 플래그를 초기화 해 std::cin 을 사용 가능한 상태로 변경
			std::cin.clear();

			// 마지막 입력 무시
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "You can only enter numbers." << std::endl;
			std::cout << "Enter a number for variable b : ";
			std::cin >> b;
		}

		PassingFunc(functions.at(i - 1), a, b);
	}
}
