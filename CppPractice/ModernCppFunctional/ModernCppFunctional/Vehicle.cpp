#include "pch.h"

#include "Vehicle.h"
#include "util.h"

auto Vehicle::HasTwoWheel() const
{
	return this->GetNumOfWheel() == 2;
}

void FindPractice()
{
	PrintTitle("find");

	const Vehicle car("car", 4);
	const Vehicle bike("bike", 2);
	const Vehicle bicycle("bicycle", 2);
	const Vehicle bus("bus", 6);

	const std::vector<Vehicle> vehicles = { car, bike, bicycle, bus };

	std::cout << "vehicle full list" << std::endl;
	std::for_each(vehicles.begin(), vehicles.end(), [](const Vehicle& vehicle)
	{
		std::cout << vehicle.GetType() << std::endl;
	});

	for (const auto& it : vehicles)
	{
		std::cout << it.GetType() << " : " << it.GetNumOfWheel() << std::endl;
	}

	const auto isTwoWheel = [](const Vehicle &vehicle)
	{
		return vehicle.HasTwoWheel();
	};

	std::cout << "two wheel only" << std::endl;
	auto&& tw = std::find_if(vehicles.begin(), vehicles.end(), isTwoWheel);
	while (tw != vehicles.end())
	{
		std::cout << tw->GetType() << std::endl;
		tw = std::find_if(++tw, vehicles.end(), isTwoWheel);
	}

	std::cout << "none two wheel only" << std::endl;
	auto&& ntw = std::find_if_not(std::begin(vehicles), std::end(vehicles), isTwoWheel);
	while (ntw != std::end(vehicles))
	{
		std::cout << ntw->GetType() << std::endl;
		ntw = std::find_if_not(++ntw, std::end(vehicles), isTwoWheel);
	}
}
