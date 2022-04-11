#pragma once
#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include<cstddef>
#include"type_traits.h"
#include<type_traits>
namespace TinySTL 
{
//定义卷标
struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag:public input_iterator_tag{};
struct bidirectional_iterator_tag:public forward_iterator_tag{};
struct random_access_iterator_tag:public bidirectional_iterator_tag {};

template<typename _IterT, typename _Ty,typename _Distance=ptrdiff_t,
	typename _Pointer=_Ty*,typename _Reference=_Ty&>
struct Iterator 
{
	typedef _IterT							iterator_category;
	typedef _Ty								value_type;
	typedef _Distance						distance_type;
	typedef _Pointer						pointer;
	typedef _Reference						reference;
};

//利用iterator_traits，无论是哪种迭代器类型，都被包装为iterator_category
template<class _Iter>
struct iterator_traits 
{
	typedef typename _Iter::iterator_category		iterator_category;
	typedef typename _Iter::value_type				value_type;
	typedef typename _Iter::distance_type			distance_type;
	typedef typename _Iter::pointer					pointer;
	typedef typename _Iter::reference				reference;
};

template<class _IterT>
struct iterator_traits<_IterT*> {
	//针对原生指针的显式具体化版本
	//原生指针行为类似random_access_iterator
	typedef random_access_iterator_tag				iterator_category;
	typedef _IterT									value_type;
	typedef std::ptrdiff_t							distance_type;
	typedef _IterT*									pointer;
	typedef _IterT&									reference;
};

//萃取一个迭代器的卷标，返回一个卷标空对象
template<typename Iter>
typename iterator_traits<Iter>::iterator_category
iterator_category(const Iter& iter) {
	return typename iterator_traits<Iter>::iterator_category();
}

//萃取一个迭代器的距离类型,返回空指针
template<typename Iter>
typename iterator_traits<Iter>::distance*
distance_type(const Iter& iter){
	return static_cast<typename iterator_traits<Iter>::distance*>(nullptr);
}

//萃取一个迭代器的数据类型
template<typename Iter>
typename iterator_traits<Iter>::value_type*
value_type(const Iter& iter) {
	return static_cast<typename iterator_traits<Iter>::value_type*>(nullptr);
}


// iterator traits

template <class T>
struct has_iterator_cat
{
private:
	struct two { char a; char b; };
	template <class U> static two test(...);
	template <class U> static char test(typename U::iterator_category* = 0);
public:
	static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
struct has_iterator_cat_of
	: public m_bool_constant<std::is_convertible<
	typename iterator_traits<T>::iterator_category, U>::value>
{
};

// 萃取某种迭代器
template <class T, class U>
struct has_iterator_cat_of<T, U, false> : public m_false_type {};

template <class Iter>
struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag> {};

template <class Iter>
struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag> {};

template <class Iter>
struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag> {};

template <class Iter>
struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};

template <class Iter>
struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};



/********************************************************/
//distance:计算两个迭代器之间的距离
template<typename Iter>
typename iterator_traits<Iter>::distance_type
distance_dispatch(Iter begin,Iter end,input_iterator_tag){
    typename iterator_traits<Iter>::distance_type distance=0;
    while(begin++!=end){
        distance++;
    }
    return distance;
}

//针对random_access_iterator的特化版本
template<typename Iter>
typename iterator_traits<Iter>::distance_type
distance_dispatch(Iter begin,Iter end,random_access_iterator_tag){
    return end-begin;
}

template<typename Iter>
typename iterator_traits<Iter>::distance_type
distance(Iter begin,Iter end){
    return distance_dispatch(begin,end,iterator_category(begin));
}

/********************************************************/
//advance:将迭代器向前移动一段距离
template<typename Iter,typename DistanceType>
void advance(Iter& iter,DistanceType n,input_iterator_tag){
    while(n>0){
        iter++;
        n--;
    }
}

//针对random_access_iterator的特化版本
template<typename Iter,typename DistanceType>
void advance(Iter& iter,DistanceType n,random_access_iterator_tag){
    iter+=n;
}

template<typename Iter,typename DistanceType>
void advance(Iter& iter,DistanceType n){
	advance(iter,n,iterator_category(iter));
}

/********************************************************/

template<class _Iter>
class reverse_iterator {
	//嵌套型别定义
	typedef typename _Iter::iterator_category					iterator_category;
	typedef typename _Iter::value_type							value_type;
	typedef typename _Iter::distance_type						distance_type;
	typedef typename _Iter::pointer								pointer;
	typedef typename _Iter::reference							reference;

	typedef _Iter										iterator_type;
	typedef reverse_iterator<_Iter>						self;

private:
	_Iter iterator;

public:
	reverse_iterator() :iterator(_Iter()) {

	}
	explicit reverse_iterator(_Iter it) :iterator(it) {

	}
	reverse_iterator(const reverse_iterator& it) {
		this->iterator = it.iterator;
	}

	//返回维护的正向迭代器
	iterator_type base() {
		return iterator;
	}

	//运算符重载
	reference operator*()const {
		auto tmp = iterator;
		return *--tmp;
	}
	reference operator->()const {
		return &(operator*());
	}

	self& operator++() {
		iterator--;
		return *this;
	}
	self operator++(int) {
		self tmp(this->iterator);
		iterator--;
		return tmp;
	}
	self& operator--() {
		iterator++;
		return *this;
	}
	self operator--(int) {
		self tmp(this->iterator);
		iterator++;
		return tmp;
	}
	
	self& operator+=(distance_type n) {
		iterator -= n;
		return *this;
	}
	self operator+(distance_type n) {
		auto tmp = *this;
		tmp.operator+=(n);
		return tmp;
	}
	self& operator-=(distance_type n) {
		iterator += n;
		return *this;
	}
	self operator-(distance_type n) {
		auto tmp = *this;
		tmp.operator-=(n);
		return tmp;
	}

	bool operator==(const reverse_iterator& rhs)const {
		return this->iterator == rhs.iterator;
	}
	bool operator!=(const reverse_iterator& rhs)const {
		return this->iterator != rhs.iterator;
	}
	bool operator>(const reverse_iterator& rhs)const {
		return iterator < rhs.iterator;
	}
	bool operator>=(const reverse_iterator& rhs)const {
		return (*this > rhs || *this == rhs);
	}
	bool operator<(const reverse_iterator& rhs)const {
		return !(*this >= rhs);
	}
	bool operator<=(const reverse_iterator& rhs)const {
		return !(*this < rhs);
	}
	reference operator[](distance_type n)const {
		return *(*this + n);
	}

};
}
#endif