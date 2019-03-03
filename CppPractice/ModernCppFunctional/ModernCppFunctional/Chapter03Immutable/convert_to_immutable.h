#pragma once

class ImmutableEmployee
{
public:
	ImmutableEmployee(
		const int& id,
		const std::string& firstName,
		const std::string& lastName,
		const double& salary
	) : m_Id(id), m_FirstName(firstName), m_LastName(lastName), m_Salary(salary) {}
	ImmutableEmployee() = default;

	ImmutableEmployee SetId(const int& id) const
	{
		return std::move(ImmutableEmployee(id, m_FirstName, m_LastName, m_Salary));
	}
	ImmutableEmployee SetFirstName(const std::string& firstName) const
	{
		return std::move(ImmutableEmployee(m_Id, firstName, m_LastName, m_Salary));
	}
	ImmutableEmployee SetLastName(const std::string& lastName) const
	{
		return std::move(ImmutableEmployee(m_Id, m_FirstName, lastName, m_Salary));
	}
	ImmutableEmployee SetSalary(const double& salary) const
	{
		return std::move(ImmutableEmployee(m_Id, m_FirstName, m_LastName, salary));
	}

	const auto& Id() const { return m_Id; }
	const auto& FirstName() const { return m_FirstName; }
	const auto& LastName() const { return m_LastName; }
	const auto& Salary() const { return m_Salary; }
private:
	const int m_Id = 0;
	const std::string m_FirstName{};
	const std::string m_LastName{};
	const double m_Salary = 0;
};

void ConvertToImmutable();