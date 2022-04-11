#pragma once
#ifndef _MYSTL_ALGOBASE_H_
#define _MYSTL_ALGOBASE_H_

#include"iterator.h"
#include"util.h"
#include<algorithm>
namespace TinySTL
{
//************************************************
//max:ȡ�����е����ֵ�����ʱ����ǰ��
template<typename _Ty>
const _Ty& max(const _Ty& _lhs, const _Ty& _rhs) {
	return _lhs >= _rhs ? _lhs : _rhs;
}
//max���ذ汾������ν��
template<typename _Ty,typename _Pred>
const _Ty& max(const _Ty& _lhs, const _Ty& _rhs, _Pred _pred) {
	return _pred(_lhs, _rhs) ? _lhs : _rhs;
}
//************************************************
//min:ȡ�����е����ֵ�����ʱ����ǰ��
template<typename _Ty>
const _Ty& min(const _Ty& _lhs, const _Ty& _rhs) {
	return _lhs <= _rhs ? _lhs : _rhs;
}

//min���ذ汾������ν��
template<typename _Ty, typename _Pred>
const _Ty& min(const _Ty& _lhs, const _Ty& _rhs, _Pred _pred) {
	return _pred(_lhs, _rhs) ? _lhs : _rhs;
}
//************************************************
//iter_swap:��������������ָ����Ե�
template<typename _Iter1,typename _Iter2>
void iter_swap(_Iter1 _lhs, _Iter2 _rhs) {
	auto tmp = *_lhs;
	*_lhs = *_rhs;
	*_rhs = tmp;
}

//************************************************
//copy:[first, last)�����ڵ�Ԫ�ؿ����� [result, result + (last - first))��
//input_iterator�汾
template<typename _InputIterator,typename _OutputIterator>
_OutputIterator unchecked_copy_cat(_InputIterator _First, 
	_InputIterator _Last, _OutputIterator _Result, input_iterator_tag) {
	for (;_First != _Last;_First++) {
		*_Result++ = *_First;
	}
	return _Result;
}
 
//random_access_iterator�汾
template<typename _RandomAccessIterator,typename _OutputIterator>
_OutputIterator unchecked_copy_cat(_RandomAccessIterator _First,
	_RandomAccessIterator _Last, _OutputIterator _Result, random_access_iterator_tag) {
	for (auto n = _Last - _First;n > 0;n--) {
		*_Result++ = *_First++;
	}
	return _Result;
}

//copy��ͳһ�ӿ�
template<typename _InputIterator, typename _OutputIterator>
_OutputIterator copy(_InputIterator _First,
	_InputIterator _Last, _OutputIterator _Result) {
	return unchecked_copy_cat(_First, _Last, _Result, iterator_catagory(_First));
}

//************************************************
//copy_backward:�� [first, last)�����ڵ�Ԫ�ؿ����� [result - (last - first), result)��
//�ṩbidirectional_iteraotr��random_access_iterator�����汾
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
//copy_if:��[first, last)������һԪ���� unary_pred ��Ԫ�ؿ������� result Ϊ��ʼ��λ����
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
//copy_n:�� [first, first + n)�����ϵ�Ԫ�ؿ����� [result, result + n)��
//����һ�� pair �ֱ�ָ�򿽱�������β��
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
//move:�� [first, last)�����ڵ�Ԫ���ƶ��� [result, result + (last - first))��
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
//move_backward:�� [first, last)�����ڵ�Ԫ���ƶ��� [result - (last - first), result)��
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
//equal:�Ƚϵ�һ������ [first, last)�����ϵ�Ԫ��ֵ�Ƿ�͵ڶ��������
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
//���ذ汾ʹ�ú������� comp ����Ƚϲ���
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
//fill_n:�� first λ�ÿ�ʼ��� n ��ֵ
template<typename _OutputIterator,typename _Size, typename _Ty>
_OutputIterator fill_n(_OutputIterator _First, _Size _Count, const _Ty& _Val) {
	for (;_Count > 0;_Count--) {
		*_First++ = _Val;
	}
	return _First;
}

//***********************************************
//fill:Ϊ [first, last)�����ڵ�����Ԫ�������ֵ
template<typename _OutputIterator, typename _Ty>
_OutputIterator fill_n(_OutputIterator _First, _OutputIterator _Last, const _Ty& _Val) {
	while (_First != _Last) {
		*_First++ = _Val;
	}
	return _First;
}

//***********************************************
// lexicographical_compare
// ���ֵ������ж��������н��бȽϣ�����ĳ��λ�÷��ֵ�һ�鲻���Ԫ��ʱ�������м��������
// (1)�����һ���е�Ԫ�ؽ�С������ true �����򷵻� false
// (2)������� last1 ����δ���� last2 ���� true
// (3)������� last2 ����δ���� last1 ���� false
// (4)���ͬʱ���� last1 �� last2 ���� false
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

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���
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
// mismatch:ƽ�бȽ��������У��ҵ���һ��ʧ���Ԫ�أ�����һ�Ե��������ֱ�ָ������������ʧ���Ԫ��
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

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���
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