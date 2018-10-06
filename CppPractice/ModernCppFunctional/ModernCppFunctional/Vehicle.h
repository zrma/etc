#pragma once

class Vehicle
{
public:
	Vehicle(const std::string &type, const int wheel) : m_VehicleType(type), m_TotalOfWheeI(wheel) {}
	Vehicle() = default;
	~Vehicle() = default;
	Vehicle(const Vehicle&) = default;
	Vehicle& operator=(const Vehicle&) = default;
	Vehicle(const Vehicle&& other) noexcept
	{
		this->m_VehicleType = other.m_VehicleType;
		this->m_TotalOfWheeI = other.m_TotalOfWheeI;
	}
	Vehicle& operator=(Vehicle&& other) noexcept
	{
		if( this != &other)
		{
			m_VehicleType = other.m_VehicleType;
			m_TotalOfWheeI = other.m_TotalOfWheeI;
		}

		return *this;
	}

	auto HasTwoWheel() const;
	auto GetType() const { return m_VehicleType; }
	auto GetNumOfWheel() const { return m_TotalOfWheeI; }
private:
	std::string m_VehicleType{};
	int m_TotalOfWheeI = 0;
};

void FindPractice();