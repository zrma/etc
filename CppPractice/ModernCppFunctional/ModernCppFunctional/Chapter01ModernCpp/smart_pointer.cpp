#include "pch.h"

#include "smart_pointer.h"
#include "../Common/util.h"

struct body_mass
{
	int id = 0;
	float weight = 0;

	body_mass(const int id, const float weight) : id(id), weight(weight)
	{
		std::cout << "BodyMass is constructed!" << std::endl;
		std::cout << "Id = " << id << std::endl;
		std::cout << "Weight = " << weight << std::endl;
	}

	body_mass(const body_mass& other) : id(other.id), weight(other.weight)
	{
		std::cout << "BodyMass is copy constructed!" << std::endl;
		std::cout << "Id = " << id << std::endl;
		std::cout << "Weight = " << weight << std::endl;
	}

	body_mass& operator=(const body_mass&) = default;

	body_mass(body_mass&& other) noexcept: id(other.id), weight(other.weight)
	{
		std::cout << "BodyMass is move constructed!" << std::endl;
	}

	body_mass& operator=(body_mass&& other) noexcept
	{
		if (this != &other)
		{
			id = other.id;
			weight = other.weight;
		}

		std::cout << "BodyMass is move assigned!" << std::endl;
		return *this;
	}

	~body_mass()
	{
		id = 0;
		weight = 0;
		std::cout << "BodyMass is destructed!" << std::endl;
	}
};

auto get_body_mass()
{
	return std::make_unique<body_mass>(1, 165.3f);
}

auto update_body_mass(std::unique_ptr<body_mass> body_mass)
{
	body_mass->weight += 1.0f;
	return body_mass;
}

void unique_ptr()
{
	print_title("unique_ptr");

	{
		const auto weight = std::make_unique<body_mass>(1, 165.3f);
		// compile error!
		// auto weight2 = weight;
		const auto weight_clone = *weight;
		const auto weight2 = std::make_shared<body_mass>(weight_clone);
		std::cout << "in scope" << std::endl;
	}

	{
		auto weight = std::make_unique<body_mass>(1, 165.3f);
		const auto weight2 = std::move(weight);
		const auto weight_clone = *weight2;
		const auto weight3 = std::make_shared<body_mass>(weight_clone);
		std::cout << "in scope" << std::endl;
	}

	{
		auto weight = get_body_mass();
		std::cout << "Current weight = " << weight->weight << std::endl;
		weight = update_body_mass(std::move(weight));
		std::cout << "Updated weight = " << weight->weight << std::endl;
	}
}

void shared_ptr()
{
	const auto sp1 = std::make_shared<int>();
	if (sp1)
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

void weak_ptr()
{
	auto sp = std::make_shared<int>(12345);
	auto wp = std::weak_ptr{sp};
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

	sp.reset();
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

void smart_pointer_practice()
{
	unique_ptr();
	shared_ptr();
	weak_ptr();
}
