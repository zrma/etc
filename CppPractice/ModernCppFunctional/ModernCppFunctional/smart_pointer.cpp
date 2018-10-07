#include "pch.h"

#include "smart_pointer.h"
#include "util.h"

struct BodyMass
{
	int Id;
	float Weight;

	BodyMass(const int id, const float weight): Id(id), Weight(weight)
	{
		std::cout << "BodyMass is constructed!" << std::endl;
		std::cout << "Id = " << id << std::endl;
		std::cout << "Weight = " << weight << std::endl;
	}
	BodyMass(const BodyMass&) = default;
	BodyMass& operator= (const BodyMass&) = default;
	BodyMass(const BodyMass&& other) noexcept
	{
		Id = other.Id;
		Weight = other.Weight;
	}
	BodyMass& operator= (BodyMass&& other) noexcept
	{
		if( this != &other)
		{
			Id = other.Id;
			Weight = other.Weight;
		}

		return *this;
	}

	~BodyMass()
	{
		Id = 0;
		Weight = 0;
		std::cout << "BodyMass is destructed!" << std::endl;
	}
};

void UniquePtr()
{
	PrintTitle("unique_ptr");

	{
		auto weight = std::make_unique<BodyMass>(1, 165.3f);
		std::cout << "in scope" << std::endl;
	}
}

void SmartPointerPractice()
{
	UniquePtr();
}
