#pragma once

inline decltype(auto) AutoPractice()
{
	std::cout << "[auto.cpp]" << std::endl;

	// 여러 개의 auto 타입 변수 생성
	constexpr auto a = 1;
	constexpr auto b = 1.0;
	constexpr auto c = a + b;
	const auto d = { b, c };
	for (auto&& it : d) { std::cout << it << std::endl; }

	// 변수의 실제 타입 출력
	std::cout << "type of a : " << typeid(a).name() << std::endl;
	std::cout << "type of b : " << typeid(b).name() << std::endl;
	std::cout << "type of c : " << typeid(c).name() << std::endl;
	std::cout << "type of d : " << typeid(d).name() << std::endl;

	return c;
}