#include "pch.h"

#include "mutable.h"
#include "../Common/util.h"

void MutableEmployee::SetId(const int id)
{
	this->m_Id = id;
}

void MutableEmployee::SetFirstName(const std::string& firstName)
{
	this->m_FirstName = firstName;
}

void MutableEmployee::SetLastName(const std::string& lastName)
{
	this->m_LastName = lastName;
}

void MutableEmployee::SetSalary(const double& salary)
{
	this->m_Salary = salary;
}

void PrintMutableEmployee(MutableEmployee& me)
{
	std::cout << "Content of MutableEmployee instance" << std::endl;
	std::cout << "Id : " << me.Id() << std::endl;
	std::cout << "Name : " << me.FirstName();
	std::cout << " " << me.LastName() << std::endl;
	std::cout << "Salary : " << me.Salary() << std::endl;
}

void MutablePractice()
{
	PrintTitle("mutable");

	const auto first = "Frankie";
	const auto last = "Gamble";
	const auto d = 1500.0;

	auto me = MutableEmployee(0, first, last, d);
	PrintMutableEmployee(me);

	me.SetId(1);
	me.SetFirstName("Alexis");
	me.SetLastName("Andrews");
	me.SetSalary(2100.0);
	PrintMutableEmployee(me);
}
