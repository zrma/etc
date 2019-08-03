#pragma once
#include <utility>

class vehicle {
public:
    vehicle(std::string type, const int wheel) : vehicle_type_(std::move(type)), total_of_wheel_i_(wheel) {}

    vehicle() = default;

    ~vehicle() = default;

    vehicle(const vehicle &) = default;

    vehicle &operator=(const vehicle &) = default;

    vehicle(const vehicle &&other) noexcept {
        this->vehicle_type_ = other.vehicle_type_;
        this->total_of_wheel_i_ = other.total_of_wheel_i_;
    }

    vehicle &operator=(vehicle &&other) noexcept {
        if (this != &other) {
            vehicle_type_ = other.vehicle_type_;
            total_of_wheel_i_ = other.total_of_wheel_i_;
        }

        return *this;
    }

    [[nodiscard]] auto has_two_wheel() const;

    [[nodiscard]] auto get_type() const { return vehicle_type_; }

    [[nodiscard]] auto get_num_of_wheel() const { return total_of_wheel_i_; }

private:
    std::string vehicle_type_{};
    int total_of_wheel_i_ = 0;
};

void find_practice();