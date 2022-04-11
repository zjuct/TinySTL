#pragma once
#ifndef _TYPE_TRAITS_H_
#define _TYPE_TRAITS_H_

namespace TinySTL
{

template<bool _Test, class _Ty = void>
struct enable_if {

};

//enable_if的特化版本
template<class _Ty>
struct enable_if<true, _Ty> {
	using type = _Ty;
};

template<class T, T v>
struct m_integral_constant {
	static constexpr T value = v;
};

template<bool b>
using m_bool_constant = m_integral_constant<bool, b>;

typedef m_bool_constant<true> m_true_type;
typedef m_bool_constant<false> m_false_type;



}

#endif
