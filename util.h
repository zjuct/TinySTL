#pragma once
#ifndef _MYSTL_UTIL_H_
#define _MYSTL_UTIL_H_

#include<cstddef>
namespace MySTL
{
//move
template<typename _Ty>
typename std::remove_reference<_Ty>::type&& move(_Ty&& arg) {
	return static_cast<typename std::remove_reference<_Ty>::type&&>(arg);
}

template<class _Ty1,class _Ty2>
struct pair {
	typedef _Ty1 first_type;
	typedef _Ty2 second_type;

	first_type first;
	second_type second;

	pair(first_type _Val1, second_type _Val2):first(_Val1),second(_Val2){}

};
}

#endif