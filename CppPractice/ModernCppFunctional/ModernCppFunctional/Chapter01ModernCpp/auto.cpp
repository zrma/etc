#include "pch.h"

#include "auto.h"
#include "../Common/util.h"

#include <boost/type_index.hpp>

constexpr auto get_value()
{
	constexpr auto a = 10;
	return a;
}

template<class T>
auto type_name(T)
{
	return boost::typeindex::type_id<T>().pretty_name();
}

void auto_practice()
{
	print_title("auto.cpp");

	// 여러 개의 auto 타입 변수 생성
	constexpr auto a = get_value();
	constexpr auto b = 1.0;
	constexpr auto c = a + b;
	const auto d = { b, c };
	for (auto&& it : d) { std::cout << it << std::endl; }

	// 변수의 실제 타입 출력
	std::cout << "type of a : " << typeid(a).name() << " / " << type_name(a) << std::endl;
	std::cout << "type of b : " << typeid(b).name() << " / " << type_name(b) << std::endl;
	std::cout << "type of c : " << typeid(c).name() << " / " << type_name(c) << std::endl;
	std::cout << "type of d : " << typeid(d).name() << " / " << type_name(d) << std::endl;
}
