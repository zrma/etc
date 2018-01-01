#include <list>
#include <iostream>

#include <boost/asio.hpp>

int main()
{
	std::list<int> l;
	l.assign( 10, 0 );

	for ( const auto &i : l )
	{
		std::cout << i << std::endl;
	}

	boost::asio::io_service service;
	service.run_one();
}