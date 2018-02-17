#include "stdafx.h"

#include "TypeTraits.h"

class Test
{
};

int main()
{
	auto a = 0;
	auto b = "test";
	auto c = new Test();
	auto d = std::make_shared<Test>();

	std::cout << is_shared_ptr_t( a ) << std::endl;
	std::cout << is_shared_ptr_t( b ) << std::endl;
	std::cout << is_shared_ptr_t( c ) << std::endl;
	std::cout << is_shared_ptr_t( d ) << std::endl;
}