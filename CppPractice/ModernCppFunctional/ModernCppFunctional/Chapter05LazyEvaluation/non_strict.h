#pragma once

auto outer_formula_non_strict(int x, int y, int z, const std::function<int(int, int)>& yz_func);

void non_strict();