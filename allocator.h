#pragma once
#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include<stddef.h>
#include"construct.h"

namespace TinySTL
{

template<class _Ty>
class allocator{
public:
    //类型定义
    typedef _Ty                                     value_type;
    typedef _Ty*                                    pointer;
    typedef _Ty&                                    reference;
    typedef const _Ty*                              const_pointer;
    typedef const _Ty&                              const_reference;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                             difference_type;

public:
    //静态函数声明
static _Ty* allocate();
static _Ty* allocate(const std::size_t count);

static void deallocate(_Ty* ptr);
static void deallocate(_Ty* ptr, const std::size_t count);

static void construct(_Ty* pos);
static void construct(_Ty* pos, _Ty& rhs);
static void construct(_Ty* pos, _Ty&& rhs);

template<typename..._Args>
static void construct(_Ty* pos, _Args&&... args);

static void destroy(_Ty* pos);
static void destroy(_Ty* begin, _Ty* end);

};

template<class _Ty>
_Ty* allocator<_Ty>::allocate() {
    return static_cast<_Ty*>(::operator new(sizeof(_Ty)));
}

template<class _Ty>
_Ty* allocator<_Ty>::allocate(const std::size_t count) {
    if (count == 0) {
        return nullptr;
    }
    return static_cast<_Ty*>(::operator new(count * sizeof(_Ty)));
}

template<class _Ty>
void allocator<_Ty>::deallocate(_Ty* ptr) {
    if (ptr) {
        ::delete ptr;
    }
}

template<class _Ty>
void allocator<_Ty>::deallocate(_Ty* ptr, const std::size_t count) {
    if (ptr) {
        ::delete ptr;
    }
}

template<class _Ty>
void allocator<_Ty>::construct(_Ty* pos) {
    //默认构造
    TinySTL::construct(pos);
}

template<class _Ty>
void allocator<_Ty>::construct(_Ty* pos, _Ty& rhs) {
    //拷贝构造
    TinySTL::construct(pos, rhs);
}

template<class _Ty>
void allocator<_Ty>::construct(_Ty* pos, _Ty&& rhs) {
    //移动构造
    TinySTL::construct(pos, rhs);
}

template<class _Ty>
template<typename... _Args>
void allocator<_Ty>::construct(_Ty* pos, _Args&&... args) {
    //一般构造
    TinySTL::construct(pos, std::forward<_Args>(args)...);
}

template<class _Ty>
void allocator<_Ty>::destroy(_Ty* pos) {
    TinySTL::destroy(pos);
}

template<class _Ty>
void allocator<_Ty>::destroy(_Ty* begin, _Ty* end) {
    TinySTL::destroy(begin, end);
}


}

#endif