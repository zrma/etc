#pragma once
#include <utility>

class vehicle
{
public:
	vehicle(std::string type, const int wheel) : vehicle_type_(std::move(type)), total_of_wheel_i_(wheel)
	{
	}

	[[nodiscard]] auto has_two_wheel() const;

	[[nodiscard]] auto get_type() const { return vehicle_type_; }

	[[nodiscard]] auto get_num_of_wheel() const { return total_of_wheel_i_; }

private:
	std::string vehicle_type_{};
	int total_of_wheel_i_ = 0;
};

void find_practice();
