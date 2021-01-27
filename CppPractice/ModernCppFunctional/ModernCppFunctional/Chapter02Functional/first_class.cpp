#include "pch.h"

#include "first_class.h"
#include "../Common/util.h"

using func_type = std::function<int(int, int)>;

auto addition(const int x, const int y)
{
	return x + y;
}

auto subtraction(const int x, const int y)
{
	return x - y;
}

auto multiplication(const int x, const int y)
{
	return x * y;
}

auto division(const int x, const int y)
{
	return x / y;
}

void passing_func(const func_type& fn, const int x, const int y)
{
	std::cout << "Result = " << fn(x, y) << std::endl;
}

void first_class()
{
	print_title("fist_class");
	std::array<func_type, 4> functions = {addition, subtraction, multiplication, division};

	while (true)
	{
		auto i = 0, a = 0, b = 0;
		func_type func;

		std::cout << "Select mode : " << std::endl;
		std::cout << "  1. Addition" << std::endl;
		std::cout << "  2. Subtraction" << std::endl;
		std::cout << "  3. Multiplication" << std::endl;
		std::cout << "  4. Division" << std::endl;
		std::cout << "  5. Exit" << std::endl;
		std::cout << "Choice : ";
		std::cin >> i;

		if (i == 5)
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
		while (std::cin.fail())
		{
			// std::cin 에러 플래그를 초기화 해 std::cin 을 사용 가능한 상태로 변경
			std::cin.clear();

			// 마지막 입력 무시
			std::cin.ignore(INT8_MAX, '\n');
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
			std::cin.ignore(INT8_MAX, '\n');
			std::cout << "You can only enter numbers." << std::endl;
			std::cout << "Enter a number for variable b : ";
			std::cin >> b;
		}

		passing_func(functions.at(static_cast<unsigned long>(i - 1)), a, b);
	}
}
