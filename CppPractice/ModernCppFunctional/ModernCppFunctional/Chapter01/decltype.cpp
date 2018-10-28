#include "pch.h"

#include "decltype.h"
#include "../Common/util.h"

int Func1();
const int& Func2();

struct X { double D;  };

void DeclTypePractice()
{
	PrintTitle("DeclType");

	std::cout << "result of add : " << Add(3, 5) << std::endl;

	const auto i = 0;
	const X* x = new X();

	decltype(Func1) F1;
	decltype(Func2) F2;
	// decl type(i) i1 = i;
	const auto i1 = i;
	
	const decltype(x->D) d1 = 0;
	// decl type((x->d)) d2 = d1;
	const auto& d2 = d1;

	std::cout << typeid(F1).name() << std::endl;
	std::cout << typeid(F2).name() << std::endl;
	_CRT_UNUSED(i1);
	_CRT_UNUSED(d2);

	delete x;
}

int Func1()
{
	return 0;
}

const int & Func2()
{
	return std::forward<int&&>(0);
}
