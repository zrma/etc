#pragma once

template<typename Func, typename... Args>
auto Curry(Func func, Args... args)
{
	return [=](auto... others)
	{
		return func(args..., others...);
	};
}

template<typename T>
decltype(auto) AreaOfRect(const T width, const T height)
{
	return width * height;
}

template<typename T>
decltype(auto) VolumeOfRect(const T width, const T height, const T depth)
{
	return width * height * depth;
}

void CurryPractice();