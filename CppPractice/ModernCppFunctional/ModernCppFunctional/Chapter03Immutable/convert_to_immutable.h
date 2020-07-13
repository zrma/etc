#pragma once
#include <utility>

class immutable_employee
{
public:
	immutable_employee(
		const int& id,
		std::string first_name,
		std::string last_name,
		const double& salary
	) : id_(id), first_name_(std::move(first_name)), last_name_(std::move(last_name)), salary_(salary)
	{
	}

	immutable_employee() = default;

	[[nodiscard]] immutable_employee set_id(const int& id) const
	{
		return immutable_employee(id, first_name_, last_name_, salary_);
	}

	[[nodiscard]] immutable_employee set_first_name(const std::string& first_name) const
	{
		return immutable_employee(id_, first_name, last_name_, salary_);
	}

	[[nodiscard]] immutable_employee set_last_name(const std::string& last_name) const
	{
		return immutable_employee(id_, first_name_, last_name, salary_);
	}

	[[nodiscard]] immutable_employee set_salary(const double& salary) const
	{
		return immutable_employee(id_, first_name_, last_name_, salary);
	}

	[[nodiscard]] const auto& id() const { return id_; }

	[[nodiscard]] const auto& first_name() const { return first_name_; }

	[[nodiscard]] const auto& last_name() const { return last_name_; }

	[[nodiscard]] const auto& salary() const { return salary_; }

private:
	const int id_ = 0;
	const std::string first_name_{};
	const std::string last_name_{};
	const double salary_ = 0;
};

void convert_to_immutable();
