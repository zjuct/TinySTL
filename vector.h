#ifndef _VECTOR_H_
#define _VECTOR_H_

#include"allocator.h"
#include"iterator.h"
#include<initializer_list>

namespace TinySTL
{



template<typename _Ty,typename _Allocator=TinySTL::allocator<_Ty>>
class vector{
public:
    //嵌套类型定义
    typedef typename _Allocator::value_type                 value_type;
    typedef typename _Allocator::pointer                    pointer;
    typedef typename _Allocator::reference                  reference;
    typedef typename _Allocator::const_pointer              const_pointer;
    typedef typename _Allocator::const_reference            const_reference;
    typedef typename _Allocator::size_type                  size_type;
    typedef typename _Allocator::difference_type            difference_type;


    //迭代器类型定义
    typedef _Ty*                                            iterator;
    typedef const _Ty*                                      const_iterator;
    typedef reverse_iterator<iterator>                      reverse_iterator;
    typedef TinySTL::reverse_iterator<const_iterator>                const_reverse_iterator;


private:
    iterator _begin;        //空间头部
    iterator _end;          //目前使用空间的尾后位置
    iterator _last;         //目前分配空间的尾后位置

public:
    //构造，析构函数定义
    vector(){
        try_init();
    }
    vector(size_type n){
        init_space(n);
    }
    vector(size_type n,const _Ty& val){
        fill_init(n,val);
    }
    vector(std::initializer_list<_Ty>& il){
        copy_init(il.begin(),il.end());
    }
    vector(const vector& vec){
        copy_init(vec.begin(),vec.end());
    }
    vector(vector&& vec)
    :_begin(vec._begin),_end(vec._end),_last(vec._last){
        //接管vec的空间
        vec._begin=vec._end=vec._last=nullptr;
    }
    ~vector(){
        clear();
    }


public:
    //公有接口定义
    //迭代器相关
    iterator begin(){
        return _begin;
    }
    iterator begin()const{
        return _begin;
    }
    iterator end(){
        return _end;
    }
    iterator end()const{
        return _end;
    }
    const_iterator cbegin()const{
        return static_cast<const_iterator>(_begin);
    }
    const_iterator cend()const{
        return static_cast<const_iterator>(_end);
    }
    reverse_iterator rbegin(){
        return reverse_iterator(_end);
    }
    reverse_iterator rbegin()const{
        return reverse_iterator(_end);
    }
    reverse_iterator rend()const{
        return reverse_iterator(_begin);
    }
    reverse_iterator rend(){
        return reverse_iterator(_begin);
    }
    const_reverse_iterator crbegin()const{
        return static_cast<const_reverse_iterator>(rbegin());
    }
    const_reverse_iterator crend()const{
        return static_cast<const_reverse_iterator>(rend());
    }

    //容量相关
    difference_type size(){
        return _end-_begin;
    }
    difference_type capacity(){
        return _last-_begin;
    }
    bool empty(){
        return _begin==_end;
    }
    void clear();


private:
    //私有辅助函数定义
    size_type max(size_type lhs,size_type rhs){
        return lhs>rhs?lhs:rhs;
    }
    size_type min(size_type lhs,size_type rhs){
        return lhs<rhs?lhs:rhs;
    }

    bool is_full(){
        return _end==_last;
    }

    //默认初始化大小为16
    void try_init();

    //分配容量为n，当前大小为size的空间
    void init_space(const size_type n,const size_type size);

    //初始化，大小为n，初始值为val
    void fill_init(const size_type n,const _Ty& val);

    //根据迭代器范围拷贝初始化
    template<typename _Iter>
    void copy_init(_Iter begin,_Iter end);

    //扩展空间为当前的两倍
    void expand();
};
/*******************************************************************/
//公有方法定义
template<typename _Ty,typename _Allocator>
void vector<_Ty,_Allocator>::clear(){
    auto it=_begin;
    for(;it!=_end;++it){
        _Allocator::destroy(it);
    }
    _Allocator::deallocate(_begin);
    _begin=_end=_last=nullptr;
}


/*******************************************************************/
//私有辅助函数定义
template<typename _Ty,typename _Allocator>
void vector<_Ty,_Allocator>::try_init(){
    try{
        _begin=_Allocator::allocate(16);
        _end=_begin;
        _last=_begin+16;
    }catch(...){
        _begin=nullptr;
        _end=nullptr;
        _last=nullptr;
    }
}

template<typename _Ty,typename _Allocator>
void vector<_Ty,_Allocator>::init_space(const size_type n,const size_type size){
    try{
        _begin=_Allocator::allocate(n);
        _end=_begin+size;
        _last=_begin+n;
    }catch(...){
        _begin=nullptr;
        _end=nullptr;
        _last=nullptr;
    }
}

template<typename _Ty,typename _Allocator>
void vector<_Ty,_Allocator>::fill_init(const size_type n,const _Ty& val){
    auto size=max(n,16);
    init_space(size,n);
    auto it=_begin;
    for(;it!=_end;++it){
        *it=val;
    }
}

template<typename _Ty,typename _Allocator>
template<typename _Iter>
void vector<_Ty,_Allocator>::copy_init(_Iter begin,_Iter end){
    auto n=distance(begin,end);
    auto size=max(n,16);
    init_space(size,n);
    auto it=_begin;
    for(;it!=_end&&begin!=end;++it,++begin){
        *it=*begin;
    }
}

template<typename _Ty,typename _Allocator>
void vector<_Ty,_Allocator>::expand(){
    
}

}

#endif