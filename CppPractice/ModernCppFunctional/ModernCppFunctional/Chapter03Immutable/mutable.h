#pragma once

class MutableEmployee
{
public:
	MutableEmployee(
		const int id,
		const std::string& firstName,
		const std::string& lastName,
		const double& salary
	) : m_Id(id), m_FirstName(firstName), m_LastName(lastName), m_Salary(salary) {}
	MutableEmployee() = default;

	void SetId(int id);
	void SetFirstName(const std::string& firstName);
	void SetLastName(const std::string& lastName);
	void SetSalary(const double& salary);

	auto Id() const { return m_Id; }
	auto FirstName() const { return m_FirstName; }
	auto LastName() const { return m_LastName; }
	auto Salary() const { return m_Salary; }
private:
	int m_Id = 0;
	std::string m_FirstName{};
	std::string m_LastName{};
	double m_Salary = 0;
};

void MutablePractice();