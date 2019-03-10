#pragma once

template<typename I, typename J>
auto add(I i, J j) -> decltype(i + j) {
    return i + j;
}

void decl_type_practice();