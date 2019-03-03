#include "pch.h"

#include "convert_to_immutable.h"
#include "../Common/util.h"

void print_immutable_employee(const immutable_employee& me)
{
	std::cout << "Content of MutableEmployee instance" << std::endl;
	std::cout << "Id : " << me.id() << std::endl;
	std::cout << "Name : " << me.first_name();
	std::cout << " " << me.last_name() << std::endl;
	std::cout << "Salary : " << me.salary() << std::endl;
}

void convert_to_immutable()
{
	print_title("convert_to_immutable");

	const auto first = "Frankie";
	const auto last = "Gamble";
	const auto d = 1500.0;

	const auto& me = immutable_employee(0, first, last, d);
	print_immutable_employee(me);

	[[maybe_unused]] const auto& me2 = me.set_id(1);
	[[maybe_unused]] const auto& me3 = me.set_first_name("Alexis");
	[[maybe_unused]] const auto& me4 = me.set_last_name("Andrew");
	const auto& me5 = me.set_salary(2100.0);
	print_immutable_employee(me5);
}
