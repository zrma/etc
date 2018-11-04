#include "pch.h"

#include "convert_to_immutable.h"
#include "../Common/util.h"

void PrintImmutableEmployee(const ImmutableEmployee& me)
{
	std::cout << "Content of MutableEmployee instance" << std::endl;
	std::cout << "Id : " << me.Id() << std::endl;
	std::cout << "Name : " << me.FirstName();
	std::cout << " " << me.LastName() << std::endl;
	std::cout << "Salary : " << me.Salary() << std::endl;
}

void ConvertToImmutable()
{
	PrintTitle("convert_to_immutable");

	const auto first = "Frankie";
	const auto last = "Gamble";
	const auto d = 1500.0;

	const auto& me = ImmutableEmployee(0, first, last, d);
	PrintImmutableEmployee(me);

	[[maybe_unused]] const auto& me2 = me.SetId(1);
	[[maybe_unused]] const auto& me3 = me.SetFirstName("Alexis");
	[[maybe_unused]] const auto& me4 = me.SetLastName("Andrew");
	const auto& me5 = me.SetSalary(2100.0);
	PrintImmutableEmployee(me5);
}
