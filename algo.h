#pragma once
#ifndef _MYSTL_ALGO_H_
#define _MYSTL_ALGO_H_

#include<cstddef>
#include<ctime>

#include"algobase.h"

namespace TinySTL
{
//***********************************************
//all_of
//���[first, last)���Ƿ�ȫ��Ԫ�ض�����һԪ���� unary_pred Ϊ true ������������򷵻� true
template<typename _InputIterator, typename _Unary_Pred>
bool all_of(_InputIterator _First, 
	_InputIterator _Last, _Unary_Pred _Pred) {
	while (_First != _Last) {
		if (!_Pred(*_First++)) {
			return false;
		}
	}
	return true;
}

//***********************************************
//any_of
//���[first, last)���Ƿ����ĳ��Ԫ������һԪ���� unary_pred Ϊ true ������������򷵻� true
template<typename _InputIterator, typename _Unary_Pred>
bool any_of(_InputIterator _First,
	_InputIterator _Last, _Unary_Pred _Pred) {
	while (_First != _Last) {
		if (_Pred(*_First++)) {
			return true;
		}
	}
	return false;
}

//***********************************************
//none_of
//���[first, last)���Ƿ�ȫ��Ԫ�ض�������һԪ���� unary_pred Ϊ true ������������򷵻� true
template<typename _InputIterator, typename _Unary_Pred>
bool none_of(_InputIterator _First,
	_InputIterator _Last, _Unary_Pred _Pred) {
	while (_First != _Last) {
		if (_Pred(*_First++)) {
			return false;
		}
	}
	return true;
}

//***********************************************
//count
//��[first, last)�����ڵ�Ԫ�������ֵ���бȽϣ�ȱʡʹ�� operator==������Ԫ����ȵĸ���
template<typename _InputIterator,typename _Ty>
int count(_InputIterator _First, 
	_InputIterator _Last, const _Ty& _Val) {
	int _Count = 0;
	while (_First != _Last) {
		if (*_First++ == _Val) {
			_Count++;
		}
	}
	return _Count;
}

//***********************************************
//count_if
//��[first, last)�����ڵ�ÿ��Ԫ�ض�����һԪ unary_pred ���������ؽ��Ϊ true �ĸ���
template<typename _InputIterator, typename _Unary_Pred>
int count(_InputIterator _First,
	_InputIterator _Last, _Unary_Pred _Pred) {
	int _Count = 0;
	while (_First != _Last) {
		if (_Pred(*_First++)) {
			_Count++;
		}
	}
	return _Count;
}

//***********************************************
// find
// ��[first, last)�������ҵ����� value ��Ԫ�أ�����ָ���Ԫ�صĵ�����
template<typename _InputIterator, typename _Ty>
_InputIterator find(_InputIterator _First,
	_InputIterator _Last, const _Ty& _Val) {
	while (_First != _Last) {
		if (*_First++ == _Val) {
			break;
		}
	}
	return _First;
}

//***********************************************
// find_if
// ��[first, last)�������ҵ���һ����һԪ���� unary_pred Ϊ true ��Ԫ�ز�����ָ���Ԫ�صĵ�����
template<typename _InputIterator, typename _Unary_Pred>
_InputIterator find_if(_InputIterator _First,
	_InputIterator _Last, _Unary_Pred _Pred) {
	while (_First != _Last) {
		if (_Pred(*_First++)) {
			break;
		}
	}
	return _First;
}

//***********************************************
// find_if_not:��[first, last)�������ҵ���һ����һԪ���� unary_pred Ϊ false ��Ԫ�ز�����ָ���Ԫ�صĵ�����
template<typename _InputIterator, typename _Unary_Pred>
_InputIterator find_if_not(_InputIterator _First,
	_InputIterator _Last, _Unary_Pred _Pred) {
	while (_First != _Last) {
		if (!_Pred(*_First++)) {
			break;
		}
	}
	return _First;
}

//***********************************************
// search
// ��[first1, last1)�в���[first2, last2)���״γ��ֵ�
template<typename _InputIterator1,typename _InputIterator2>
_InputIterator1 search(_InputIterator1 _First1, _InputIterator1 _Last1,
	_InputIterator1 _First2, _InputIterator2 _Last2) {
	auto n1=distance(_First1,_Last1);
	auto n2=distance(_First2,_Last2);
	if(n1<n2){
		return _Last1;
	}
	auto i=_First1;
	auto j=_First2;

	auto pos=i;
	while(i!=_Last1&&j!=_Last2){
		if(*i == *j){
			++i;
			++j;
		}
		else{
			++i;
			pos=i;
			j=_First2;
		}
	}
	if(j==_Last2){
		return pos;
	}else{
		return _Last1;
	}
}

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���
template<typename _InputIterator1,typename _InputIterator2,typename _Pred>
_InputIterator1 search(_InputIterator1 _First1,_InputIterator1 _Last1,
	_InputIterator2 _First2, _InputIterator2 _Last2,_Pred pred) {
	auto n1=distance(_First1,_Last1);
	auto n2=distance(_First2,_Last2);
	if(n1<n2){
		return _Last1;
	}
	auto i=_First1;
	auto j=_First2;
	while(i!=_Last1&&j!=_Last2){
		if(pred(*i,*j)){
			++i;
			++j;
		}
		else{
			++_First1;
			i=_First1;
			j=_First2;
		}
	}
	if(j==_Last2){
		return _First1;
	}else{
		return _Last1;
	}
}

//***********************************************
// search_n
// ��[first, last)�в������� n �� value ���γɵ������У�����һ��������ָ��������е���ʼ��
// ���ذ汾ʹ�ú������� comp ����Ƚϲ���
template<typename _InputIterator,typename _Ty>
_InputIterator search_n(_InputIterator First,_InputIterator Last,size_t n1,const _Ty& val){
	auto n2=distance(First,Last);
	if(n1>n2){
		return Last;
	}
	auto i=First;
	auto j=n1;
	while(i!=Last&&j!=n1){
		if(*i==val){
			++i;
			++j;
		}
		else{
			++First;
			i=First;
			j=n1;
		}
	}
	if(j==n1){
		return First;
	}
	else{
		return Last;
	}
}

 
//***********************************************
// find_end
// ����
// ��[first1, last1)�����в���[first2, last2)���һ�γ��ֵĵط����������ڷ��� last1
template<typename _ForwardIterator1,typename _ForwardIterator2>
_ForwardIterator1 find_end_dispatch(_ForwardIterator1 First1,_ForwardIterator1 Last1,
	_ForwardIterator2 First2,_ForwardIterator2 Last2,forward_iterator_tag){
	auto n1=distance(First1,Last1);
	auto n2=distance(First2,Last2);
	if(n1<n2){
		return Last1;
	}
	auto i=Last1;
	auto j=Last2;
	while(i!=First1&&j!=First2){
		if(*i==*j){
			--i;
			--j;
		}
		else{
			--Last1;
			i=Last1;
			j=Last2;
		}
	}
	if(j==First2){
		return i;
	}
	else{
		return Last1;
	}
}

// bidirectional_iterator_tag �汾����
template<typename _BidirectionalIterator1,typename _BidirectionalIterator2>
_BidirectionalIterator1 find_end_dispatch(_BidirectionalIterator1 First1,_BidirectionalIterator1 Last1,
	_BidirectionalIterator2 First2,_BidirectionalIterator2 Last2,bidirectional_iterator_tag){
	auto n1=distance(First1,Last1);
	auto n2=distance(First2,Last2);
	if(n1<n2){
		return Last1;
	}
	auto i=Last1;
	auto j=Last2;
	while(i!=First1&&j!=First2){
		if(*i==*j){
			--i;
			--j;
		}
		else{
			--Last1;
			i=Last1;
			j=Last2;
		}
	}
	if(j==First2){
		return i;
	}
	else{
		return Last1;
	}
}

// ͳһ�ӿ�
template<typename _ForwardIterator1,typename _ForwardIterator2>
_ForwardIterator1 find_end(_ForwardIterator1 First1,_ForwardIterator1 Last1,
	_ForwardIterator2 First2,_ForwardIterator2 Last2){
	find_end_dispatch(First1,Last1,First2,Last2,iterator_category(First1));
}

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���
template<typename _ForwardIterator1,typename _ForwardIterator2,typename _Pred>
_ForwardIterator1 find_end_dispatch(_ForwardIterator1 First1,_ForwardIterator1 Last1,
	_ForwardIterator2 First2,_ForwardIterator2 Last2,_Pred pred,forward_iterator_tag){
	auto n1=distance(First1,Last1);
	auto n2=distance(First2,Last2);
	if(n1<n2){
		return Last1;
	}
	auto i=Last1;
	auto j=Last2;
	while(i!=First1&&j!=First2){
		if(*i==*j){
			--i;
			--j;
		}
		else{
			--Last1;
			i=Last1;
			j=Last2;
		}
	}
	if(j==First2){
		return i;
	}
	else{
		return Last1;
	}
}

// bidirectional_iterator_tag �汾����
template<typename _BidirectionalIterator1,typename _BidirectionalIterator2,typename _Pred>
_BidirectionalIterator1 find_end_dispatch(_BidirectionalIterator1 First1,_BidirectionalIterator1 Last1,
	_BidirectionalIterator2 First2,_BidirectionalIterator2 Last2,_Pred pred,bidirectional_iterator_tag){
	auto n1=distance(First1,Last1);
	auto n2=distance(First2,Last2);
	if(n1<n2){
		return Last1;
	}
	auto i=Last1;
	auto j=Last2;
	while(i!=First1&&j!=First2){
		if(*i==*j){
			--i;
			--j;
		}
		else{
			--Last1;
			i=Last1;
			j=Last2;
		}
	}
	if(j==First2){
		return i;
	}
	else{
		return Last1;
	}
}

// ͳһ�ӿ�
template<typename _ForwardIterator1,typename _ForwardIterator2,typename _Pred>
_ForwardIterator1 find_end(_ForwardIterator1 First1,_ForwardIterator1 Last1,
	_ForwardIterator2 First2,_ForwardIterator2 Last2,_Pred pred){
	find_end_dispatch(First1,Last1,First2,Last2,pred,iterator_category(First1));
}

//***********************************************
// find_first_of
// ��[first1, last1)�в���[first2, last2)�е�ĳЩԪ�أ�����ָ���һ�γ��ֵ�Ԫ�صĵ�����
template<typename _InputIter,typename _ForwardIter>
_InputIter find_first_of(_InputIter First1,_InputIter Last1,
	_ForwardIter First2,_ForwardIter Last2){
	for(;First1!=Last1;++First1){
		for(auto it=First2;it!=Last2;++it){
			if(*First1==*it){
				return First1;
			}
		}
	}
	return Last1;
}

//���ذ汾ʹ�ú������� comp ����Ƚϲ���
template<typename _InputIter,typename _ForwardIter,typename _Pred>
_InputIter find_first_of(_InputIter First1,_InputIter Last1,
	_ForwardIter First2,_ForwardIter Last2,_Pred pred){
	for(;First1!=Last1;++First1){
		for(auto it=First2;it!=Last2;++it){
			if(pred(*First1,*it)){
				return First1;
			}
		}
	}
	return Last1;
}

//***********************************************
// for_each
// ʹ��һ���������� f ��[first, last)�����ڵ�ÿ��Ԫ��ִ��һ�� operator() �����������ܸı�Ԫ������
template<typename _InputIterator,typename _Pred>
void for_each(_InputIterator _First, 
	_InputIterator _Last, _Pred _pred) {
	while (_First != _Last) {
		_pred(*_First++);
	}
}

//***********************************************
// adjacent_find
// �ҳ���һ��ƥ�������Ԫ�أ�ȱʡʹ�� operator== �Ƚϣ�����ҵ�����һ����������ָ�����Ԫ�صĵ�һ��Ԫ��
template<typename _ForwardIter>
_ForwardIter adjacent_find(_ForwardIter First,_ForwardIter Last){
	if(First==Last){
		return Last;
	}
	auto it=First;
	++First;
	for(;First!=Last;++First){
		if(*it==*First){
			return it;
		}
		it=First;
	}
	if(*it==*First){
		return it;
	}
	return Last;
}

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���
template<typename _ForwardIter,typename _Pred>
_ForwardIter adjacent_find(_ForwardIter First,_ForwardIter Last,_Pred pred){
	if(First==Last){
		return Last;
	}
	auto it=First;
	++First;
	for(;First!=Last;++First){
		if(pred(*it,*First)){
			return it;
		}
		it=First;
	}
	if(*it==*First){
		return it;
	}
	return Last;
}

//***********************************************
// lower_bound
// ��[first, last)�в��ҵ�һ����С�� value ��Ԫ�أ�������ָ�����ĵ���������û���򷵻� last
// _ForwardIterator�汾
template<typename _ForwardIterator, typename _Ty>
_ForwardIterator lower_bound_dispatch(_ForwardIterator _First,
	_ForwardIterator _Last, const _Ty& _Val, forward_iterator_tag) {
	while (_First != _Last) {
		if (*_First >= _Val) {
			break;
		}
		else {
			_First++;
		}
	}
	return _First;
}

// lbound_dispatch �� random_access_iterator_tag �汾
template<typename _RandomAccessIterator, typename _Ty>
_RandomAccessIterator lower_bound_dispatch(_RandomAccessIterator _First,
	_RandomAccessIterator _Last, const _Ty& _Val, random_access_iterator_tag) {
	auto _Count = _Last - _First;
	int i = 0;
	for (;i < _Count;i++) {
		if (*(_First + i) >= _Val) {
			break;
		}
	}
	return _First + i;
}

// ͳһ�ӿ�
template<typename _ForwardIterator, typename _Ty>
_ForwardIterator lower_bound(_ForwardIterator _First,
	_ForwardIterator _Last, const _Ty& _Val) {
	return lower_bound_dispatch(_First, _Last, _Val, iterator_catagory(_First));
}

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���
// __ForwardIterator�汾
template<typename _ForwardIterator, typename _Pred>
_ForwardIterator lower_bound_dispatch(_ForwardIterator _First,
	_ForwardIterator _Last, _Pred _pred, forward_iterator_tag) {
	while (_First != _Last) {
		if (_pred(*_First)) {
			break;
		}
		else {
			_First++;
		}
	}
	return _First;
}

// lbound_dispatch �� random_access_iterator_tag �汾
template<typename _RandomAccessIterator, typename _Pred>
_RandomAccessIterator lower_bound_dispatch(_RandomAccessIterator _First,
	_RandomAccessIterator _Last, _Pred _pred, random_access_iterator_tag) {
	auto _Count = _Last - _First;
	int i = 0;
	for (;i < _Count;i++) {
		if (_pred(*(_First + i))) {
			break;
		}
	}
	return _First + i;
}

//ͳһ�ӿ�
template<typename _ForwardIterator, typename _Pred>
_ForwardIterator lower_bound(_ForwardIterator _First,
	_ForwardIterator _Last, _Pred _pred) {
	return lower_bound_dispatch(_First, _Last, _pred, iterator_catagory(_First));
}

//***********************************************
// upper_bound
// ��[first, last)�в��ҵ�һ������value ��Ԫ�أ�������ָ�����ĵ���������û���򷵻� last
// _ForwardIterator�汾
template<typename _ForwardIterator, typename _Ty>
_ForwardIterator upper_bound_dispatch(_ForwardIterator _First,
	_ForwardIterator _Last, const _Ty& _Val, forward_iterator_tag) {
	while (_First != _Last) {
		if (*_First > _Val) {
			break;
		}
		else {
			_First++;
		}
	}
	return _First;
}

 
// ubound_dispatch �� random_access_iterator_tag �汾
template<typename _RandomAccessIterator, typename _Ty>
_RandomAccessIterator upper_bound_dispatch(_RandomAccessIterator _First,
	_RandomAccessIterator _Last, const _Ty& _Val, random_access_iterator_tag) {
	auto _Count = _Last - _First;
	int i = 0;
	for (;i < _Count;i++) {
		if (*(_First + i) > _Val) {
			break;
		}
	}
	return _First + i;
}

//ͳһ�ӿ�
template<typename _ForwardIterator, typename _Ty>
_ForwardIterator upper_bound(_ForwardIterator _First,
	_ForwardIterator _Last, const _Ty& _Val) {
	return upper_bound_dispatch(_First, _Last, _Val, iterator_catagory(_First));
}

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���
// _ForwardIterator�汾
template<typename _ForwardIterator, typename _Pred>
_ForwardIterator upper_bound_dispatch(_ForwardIterator _First,
	_ForwardIterator _Last, _Pred _pred, forward_iterator_tag) {
	while (_First != _Last) {
		if (_pred(*_First)) {
			break;
		}
		else {
			_First++;
		}
	}
	return _First;
}

// ubound_dispatch �� random_access_iterator_tag �汾
template<typename _RandomAccessIterator, typename _Pred>
_RandomAccessIterator upper_bound_dispatch(_RandomAccessIterator _First,
	_RandomAccessIterator _Last, _Pred _pred, random_access_iterator_tag) {
	auto _Count = _Last - _First;
	int i = 0;
	for (;i < _Count;i++) {
		if (_pred(*(_First + i))) {
			break;
		}
	}
	return _First + i;
}

//ͳһ�ӿ�
template<typename _ForwardIterator, typename _Pred>
_ForwardIterator upper_bound(_ForwardIterator _First,
	_ForwardIterator _Last, _Pred _pred) {
	return upper_bound_dispatch(_First, _Last, _pred, iterator_catagory(_First));
}

//***********************************************
// binary_search
// ���ֲ��ң������[first, last)���е�ͬ�� value ��Ԫ�أ����� true�����򷵻� false
template<typename _RandomIter,typename _Ty>
bool binary_search(_RandomIter First,_RandomIter Last,const _Ty& val){
	auto n=distance(First,Last);
	n/=2;
	auto mid=advance(First,n);
	if(*mid==val){
		return true;
	}
	else if(*mid<val){
		return binary_search(++mid,Last,val);
	}
	else{
		return binary_search(First,--mid,val);
	}
}

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���
template<typename _RandomIter,typename _Ty,typename _Pred>
bool binary_search(_RandomIter First,_RandomIter Last,const _Ty& val,_Pred pred){
	auto n=distance(First,Last);
	n/=2;
	auto mid=advance(First,n);
	if(pred(*mid,val)==0){
		return true;
	}
	else if(pred(*mid,val)<0){
		return binary_search(++mid,Last,val);
	}
	else{
		return binary_search(First,--mid,val);
	}
}

//***********************************************
// equal_range
// ����[first,last)�������� value ��ȵ�Ԫ�����γɵ����䣬����һ�Ե�����ָ��������β
// ��һ��������ָ���һ����С�� value ��Ԫ�أ��ڶ���������ָ���һ������ value ��Ԫ��

// erange_dispatch �� forward_iterator_tag �汾

// erange_dispatch �� random_access_iterator_tag �汾

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// generate
// ���������� gen ����������[first, last)�ڵ�ÿ��Ԫ�ظ�ֵ

//***********************************************
// generate_n
// �ú������� gen ������ n ��Ԫ�ظ�ֵ

//***********************************************
// includes
// �ж�����һS1 �Ƿ�������ж�S2

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// is_heap
// ���[first, last)�ڵ�Ԫ���Ƿ�Ϊһ���ѣ�����ǣ��򷵻� true

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// is_sorted
// ���[first, last)�ڵ�Ԫ���Ƿ���������������򷵻� true

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// median
// �ҳ�����ֵ���м�ֵ

//���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// max_element
// ����һ����������ָ������������Ԫ��

//���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// min_element
// ����һ����������ָ����������С��Ԫ��

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// swap_ranges
// ��[first1, last1)�� first2 ��ʼ��������ͬ����Ԫ��
// ���������䳤�ȱ�����ͬ���������в��ܻ����ص�������һ��������ָ�����ж����һ��������Ԫ�ص���һλ��

//***********************************************
// transform
// ��һ���汾�Ժ������� unary_op ������[first, last)�е�ÿ��Ԫ�ز������������ result ��

// �ڶ����汾�Ժ������� binary_op ��������������[first1, last1)��[first2, last2)����ͬλ��

//***********************************************
// remove_copy
// �Ƴ���������ָ�� value ��ȵ�Ԫ�أ�����������Ƶ��� result ��ʾ��ʼλ�õ�������

//***********************************************
// remove
// �Ƴ�������ָ�� value ��ȵ�Ԫ��
// ������������ɾ����ЩԪ�أ����� remove �� remove_if �������� array

//***********************************************
// remove_copy_if
// �Ƴ�������������һԪ���� unary_pred Ϊ true ��Ԫ�أ�����������Ƶ��� result Ϊ��ʼλ�õ�����

//***********************************************
// remove_if
// �Ƴ�������������һԪ���� unary_pred Ϊ true ��Ԫ��

//***********************************************
// replace
// �����������е� old_value ���� new_value ���

//***********************************************
// replace_copy
// ��Ϊ�� replace ���ƣ���ͬ���ǽ�������Ƶ� result ��ָ�������У�ԭ����û�иı�

//***********************************************
// replace_copy_if
// ��Ϊ�� replace_if ���ƣ���ͬ���ǽ�������Ƶ� result ��ָ�������У�ԭ����û�иı�

//***********************************************
// replace_if
// ��������������һԪ���� unary_pred Ϊ true ��Ԫ�ض��� new_value ���

//***********************************************
// reverse
// ��[first, last)�����ڵ�Ԫ�ط�ת

// reverse_dispatch �� random_access_iterator_tag �汾

//***********************************************
// reverse_copy
// ��Ϊ�� reverse ���ƣ���ͬ���ǽ�������Ƶ� result ��ָ������

//***********************************************
// random_shuffle
// ��[first, last)�ڵ�Ԫ�ش����������

// ���ذ汾ʹ��һ������������ĺ������� rand

//***********************************************
// rotate
// ��[first, middle)�ڵ�Ԫ�غ� [middle, last)�ڵ�Ԫ�ػ��������Խ����������Ȳ�ͬ������
// ���ؽ����� middle ��λ��

// rotate_dispatch �� bidirectional_iterator_tag �汾

// rotate_dispatch �� random_access_iterator_tag �汾

//***********************************************
// rotate_copy
// ��Ϊ�� rotate ���ƣ���ͬ���ǽ�������Ƶ� result ��ָ��������

//***********************************************
// is_permutation
// �ж�[first1,last1)�Ƿ�Ϊ[first2, last2)���������

//***********************************************
// next_permutation
// ȡ��[first, last)����ʾ���е���һ��������ϣ����û����һ��������ϣ����� false�����򷵻� true

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// prev_permutation
// ȡ��[first, last)����ʾ���е���һ��������ϣ����û����һ��������ϣ����� false�����򷵻�

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// merge
// ��������������ļ��� S1 �� S2 �ϲ�����������һ�οռ䣬����һ��������ָ�����һ��Ԫ�ص���һλ��

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// inplace_merge
// ��������һ��������������н�ϳɵ�һ���в���������

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// partial_sort
// �������������������򣬱�֤��С�� N ��Ԫ���Ե���˳������[first, first + N)��

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// partial_sort_copy
// ��Ϊ�� partial_sort ���ƣ���ͬ���ǰ����������Ƶ� result ������

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// partition
// �������ڵ�Ԫ�����ţ���һԪ���������ж�Ϊ true ��Ԫ�ػ�ŵ������ǰ��
// �ú�������֤Ԫ�ص�ԭʼ���λ��

//***********************************************
// partition_copy
// ��Ϊ�� partition ���ƣ���ͬ���ǣ�����һԪ�������ж�Ϊ true �ķŵ� result_true ���������
// ����ŵ� result_false ��������䣬������һ�� mystl::pair ָ�������������β��

//***********************************************
// sort
// ��[first, last)�ڵ�Ԫ���Ե����ķ�ʽ����

//***********************************************
// nth_element
// ���������ţ�ʹ������С�ڵ� n ��Ԫ�ص�Ԫ�س���������ǰ�棬�������ĳ��������ĺ���

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// unique_copy
// ��[first, last)�н�Ԫ�ظ��Ƶ� result �ϣ����б�������������ظ���Ԫ�أ�ֻ�Ḵ��һ��

// unique_copy_dispatch �� output_iterator_tag �汾

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���

//***********************************************
// unique
// �Ƴ�[first, last)���ظ���Ԫ�أ����б������򣬺� remove ���ƣ���Ҳ����������ɾ���ظ�Ԫ��

// ���ذ汾ʹ�ú������� comp ����Ƚϲ���


}

#endif