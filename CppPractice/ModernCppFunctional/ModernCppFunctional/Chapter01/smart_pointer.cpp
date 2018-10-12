#include "pch.h"

#include "smart_pointer.h"
#include "../Common/util.h"

struct BodyMass
{
	int Id = 0;
	float Weight = 0;

	BodyMass(const int id, const float weight): Id(id), Weight(weight)
	{
		std::cout << "BodyMass is constructed!" << std::endl;
		std::cout << "Id = " << Id << std::endl;
		std::cout << "Weight = " << Weight << std::endl;
	}
	BodyMass(const BodyMass& other) : Id(other.Id), Weight(other.Weight)
	{
		// use default 경고 우회
		Id = other.Id;

		std::cout << "BodyMass is copy constructed!" << std::endl;
		std::cout << "Id = " << Id << std::endl;
		std::cout << "Weight = " << Weight << std::endl;
	}
	BodyMass& operator= (const BodyMass&) = default;
	BodyMass(const BodyMass&& other) noexcept: Id(std::move(other.Id)), Weight(std::move(other.Weight))
	{
		std::cout << "BodyMass is move constructed!" << std::endl;
	}
	BodyMass& operator= (BodyMass&& other) noexcept
	{
		if( this != &other)
		{
			Id = std::move(other.Id);
			Weight = std::move(other.Weight);
		}

		std::cout << "BodyMass is move assigned!" << std::endl;
		return *this;
	}

	~BodyMass()
	{
		Id = 0;
		Weight = 0;
		std::cout << "BodyMass is destructed!" << std::endl;
	}
};

auto GetBodyMass()
{
	return std::make_unique<BodyMass>(1, 165.3f);
}

auto UpdateBodyMass(std::unique_ptr<BodyMass> bodyMass)
{
	bodyMass->Weight += 1.0f;
	return bodyMass;
}

void UniquePtr()
{
	PrintTitle("unique_ptr");

	{
		const auto weight = std::make_unique<BodyMass>(1, 165.3f);
		// compile error!
		// auto weight2 = weight;
		const auto weightClone = *weight;
		const auto weight2 = std::make_shared<BodyMass>(weightClone);
		std::cout << "in scope" << std::endl;
	}

	{
		auto weight = GetBodyMass();
		std::cout << "Current weight = " << weight->Weight << std::endl;
		weight = UpdateBodyMass(std::move(weight));
		std::cout << "Updated weight = " << weight->Weight << std::endl;
	}
}

void SharedPtr()
{
	const auto sp1 = std::make_shared<int>();
	if(sp1)
	{
		std::cout << "sp1 is initialized" << std::endl;
	}
	else
	{
		std::cout << "sp1 is not initialized" << std::endl;
	}
	std::cout << "sp1 pointing counter = " << sp1.use_count() << std::endl;

	auto sp2 = sp1;
	std::cout << "sp1 pointing counter = " << sp1.use_count() << std::endl;

	sp2.reset();
	std::cout << "sp1 pointing counter = " << sp1.use_count() << std::endl;
}

void WeakPtr()
{
	auto sp = std::make_shared<int>(12345);
	auto wp = std::weak_ptr<int>{ sp };
	if(wp.expired())
	{
		std::cout << "wp is expired" << std::endl;
	}
	else
	{
		std::cout << "wp is not expired" << std::endl;
	}

	std::cout << "sp pointing counter = " << sp.use_count() << std::endl;
	if ( const auto locked = wp.lock() )
	{
		std::cout << "wp is locked. Value = " << *locked << std::endl;
	}
	else
	{
		std::cout << "wp is unlocked" << std::endl;
		wp.reset();
	}

	sp = nullptr;
	if (wp.expired())
	{
		std::cout << "wp is expired" << std::endl;
	}
	else
	{
		std::cout << "wp is not expired" << std::endl;
	}

	std::cout << "sp pointing counter = " << sp.use_count() << std::endl;
	if (const auto locked = wp.lock())
	{
		std::cout << "wp is locked. Value = " << *locked << std::endl;
	}
	else
	{
		std::cout << "wp is unlocked" << std::endl;
		wp.reset();
	}
}

void SmartPointerPractice()
{
	UniquePtr();
	SharedPtr();
	WeakPtr();
}
