#include "pch.h"

#include "TypeTraits.h"
#include <boost/type_index.hpp>

class Test
{
};

template<class T>
void type_name(T)
{
	std::cout << "\n Short name: " << boost::typeindex::type_id<T>().raw_name();
	std::cout << "\n Readable name: " << boost::typeindex::type_id<T>().pretty_name();
}

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

	type_name( a );
	type_name( b );
	type_name( c );
	type_name( d );
}