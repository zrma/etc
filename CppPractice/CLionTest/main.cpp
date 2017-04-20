#include <list>
#include <iostream>

int main()
{
	std::list<int> l;
	l.assign( 100, 0 );

	for( const auto& i : l )
	{
		std::cout << i << std::endl;
	}
}