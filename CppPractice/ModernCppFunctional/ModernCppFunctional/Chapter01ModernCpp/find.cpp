#include "pch.h"

#include "find.h"
#include "../Common/util.h"

auto vehicle::has_two_wheel() const
{
	return this->get_num_of_wheel() == 2;
}

void find_practice()
{
	print_title("find");

	const vehicle car("car", 4);
	const vehicle bike("bike", 2);
	const vehicle bicycle("bicycle", 2);
	const vehicle bus("bus", 6);

	const auto vehicles = std::vector{ car, bike, bicycle, bus };

	std::cout << "vehicle full list" << std::endl;
	std::for_each(vehicles.begin(), vehicles.end(), [](const vehicle& vehicle)
	{
		std::cout << vehicle.get_type() << std::endl;
	});

	for (const auto& it : vehicles)
	{
		std::cout << it.get_type() << " : " << it.get_num_of_wheel() << std::endl;
	}

	const auto is_two_wheel = [](const auto &vehicle)
	{
		return vehicle.has_two_wheel();
	};

	std::cout << "two wheel only" << std::endl;
	auto&& tw = std::find_if(vehicles.begin(), vehicles.end(), is_two_wheel);
	while (tw != vehicles.end())
	{
		std::cout << tw->get_type() << std::endl;
		tw = std::find_if(++tw, vehicles.end(), is_two_wheel);
	}

	std::cout << "none two wheel only" << std::endl;
	auto&& ntw = std::find_if_not(std::begin(vehicles), std::end(vehicles), is_two_wheel);
	while (ntw != std::end(vehicles))
	{
		std::cout << ntw->get_type() << std::endl;
		ntw = std::find_if_not(++ntw, std::end(vehicles), is_two_wheel);
	}
}
