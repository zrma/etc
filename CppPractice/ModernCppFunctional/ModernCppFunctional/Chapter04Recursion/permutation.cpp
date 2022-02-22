#include "pch.h"

#include <boost/range/adaptor/indexed.hpp>

#include "permutation.h"
#include "../Common/util.h"


void permute(const std::string& chosen, const std::string& remain)
{
	if (remain.empty())
	{
		std::cout << chosen << std::endl;
	}
	else
	{
		for (const auto&& it : remain | boost::adaptors::indexed(0))
		{
			const auto pos = it.index();
			permute(chosen + it.value(), remain.substr(0, pos) + remain.substr(pos + 1));
		}
	}
}

void permutation(const std::string& s)
{
	permute("", s);
}

void permutation_practice()
{
	print_title("permutation");

	std::string str;
	std::cout << "Permutation of a string" << std::endl;
	std::cout << ">> Enter a string : ";
	std::getline(std::cin, str);
	std::getline(std::cin, str);

	std::cout << std::endl << "The possibility permutation of " << str << std::endl;
	permutation(str);
}
