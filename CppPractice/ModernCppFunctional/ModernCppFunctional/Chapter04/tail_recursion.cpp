#include "pch.h"
#include "tail_recursion.h"
#include "../Common/util.h"

void SimpleTailRecursion(const long long n)
{
	std::cout << n << std::endl;

#ifndef _DEBUG
	SimpleTailRecursion(n + 1);
#endif // _DEBUG
}

void TailRecursionPractice()
{
	PrintTitle("tail_recursion");
	SimpleTailRecursion(0);
}
