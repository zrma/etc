#pragma once

void PrintTitle(const std::string&& title);

template <typename T>
void PrintContainer(T t)
{
	std::for_each(t.begin(), t.end(), [](auto n) { std::cout << n << " "; });
	std::cout << std::endl;
}