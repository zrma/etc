#pragma once

class vehicle
{
public:
	vehicle(const std::string &type, const int wheel) : vehicle_type_(type), total_of_wheel_i_(wheel) {}
	vehicle() = default;
	~vehicle() = default;
	vehicle(const vehicle&) = default;
	vehicle& operator=(const vehicle&) = default;
	vehicle(const vehicle&& other) noexcept
	{
		this->vehicle_type_ = other.vehicle_type_;
		this->total_of_wheel_i_ = other.total_of_wheel_i_;
	}
	vehicle& operator=(vehicle&& other) noexcept
	{
		if( this != &other)
		{
			vehicle_type_ = other.vehicle_type_;
			total_of_wheel_i_ = other.total_of_wheel_i_;
		}

		return *this;
	}

	auto has_two_wheel() const;
	auto get_type() const { return vehicle_type_; }
	auto get_num_of_wheel() const { return total_of_wheel_i_; }
private:
	std::string vehicle_type_{};
	int total_of_wheel_i_ = 0;
};

void find_practice();