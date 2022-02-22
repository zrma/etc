﻿#include "pch.h"

#include "mutable.h"

#include <utility>
#include "../Common/util.h"

void mutable_employee::set_id(const int id)
{
	this->id_ = id;
}

void mutable_employee::set_first_name(std::string first_name)
{
	this->first_name_ = std::move(first_name);
}

void mutable_employee::set_last_name(std::string last_name)
{
	this->last_name_ = std::move(last_name);
}

void mutable_employee::set_salary(const double salary)
{
	this->salary_ = salary;
}

void print_mutable_employee(const mutable_employee& me)
{
	std::cout << "Content of MutableEmployee instance" << std::endl;
	std::cout << "Id : " << me.id() << std::endl;
	std::cout << "Name : " << me.first_name();
	std::cout << " " << me.last_name() << std::endl;
	std::cout << "Salary : " << me.salary() << std::endl;
}

void mutable_practice()
{
	print_title("mutable");

	const auto* const first = "Frankie";
	const auto* const last = "Gamble";
	constexpr auto d = 1500.0;

	auto me = mutable_employee(0, first, last, d);
	print_mutable_employee(me);

	me.set_id(1);
	me.set_first_name("Alexis");
	me.set_last_name("Andrews");
	me.set_salary(2100.0);
	print_mutable_employee(me);
}
