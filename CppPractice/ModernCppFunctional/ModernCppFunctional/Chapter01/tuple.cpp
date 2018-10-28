﻿#include "pch.h"

#include "tuple.h"
#include "../Common/util.h"

void Tuples()
{
	PrintTitle("tuples");

	const auto t1 = std::tuple(1, "Robert", true);
	const auto t2 = std::make_tuple(2, "Anna", false);

	std::cout << "t1 elements : ";
	std::cout << std::get<0>(t1) << " ";
	std::cout << std::get<1>(t1) << " ";
	std::cout << std::get<2>(t1) << " ";
	std::cout << std::endl;

	std::cout << "t2 elements : ";
	std::cout << std::get<0>(t2) << " ";
	std::cout << std::get<1>(t2) << " ";
	std::cout << std::get<2>(t2) << " ";
	std::cout << std::endl;
}

void Tie()
{
	PrintTitle("tuple_tie");

	const std::tuple<int, std::string, bool> t1(1, "Robert", true);
	const auto t2 = std::make_tuple(2, "Anna", false);

	auto i = 0;
	std::string s = "";
	auto b = false;

	std::tie(i, s, b) = t1;
	std::cout << "tie(s, i, b) = t1 : ";
	std::cout << s << " ";
	std::cout << i << " ";
	std::cout << b << " ";
	std::cout << std::endl;

	std::tie(std::ignore, s, std::ignore) = t2;
	std::cout << "tie(ignore, i, ignore) = t2 : ";
	std::cout << s << " ";
	std::cout << i << " ";
	std::cout << b << " ";
	std::cout << std::endl;
}

void AutoUnpack()
{
	PrintTitle("auto_unpack");

	auto[i, s, b] = std::tuple(1, "Robert", true);
	std::cout << "auto [i, s, b] = std::tuple() : ";
	std::cout << i << " ";
	std::cout << s << " ";
	std::cout << b << " ";
	std::cout << std::endl;
}

auto GetData(const int dataId)
{
	switch (dataId)
	{
	case 1:
		return std::make_tuple(0, "Chloe", false);
	case 2:
		return std::make_tuple(1, "Bryan", true);
	default:
		return std::make_tuple(2, "Zoe", false);
	}
}

void TupleValueReturn()
{
	PrintTitle("tuple_value_return");

	auto people = GetData(1);
	std::cout << "name = " << std::get<1>(people) << std::endl;
	
	std::string name = "";
	std::tie(std::ignore, name, std::ignore) = people;
	std::cout << "name = " << name << std::endl;
}

void TuplePractice()
{
	Tuples();
	Tie();
	AutoUnpack();
	TupleValueReturn();
}
