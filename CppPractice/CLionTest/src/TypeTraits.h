//
// Created by zrma on 2018. 2. 16..
//

#ifndef CLIONTEST_TYPETRAITS_H
#define CLIONTEST_TYPETRAITS_H

#include <type_traits>
#include <memory>

#include <boost/mpl/bool.hpp>

template<typename T>
struct is_shared_ptr : boost::mpl::false_
{
};

template<typename T>
struct is_shared_ptr<std::shared_ptr<T> > : boost::mpl::true_
{
};

template<typename T>
constexpr bool is_shared_ptr_t(T)
{
	return is_shared_ptr<T>::value;
}

#endif //CLIONTEST_TYPETRAITS_H
