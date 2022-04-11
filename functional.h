#pragma once
#ifndef _FUNCTIONAL_H_
#define _FUNCTIONAL_H_

namespace TinySTL
{
template<class _Ty>
struct greater
{
	bool operator()(const _Ty& lhs, const _Ty& rhs) {
		return lhs > rhs;
	}
};

template<class _Ty>
struct less
{
	bool operator()(const _Ty& lhs, const _Ty& rhs) {
		return lhs < rhs;
	}
};

template<class _Ty>
struct equal_to {
	bool operator()(const _Ty& lhs, const _Ty& rhs) {
		return lhs == rhs;
	}
};




}

#endif