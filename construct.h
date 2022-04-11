#pragma once
#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include<memory>

namespace TinySTL
{

template<typename _Ty>
void construct(_Ty* pos) {
    //默认构造
    ::new (static_cast<void*>(pos)) _Ty();
}


template<typename _Ty>
void construct(_Ty* pos,_Ty& rhs){
    //拷贝构造
    ::new (static_cast<void*>(pos)) _Ty(rhs);
}

template<typename _Ty>
void construct(_Ty* pos,_Ty&& rhs){
    //移动构造
    ::new (static_cast<void*>(pos)) _Ty(rhs);
}

template<typename _Ty,typename... _Args>
void construct(_Ty* pos,_Args&&... args){
    //一般构造
    ::new(static_cast<void*>(pos)) _Ty(std::forward<_Args>(args)...);
}

template<typename _Ty>
void destroy(_Ty* pos){
    if(pos){
        pos->~_Ty();
    }
}

template<typename _Ty>
void destroy(_Ty* begin,_Ty* end){
    //销毁一个区间内的对象
    for(;end!=begin;end--){
        destroy(end);
    }
}


}
#endif