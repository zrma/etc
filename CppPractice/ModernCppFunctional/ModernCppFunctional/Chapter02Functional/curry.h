#pragma once

template<typename Func, typename... Args>
auto curry(Func func, Args... args)
{
	return [=](auto... others)
	{
		return func(args..., others...);
	};
}

template<typename T>
decltype(auto) area_of_rect(const T width, const T height)
{
	return width * height;
}

template<typename T>
decltype(auto) volume_of_rect(const T width, const T height, const T depth)
{
	return width * height * depth;
}

void curry_practice();