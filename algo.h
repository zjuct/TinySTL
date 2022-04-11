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
//检查[first, last)内是否全部元素都满足一元操作 unary_pred 为 true 的情况，满足则返回 true
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
//检查[first, last)内是否存在某个元素满足一元操作 unary_pred 为 true 的情况，满足则返回 true
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
//检查[first, last)内是否全部元素都不满足一元操作 unary_pred 为 true 的情况，满足则返回 true
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
//对[first, last)区间内的元素与给定值进行比较，缺省使用 operator==，返回元素相等的个数
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
//对[first, last)区间内的每个元素都进行一元 unary_pred 操作，返回结果为 true 的个数
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
// 在[first, last)区间内找到等于 value 的元素，返回指向该元素的迭代器
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
// 在[first, last)区间内找到第一个令一元操作 unary_pred 为 true 的元素并返回指向该元素的迭代器
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
// find_if_not:在[first, last)区间内找到第一个令一元操作 unary_pred 为 false 的元素并返回指向该元素的迭代器
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
// 在[first1, last1)中查找[first2, last2)的首次出现点
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

// 重载版本使用函数对象 comp 代替比较操作
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
// 在[first, last)中查找连续 n 个 value 所形成的子序列，返回一个迭代器指向该子序列的起始处
// 重载版本使用函数对象 comp 代替比较操作
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
// 不对
// 在[first1, last1)区间中查找[first2, last2)最后一次出现的地方，若不存在返回 last1
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

// bidirectional_iterator_tag 版本重载
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

// 统一接口
template<typename _ForwardIterator1,typename _ForwardIterator2>
_ForwardIterator1 find_end(_ForwardIterator1 First1,_ForwardIterator1 Last1,
	_ForwardIterator2 First2,_ForwardIterator2 Last2){
	find_end_dispatch(First1,Last1,First2,Last2,iterator_category(First1));
}

// 重载版本使用函数对象 comp 代替比较操作
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

// bidirectional_iterator_tag 版本重载
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

// 统一接口
template<typename _ForwardIterator1,typename _ForwardIterator2,typename _Pred>
_ForwardIterator1 find_end(_ForwardIterator1 First1,_ForwardIterator1 Last1,
	_ForwardIterator2 First2,_ForwardIterator2 Last2,_Pred pred){
	find_end_dispatch(First1,Last1,First2,Last2,pred,iterator_category(First1));
}

//***********************************************
// find_first_of
// 在[first1, last1)中查找[first2, last2)中的某些元素，返回指向第一次出现的元素的迭代器
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

//重载版本使用函数对象 comp 代替比较操作
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
// 使用一个函数对象 f 对[first, last)区间内的每个元素执行一个 operator() 操作，但不能改变元素内容
template<typename _InputIterator,typename _Pred>
void for_each(_InputIterator _First, 
	_InputIterator _Last, _Pred _pred) {
	while (_First != _Last) {
		_pred(*_First++);
	}
}

//***********************************************
// adjacent_find
// 找出第一对匹配的相邻元素，缺省使用 operator== 比较，如果找到返回一个迭代器，指向这对元素的第一个元素
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

// 重载版本使用函数对象 comp 代替比较操作
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
// 在[first, last)中查找第一个不小于 value 的元素，并返回指向它的迭代器，若没有则返回 last
// _ForwardIterator版本
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

// lbound_dispatch 的 random_access_iterator_tag 版本
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

// 统一接口
template<typename _ForwardIterator, typename _Ty>
_ForwardIterator lower_bound(_ForwardIterator _First,
	_ForwardIterator _Last, const _Ty& _Val) {
	return lower_bound_dispatch(_First, _Last, _Val, iterator_catagory(_First));
}

// 重载版本使用函数对象 comp 代替比较操作
// __ForwardIterator版本
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

// lbound_dispatch 的 random_access_iterator_tag 版本
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

//统一接口
template<typename _ForwardIterator, typename _Pred>
_ForwardIterator lower_bound(_ForwardIterator _First,
	_ForwardIterator _Last, _Pred _pred) {
	return lower_bound_dispatch(_First, _Last, _pred, iterator_catagory(_First));
}

//***********************************************
// upper_bound
// 在[first, last)中查找第一个大于value 的元素，并返回指向它的迭代器，若没有则返回 last
// _ForwardIterator版本
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

 
// ubound_dispatch 的 random_access_iterator_tag 版本
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

//统一接口
template<typename _ForwardIterator, typename _Ty>
_ForwardIterator upper_bound(_ForwardIterator _First,
	_ForwardIterator _Last, const _Ty& _Val) {
	return upper_bound_dispatch(_First, _Last, _Val, iterator_catagory(_First));
}

// 重载版本使用函数对象 comp 代替比较操作
// _ForwardIterator版本
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

// ubound_dispatch 的 random_access_iterator_tag 版本
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

//统一接口
template<typename _ForwardIterator, typename _Pred>
_ForwardIterator upper_bound(_ForwardIterator _First,
	_ForwardIterator _Last, _Pred _pred) {
	return upper_bound_dispatch(_First, _Last, _pred, iterator_catagory(_First));
}

//***********************************************
// binary_search
// 二分查找，如果在[first, last)内有等同于 value 的元素，返回 true，否则返回 false
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

// 重载版本使用函数对象 comp 代替比较操作
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
// 查找[first,last)区间中与 value 相等的元素所形成的区间，返回一对迭代器指向区间首尾
// 第一个迭代器指向第一个不小于 value 的元素，第二个迭代器指向第一个大于 value 的元素

// erange_dispatch 的 forward_iterator_tag 版本

// erange_dispatch 的 random_access_iterator_tag 版本

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// generate
// 将函数对象 gen 的运算结果对[first, last)内的每个元素赋值

//***********************************************
// generate_n
// 用函数对象 gen 连续对 n 个元素赋值

//***********************************************
// includes
// 判断序列一S1 是否包含序列二S2

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// is_heap
// 检查[first, last)内的元素是否为一个堆，如果是，则返回 true

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// is_sorted
// 检查[first, last)内的元素是否升序，如果是升序，则返回 true

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// median
// 找出三个值的中间值

//重载版本使用函数对象 comp 代替比较操作

//***********************************************
// max_element
// 返回一个迭代器，指向序列中最大的元素

//重载版本使用函数对象 comp 代替比较操作

//***********************************************
// min_element
// 返回一个迭代器，指向序列中最小的元素

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// swap_ranges
// 将[first1, last1)从 first2 开始，交换相同个数元素
// 交换的区间长度必须相同，两个序列不能互相重叠，返回一个迭代器指向序列二最后一个被交换元素的下一位置

//***********************************************
// transform
// 第一个版本以函数对象 unary_op 作用于[first, last)中的每个元素并将结果保存至 result 中

// 第二个版本以函数对象 binary_op 作用于两个序列[first1, last1)、[first2, last2)的相同位置

//***********************************************
// remove_copy
// 移除区间内与指定 value 相等的元素，并将结果复制到以 result 标示起始位置的容器上

//***********************************************
// remove
// 移除所有与指定 value 相等的元素
// 并不从容器中删除这些元素，所以 remove 和 remove_if 不适用于 array

//***********************************************
// remove_copy_if
// 移除区间内所有令一元操作 unary_pred 为 true 的元素，并将结果复制到以 result 为起始位置的容器

//***********************************************
// remove_if
// 移除区间内所有令一元操作 unary_pred 为 true 的元素

//***********************************************
// replace
// 将区间内所有的 old_value 都以 new_value 替代

//***********************************************
// replace_copy
// 行为与 replace 类似，不同的是将结果复制到 result 所指的容器中，原序列没有改变

//***********************************************
// replace_copy_if
// 行为与 replace_if 类似，不同的是将结果复制到 result 所指的容器中，原序列没有改变

//***********************************************
// replace_if
// 将区间内所有令一元操作 unary_pred 为 true 的元素都用 new_value 替代

//***********************************************
// reverse
// 将[first, last)区间内的元素反转

// reverse_dispatch 的 random_access_iterator_tag 版本

//***********************************************
// reverse_copy
// 行为与 reverse 类似，不同的是将结果复制到 result 所指容器中

//***********************************************
// random_shuffle
// 将[first, last)内的元素次序随机重排

// 重载版本使用一个产生随机数的函数对象 rand

//***********************************************
// rotate
// 将[first, middle)内的元素和 [middle, last)内的元素互换，可以交换两个长度不同的区间
// 返回交换后 middle 的位置

// rotate_dispatch 的 bidirectional_iterator_tag 版本

// rotate_dispatch 的 random_access_iterator_tag 版本

//***********************************************
// rotate_copy
// 行为与 rotate 类似，不同的是将结果复制到 result 所指的容器中

//***********************************************
// is_permutation
// 判断[first1,last1)是否为[first2, last2)的排列组合

//***********************************************
// next_permutation
// 取得[first, last)所标示序列的下一个排列组合，如果没有下一个排序组合，返回 false，否则返回 true

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// prev_permutation
// 取得[first, last)所标示序列的上一个排列组合，如果没有上一个排序组合，返回 false，否则返回

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// merge
// 将两个经过排序的集合 S1 和 S2 合并起来置于另一段空间，返回一个迭代器指向最后一个元素的下一位置

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// inplace_merge
// 把连接在一起的两个有序序列结合成单一序列并保持有序

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// partial_sort
// 对整个序列做部分排序，保证较小的 N 个元素以递增顺序置于[first, first + N)中

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// partial_sort_copy
// 行为与 partial_sort 类似，不同的是把排序结果复制到 result 容器中

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// partition
// 对区间内的元素重排，被一元条件运算判定为 true 的元素会放到区间的前段
// 该函数不保证元素的原始相对位置

//***********************************************
// partition_copy
// 行为与 partition 类似，不同的是，将被一元操作符判定为 true 的放到 result_true 的输出区间
// 其余放到 result_false 的输出区间，并返回一个 mystl::pair 指向这两个区间的尾部

//***********************************************
// sort
// 将[first, last)内的元素以递增的方式排序

//***********************************************
// nth_element
// 对序列重排，使得所有小于第 n 个元素的元素出现在它的前面，大于它的出现在它的后面

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// unique_copy
// 从[first, last)中将元素复制到 result 上，序列必须有序，如果有重复的元素，只会复制一次

// unique_copy_dispatch 的 output_iterator_tag 版本

// 重载版本使用函数对象 comp 代替比较操作

//***********************************************
// unique
// 移除[first, last)内重复的元素，序列必须有序，和 remove 类似，它也不能真正的删除重复元素

// 重载版本使用函数对象 comp 代替比较操作


}

#endif