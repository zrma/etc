#include "pch.h"
#include "Permute.h"
#include "../Common/util.h"

void Permute(const std::string& chosen, const std::string& remain)
{
	if( remain == "")
	{
		std::cout << chosen << std::endl;
	}
	else
	{
		for (const auto& it : remain)
		{
			const auto pos = remain.find(it);
			Permute(chosen + it, remain.substr(0, pos) + remain.substr(pos + 1));
		}
	}
}

void Permutation(const std::string& s)
{
	Permute("", s);
}

void PermutationPractice()
{
	PrintTitle("permutation");

	std::string str;
	std::cout << "Permutation of a string" << std::endl;
	std::cout << ">> Enter a string : ";
	std::getline(std::cin, str);
	std::getline(std::cin, str);

	std::cout << std::endl << "The possibility permutation of " << str << std::endl;
	Permutation(str);
}
