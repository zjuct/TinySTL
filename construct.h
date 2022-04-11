#pragma once
#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include<memory>

namespace TinySTL
{

template<typename _Ty>
void construct(_Ty* pos) {
    //Ĭ�Ϲ���
    ::new (static_cast<void*>(pos)) _Ty();
}


template<typename _Ty>
void construct(_Ty* pos,_Ty& rhs){
    //��������
    ::new (static_cast<void*>(pos)) _Ty(rhs);
}

template<typename _Ty>
void construct(_Ty* pos,_Ty&& rhs){
    //�ƶ�����
    ::new (static_cast<void*>(pos)) _Ty(rhs);
}

template<typename _Ty,typename... _Args>
void construct(_Ty* pos,_Args&&... args){
    //һ�㹹��
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
    //����һ�������ڵĶ���
    for(;end!=begin;end--){
        destroy(end);
    }
}


}
#endif