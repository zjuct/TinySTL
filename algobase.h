#pragma once
#ifndef _MYSTL_ALGOBASE_H_
#define _MYSTL_ALGOBASE_H_

#include"iterator.h"
#include"util.h"
#include<algorithm>
namespace TinySTL
{
//************************************************
//max:取二者中的最大值，相等时返回前者
template<typename _Ty>
const _Ty& max(const _Ty& _lhs, const _Ty& _rhs) {
	return _lhs >= _rhs ? _lhs : _rhs;
}
//max重载版本，接受谓词
template<typename _Ty,typename _Pred>
const _Ty& max(const _Ty& _lhs, const _Ty& _rhs, _Pred _pred) {
	return _pred(_lhs, _rhs) ? _lhs : _rhs;
}
//************************************************
//min:取二者中的最大值，相等时返回前者
template<typename _Ty>
const _Ty& min(const _Ty& _lhs, const _Ty& _rhs) {
	return _lhs <= _rhs ? _lhs : _rhs;
}

//min重载版本，接受谓词
template<typename _Ty, typename _Pred>
const _Ty& min(const _Ty& _lhs, const _Ty& _rhs, _Pred _pred) {
	return _pred(_lhs, _rhs) ? _lhs : _rhs;
}
//************************************************
//iter_swap:将两个迭代器所指对象对调
template<typename _Iter1,typename _Iter2>
void iter_swap(_Iter1 _lhs, _Iter2 _rhs) {
	auto tmp = *_lhs;
	*_lhs = *_rhs;
	*_rhs = tmp;
}

//************************************************
//copy:[first, last)区间内的元素拷贝到 [result, result + (last - first))内
//input_iterator版本
template<typename _InputIterator,typename _OutputIterator>
_OutputIterator unchecked_copy_cat(_InputIterator _First, 
	_InputIterator _Last, _OutputIterator _Result, input_iterator_tag) {
	for (;_First != _Last;_First++) {
		*_Result++ = *_First;
	}
	return _Result;
}
 
//random_access_iterator版本
template<typename _RandomAccessIterator,typename _OutputIterator>
_OutputIterator unchecked_copy_cat(_RandomAccessIterator _First,
	_RandomAccessIterator _Last, _OutputIterator _Result, random_access_iterator_tag) {
	for (auto n = _Last - _First;n > 0;n--) {
		*_Result++ = *_First++;
	}
	return _Result;
}

//copy的统一接口
template<typename _InputIterator, typename _OutputIterator>
_OutputIterator copy(_InputIterator _First,
	_InputIterator _Last, _OutputIterator _Result) {
	return unchecked_copy_cat(_First, _Last, _Result, iterator_catagory(_First));
}

//************************************************
//copy_backward:将 [first, last)区间内的元素拷贝到 [result - (last - first), result)内
//提供bidirectional_iteraotr和random_access_iterator两个版本
template<typename _BidirectionalIterator1,typename _BidirectionalIterator2>
_BidirectionalIterator2 unchecked_copy_backward_cat(_BidirectionalIterator1 _First,
	_BidirectionalIterator1 _Last, _BidirectionalIterator2 _Result, bidirectional_iterator_tag) {
	while (_Last != _First) {
		*--_Result = *--_Last;
	}
	return _Result;
}

template<typename _RandomAccessIterator,typename _BidirectionalIterator>
_BidirectionalIterator unchecked_copy_backward_cat(_RandomAccessIterator _First,
	_RandomAccessIterator _Last, _BidirectionalIterator _Result, random_access_iterator_tag) {
	for (auto n = _Last - _First;n > 0;n--) {
		*--_Result = *--_Last;
	}
	return _Result;
}

template<typename _BidirectionalIterator1, typename _BidirectionalIterator2>
_BidirectionalIterator2 unchecked_copy_backward(_BidirectionalIterator1 _First,
	_BidirectionalIterator1 _Last, _BidirectionalIterator2 _Result) {
	return unchecked_copy_backward_cat(_First, _Last, _Result, iterator_catagory(_First));
}

template<typename _BidirectionalIterator1, typename _BidirectionalIterator2>
_BidirectionalIterator2 copy_backward(_BidirectionalIterator1 _First,
	_BidirectionalIterator1 _Last, _BidirectionalIterator2 _Result) {
	return unchecked_copy_backward(_First, _Last, _Result, iterator_catagory(_First));
}

//************************************************
//copy_if:把[first, last)内满足一元操作 unary_pred 的元素拷贝到以 result 为起始的位置上
template<typename _InputIterator,typename _OutputIterator,typename _UnaryPred>
_OutputIterator unchecked_copy_if_cat(_InputIterator _First, 
	_InputIterator _Last, _OutputIterator _Result, _UnaryPred _Pred, input_iterator_tag) {
	while (_First != _Last) {
		if (_Pred(*_First)) {
			*_Result++ = *_First++;
		}
	}
	return _Result;
}

template<typename _RandomAccessIterator, typename _OutputIterator, typename _UnaryPred>
_OutputIterator unchecked_copy_if_cat(_RandomAccessIterator _First,
	_RandomAccessIterator _Last, _OutputIterator _Result, _UnaryPred _Pred) {
	for (auto n = _Last - _First;n > 0;n--) {
		if (_Pred(*_First)) {
			*_Result++ = *_First++;
		}
	}
	return _Result;
}

template<typename _InputIterator, typename _OutputIterator, typename _UnaryPred>
_OutputIterator unchecked_copy_if(_InputIterator _First,
	_InputIterator _Last, _OutputIterator _Result, _UnaryPred _Pred) {
	return unchecked_copy_if_cat(_First, _Last, _Result, _Pred, iterator_catagory(_First));
}

template<typename _InputIterator, typename _OutputIterator, typename _UnaryPred>
_OutputIterator copy_if(_InputIterator _First,
	_InputIterator _Last, _OutputIterator _Result, _UnaryPred _Pred) {
	return unchecked_copy_if(_First, _Last, _Result, _Pred);
}

//************************************************
//copy_n:把 [first, first + n)区间上的元素拷贝到 [result, result + n)上
//返回一个 pair 分别指向拷贝结束的尾部
template<typename _InputIterator,typename _Size,typename _OutputIterator>
std::pair<_InputIterator, _OutputIterator> unchecked_copy_n_cat(_InputIterator _First,
	_Size _Count, _OutputIterator _Result, input_iterator_tag) {
	for (;_Count > 0;_Count--) {
		*_Result++ = *_First++;
	}
	return std::pair<_InputIterator, _OutputIterator>(_First, _Result);
}

template<typename _RandomAccessIterator, typename _Size, typename _OutputIterator>
std::pair<_RandomAccessIterator, _OutputIterator> unchecked_copy_n_cat(_RandomAccessIterator _First,
	_Size _Count, _OutputIterator _Result, random_access_iterator_tag) {
	_RandomAccessIterator _Last = _First + _Count;
	_Result = copy(_First, _Last, _Result);
	return std::pair<_RandomAccessIterator, _OutputIterator>(_Last, _Result);
}

template<typename _InputIterator, typename _Size, typename _OutputIterator>
std::pair<_InputIterator, _OutputIterator> copy_n(_InputIterator _First,
	_Size _Count, _OutputIterator _Result, input_iterator_tag) {
	return unchecked_copy_n_cat(_First, _Count, _Result, iterator_catagory(_First));
}

//************************************************
//move:把 [first, last)区间内的元素移动到 [result, result + (last - first))内
template<typename _InputIterator, typename _OutputIterator>
_OutputIterator unchecked_move_cat(_InputIterator _First, 
	_InputIterator _Last, _OutputIterator _Result, input_iterator_tag) {
	while (_First != _Last) {
		*_Result++ = MySTL::move(*_First++);
	}
	return _Result;
}

template<typename _RandomAccessIterator, typename _OutputIterator>
_OutputIterator unchecked_move_cat(_RandomAccessIterator _First,
	_RandomAccessIterator _Last, _OutputIterator _Result, random_access_iterator_tag) {
	for (auto n = _Last - _First;n > 0;n--) {
		*_Result++ = MySTL::move(*_First++);
	}
	return _Result;
}

template<typename _InputIterator, typename _OutputIterator>
_OutputIterator move(_InputIterator _First,
	_InputIterator _Last, _OutputIterator _Result) {
	return unchecked_move_cat(_First, _Last, _Result, iterator_catagory(_First));
}
//************************************************
//move_backward:将 [first, last)区间内的元素移动到 [result - (last - first), result)内
template<typename _BidirectionalIterator1, typename _BidirectionalIterator2>
_BidirectionalIterator2 unchecked_move_backward_cat(_BidirectionalIterator1 _First,
	_BidirectionalIterator1 _Last, _BidirectionalIterator2 _Result, bidirectional_iterator_tag) {
	while (_Last != _First) {
		*--_Result = *--_Last;
	}
	return _Result;
}

template<typename _RandomAccessIterator, typename _BidirectionalIterator>
_BidirectionalIterator unchecked_move_backward_cat(_RandomAccessIterator _First,
	_RandomAccessIterator _Last, _BidirectionalIterator _Result, random_access_iterator_tag) {
	for (auto n = _Last - _First;n > 0;n--) {
		*--_Result = *--_Last;
	}
	return _Result;
}

template<typename _BidirectionalIterator1, typename _BidirectionalIterator2>
_BidirectionalIterator2 move_backward(_BidirectionalIterator1 _First,
	_BidirectionalIterator1 _Last, _BidirectionalIterator2 _Result) {
	return unchecked_move_backward_cat(_First, _Last, _Result, iterator_catagory(_First));
}
//************************************************
//equal:比较第一序列在 [first, last)区间上的元素值是否和第二序列相等
template<typename _InputIterator1, typename _InputIterator2>
bool equal(_InputIterator1 _First1, 
	_InputIterator1 _Last1, _InputIterator2 _First2) {
	while (_First1 != _Last1) {
		if (*_First1++ != *_First2++) {
			return false;
		}
	}
	return true;
}
//重载版本使用函数对象 comp 代替比较操作
template<typename _InputIterator1, typename _InputIterator2, typename _Pred>
bool equal(_InputIterator1 _First1,
	_InputIterator1 _Last1, _InputIterator2 _First2, _Pred _Comp) { 
	while (_First1 != _Last1) {
		if (!_Comp(*_First1++, *_First2++)) {
			return false;
		}
	}
	return true;
}

//***********************************************
//fill_n:从 first 位置开始填充 n 个值
template<typename _OutputIterator,typename _Size, typename _Ty>
_OutputIterator fill_n(_OutputIterator _First, _Size _Count, const _Ty& _Val) {
	for (;_Count > 0;_Count--) {
		*_First++ = _Val;
	}
	return _First;
}

//***********************************************
//fill:为 [first, last)区间内的所有元素填充新值
template<typename _OutputIterator, typename _Ty>
_OutputIterator fill_n(_OutputIterator _First, _OutputIterator _Last, const _Ty& _Val) {
	while (_First != _Last) {
		*_First++ = _Val;
	}
	return _First;
}

//***********************************************
// lexicographical_compare
// 以字典序排列对两个序列进行比较，当在某个位置发现第一组不相等元素时，有下列几种情况：
// (1)如果第一序列的元素较小，返回 true ，否则返回 false
// (2)如果到达 last1 而尚未到达 last2 返回 true
// (3)如果到达 last2 而尚未到达 last1 返回 false
// (4)如果同时到达 last1 和 last2 返回 false
template<typename _InputIterator1, typename _InputIterator2>
bool lexicographical_compare(_InputIterator1 _First1, _InputIterator1 _Last1,
	_InputIterator2 _First2, _InputIterator2 _Last2) {
	while (_First1 != _Last1 && _First2 != _Last2) {
		if (*_First1 < *_First2) {
			return true;
		}
		else if (*_First1 > *_First2) {
			return false;
		}
		_First1++;
		_First2++;
	}
	if (_First1 == _Last1 && _First2 != _Last2) {
		return true;
	}
	if (_First1 != _Last1 && _First2 == _Last2) {
		return false;
	}
	return false;
}

// 重载版本使用函数对象 comp 代替比较操作
template<typename _InputIterator1, typename _InputIterator2, typename _Pred>
bool lexicographical_compare(_InputIterator1 _First1, _InputIterator1 _Last1,
	_InputIterator2 _First2, _InputIterator2 _Last2, _Pred _Comp) {
	while (_First1 != _Last1 && _First2 != _Last2) {
		if (_Comp(*_First1, *_First2)) {
			return true;
		}
		else if (_Comp(*_First2, *_First1)) {
			return false;
		}
		_First1++;
		_First2++;
	}
	if (_First1 == _Last1 && _First2 != _Last2) {
		return true;
	}
	if (_First1 != _Last1 && _First2 == _Last2) {
		return false;
	}
	return false;
}

//***********************************************
// mismatch:平行比较两个序列，找到第一处失配的元素，返回一对迭代器，分别指向两个序列中失配的元素
template<typename _InputIterator1, typename _InputIterator2>
std::pair< _InputIterator1, _InputIterator2> mismatch(_InputIterator1 _First1, _InputIterator1 _Last1,
	_InputIterator2 _First2, _InputIterator2 _Last2) {
	while (_First1 != _Last1 && _First2 != _Last2) {
		if (*_First1 == *_First2) {
			_First1++;
			_First2++;
		}
	}
	return std::pair< _InputIterator1, _InputIterator2>(_First1, _First2);
}

// 重载版本使用函数对象 comp 代替比较操作
template<typename _InputIterator1, typename _InputIterator2, typename _Pred>
std::pair< _InputIterator1, _InputIterator2> mismatch(_InputIterator1 _First1, _InputIterator1 _Last1,
	_InputIterator2 _First2, _InputIterator2 _Last2, _Pred _Comp) {
	while (_First1 != _Last1 && _First2 != _Last2) {
		if (_Comp(*_First1,*_First2)) {
			_First1++;
			_First2++;
		}
	}
	return std::pair< _InputIterator1, _InputIterator2>(_First1, _First2);
}

}
#endif