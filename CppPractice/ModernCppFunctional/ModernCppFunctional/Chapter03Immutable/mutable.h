#pragma once
#include <utility>

class mutable_employee
{
public:
	mutable_employee(
		const int id,
		std::string first_name,
		std::string last_name,
		const double salary
	) : id_(id), first_name_(std::move(first_name)), last_name_(std::move(last_name)), salary_(salary)
	{
	}

	mutable_employee() = default;

	void set_id(int id);

	void set_first_name(std::string first_name);

	void set_last_name(std::string last_name);

	void set_salary(double salary);

	[[nodiscard]] auto id() const { return id_; }

	[[nodiscard]] auto first_name() const { return first_name_; }

	[[nodiscard]] auto last_name() const { return last_name_; }

	[[nodiscard]] auto salary() const { return salary_; }

private:
	int id_ = 0;
	std::string first_name_{};
	std::string last_name_{};
	double salary_ = 0;
};

void mutable_practice();
