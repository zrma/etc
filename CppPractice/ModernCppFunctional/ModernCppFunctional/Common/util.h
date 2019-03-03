#pragma once

void print_title(const std::string&& title);

template <typename T>
void print_container(T t)
{
	std::for_each(t.begin(), t.end(), [](auto n) { std::cout << n << " "; });
	std::cout << std::endl;
}