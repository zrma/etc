#include "pch.h"

#include "curry.h"
#include "util.h"
#include <boost/range/irange.hpp>


void CurryPractice()
{
	PrintTitle("curry");

	const auto width5 = Curry(AreaOfRect<int>, 5);
	std::cout << "Curried with specific width = 5" << std::endl;

	for( auto height : boost::irange(5))
	{
		std::cout << "Width5(" << height << ") = " << width5(height);
		std::cout << std::endl;
	}

	const auto width5Height4 = Curry(VolumeOfRect<int>, 5, 4);
	std::cout << "Curried with specific width = 5, height = 4" << std::endl;

	for (auto depth : boost::irange(5))
	{
		std::cout << "Width5Height4(" << depth << ") = " << width5Height4(depth);
		std::cout << std::endl;
	}
}
