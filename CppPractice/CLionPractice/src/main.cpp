#include "cph.h"

#include "TypeTraits.h"

class Test
{
};

int main()
{
	const auto a = 0;
	const auto b = "test";
	const auto c = new Test();
	const auto d = std::make_shared<Test>();

	std::cout << is_shared_ptr_t( a ) << std::endl;
	std::cout << is_shared_ptr_t( b ) << std::endl;
	std::cout << is_shared_ptr_t( c ) << std::endl;
	std::cout << is_shared_ptr_t( d ) << std::endl;
}