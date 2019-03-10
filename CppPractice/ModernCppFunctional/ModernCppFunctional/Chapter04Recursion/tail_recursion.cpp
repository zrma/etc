#include "pch.h"
#include "tail_recursion.h"
#include "../Common/util.h"

void simple_tail_recursion(const long long n) {
    std::cout << n << std::endl;

#ifndef _DEBUG
    if (n < 100000) {
        simple_tail_recursion(n + 1);
    }
#endif // _DEBUG
}

void tail_recursion_practice() {
    print_title("tail_recursion");
    simple_tail_recursion(0);
}
