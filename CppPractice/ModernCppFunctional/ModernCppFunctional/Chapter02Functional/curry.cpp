#include "pch.h"

#include "curry.h"
#include "../Common/util.h"
#include <boost/range/irange.hpp>


void curry_practice() {
    print_title("curry");

    [[maybe_unused]] const auto _ = area_of_rect<int>;
    [[maybe_unused]] const auto __ = volume_of_rect<double>;

    const auto width5 = curry(area_of_rect<int>, 5);
    std::cout << "Curried with specific width = 5" << std::endl;

    for (const auto height : boost::irange(0, 5)) {
        std::cout << "Width5(" << height << ") = " << width5(height);
        std::cout << std::endl;
    }

    const auto width5_height4 = curry(volume_of_rect<double>, 5, 4);
    std::cout << "Curried with specific width = 5, height = 4" << std::endl;

    for (const auto depth : boost::irange(0, 5)) {
        std::cout << "Width5Height4(" << depth << ") = " << width5_height4(depth);
        std::cout << std::endl;
    }
}
