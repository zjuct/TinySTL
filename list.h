#ifndef _LIST_H_
#define _LIST_H_

#include"allocator.h"
#include"iterator.h"
#include"functional.h"
#include<assert.h>
#include<exception>

namespace TinySTL
{

template<class _Ty,class _Allocator>
class list;

template<class _Ty>
class list_iterator;

template<class _Ty>
class list_const_iterator;

//����ඨ��
template<class _Ty>
class _Node{
public:
    //��Ԫ����
    friend class list_iterator<_Ty>;
    friend class list_const_iterator<_Ty>;
    friend class list<_Ty, TinySTL::allocator<_Node<_Ty>>>;
    

    _Node()
    :_val(-1),_prev(nullptr),_next(nullptr){}

    _Node(const _Ty& val)
    :_val(val),_prev(nullptr),_next(nullptr){}

    _Node(const _Ty& val,_Node* prev,_Node* next)
    :_val(val),_prev(prev),_next(next){}

    _Ty GetVal() {
        return _val;
    }

    //����ý�����������Ĺ�ϵ
    void UnLink() {
        _prev = _next = &*this;
    }
    
private:
    _Ty _val;
    _Node* _prev;
    _Node* _next;
};

//list�ĵ���������
template<class _Ty>
class list_iterator :public TinySTL::Iterator<bidirectional_iterator_tag, _Ty>
{
    friend class list<_Ty, TinySTL::allocator<_Node<_Ty>>>;
public:
    typedef _Ty                 value_type;
    typedef _Ty*                pointer;
    typedef _Ty&                reference;

    typedef _Node<_Ty>          list_node;
    typedef list_node*          pNode;
    typedef list_iterator       self;    //�������

    list_iterator() = default;
    list_iterator(pNode node):_content(node) {

    }

    reference operator*() {
        return _content->_val;
    }
    pointer operator->() {
        return &(operator*());
    }
    self& operator++() {
        _content = _content->_next;
        return *this;
    }
    self operator++(int) {
        self tmp(_content);
        _content = _content->_next;
        return tmp;
    }
    self& operator--() {
        _content = _content->_prev;
        return *this;
    }
    self operator--(int) {
        self tmp(_content);
        _content = _content->_prev;
        return tmp;
    }
    bool operator==(const self& rhs)const {
        return &(*_content) == &(*rhs._content);
    }
    bool operator!=(const self& rhs)const {
        return !(this->operator==(rhs));
    }
    bool operator!()const {
        return _content == nullptr;
    }
    
private:
    pNode GetNode() {
        return _content;
    }
    pNode _content;
};

//const������
template<class _Ty>
class list_const_iterator :public TinySTL::Iterator<bidirectional_iterator_tag, _Ty>
{
    friend class list<_Ty, TinySTL::allocator<_Node<_Ty>>>;
public:
    typedef _Ty                 value_type;
    typedef const _Ty*          const_pointer;
    typedef const _Ty&          const_reference;

    typedef _Node<_Ty>          list_node;
    typedef list_node*          pNode;
    typedef list_const_iterator self;    //�������

    list_const_iterator(pNode node) :_content(node) {
        
    }

    const_reference operator*() {
        return _content->_val;
    }
    const_pointer operator->() {
        return &(operator*());
    }
    self& operator++() {
        _content = _content->_next;
        return *this;
    }
    self operator++(int) {
        self tmp(_content);
        _content = _content->_next;
        return tmp;
    }
    self& operator--() {
        _content = _content->_prev;
        return *this;
    }
    self operator--(int) {
        self tmp(_content);
        _content = _content->_prev;
        return tmp;
    }
    
    bool operator==(const self& rhs) {
        return &(*_content) == &(*rhs._content);
    }
    bool operator!=(const self& rhs) {
        return !(this->operator==(rhs));
    }
private:
    pNode GetNode() {
        return _content;
    }
    pNode _content;
};

//list��������
template<class _Ty,class _Allocator=TinySTL::allocator<_Node<_Ty>>>
class list{
public:
    //���Ͷ���
    typedef _Ty                                                         value_type;
    typedef _Ty*                                                        pointer;
    typedef _Ty&                                                        reference;
    typedef const _Ty*                                                  const_pointer;
    typedef const _Ty&                                                  const_reference;
    typedef size_t                                                      size_type;

    typedef list_iterator<_Ty>                                          iterator;
    typedef list_const_iterator<_Ty>                                    const_iterator;
    typedef _Node<_Ty>                                                  Node;
    typedef _Node<_Ty>*                                                 pNode;

    typedef TinySTL::allocator<_Ty>                                     date_allocator;
private:
    //��Ա����
    pNode _head;
    size_type _size;
    
    
public:
    //���캯������������

    list(){
        FillInit(0, _Ty());
    }
    list(size_t n){
        FillInit(n, _Ty());
    }
    list(size_t n,const _Ty& val){
        FillInit(n, val);
    }
    list(std::initializer_list<_Ty>& il){
        CopyInit(il.begin(), il.end());
    }
    list(const list& l){
        CopyInit(l.begin(), l.end());
    }

    ~list() {
        clear();
    }
public:
    //���з���
    iterator begin(){
        return iterator(this->_head->_next);
    }
    const_iterator begin()const {
        return const_iterator(this->_head->_next);
    }
    iterator end(){
        return iterator(this->_head);
    }
    const_iterator end()const {
        return const_iterator(this->_head);
    }

    //������ز���
    size_type size()const {
        return _size;
    }

    bool empty()const {
        return _size == 0;
    }

    void clear() {
        earse(begin(), end());
    }

    //����Ԫ����ز���
    reference front() {
        return const_cast<reference>((static_cast<const list&>(*this)).front());
    }
    const_reference front()const {
        if (empty()) {
            throw new std::exception();
        }
        return *begin();
    }

    reference back() {
        return const_cast<reference>((static_cast<const list&>(*this)).back());
    }
    const_reference back()const {
        if (empty()) {
            throw new std::exception();
        }
        return *(--end());
    }

    //����������ز���
    void assign(size_type n,const _Ty& val) {
        fill_assign(n, val);
    }

    template<typename _Iter,typename std::enable_if<
        is_input_iterator<_Iter>::value, int>::type = 0>
        void assign(_Iter begin, _Iter end) {
        copy_assign(begin, end);
    }
    void assign(std::initializer_list<_Ty>& il) {
        copy_assign(il.begin(), il.end());
    }

    //emplace_back/emplace_front/emplace
    template<typename...Args>
    void emplace_back(Args&&...args) {
        pNode node = GetNode(args...);
        LinkNode(end(), node);
        ++_size;
    }
    template<typename...Args>
    void emplace_front(Args&&...args) {
        pNode node = GetNode(args...);
        LinkNode(begin(), node);
        ++_size;
    }
    template<typename...Args>
    void emplace(iterator pos,Args&&...args) {
        pNode node = GetNode(args...);
        LinkNode(pos, node);
        ++_size;
    }

    void resize(size_type n) {
        resize(n, _Ty());
    }
    void resize(size_type n, const _Ty val);

    //���뵽pos֮ǰ
    iterator insert(const iterator pos, const _Ty& val);

    iterator insert(const iterator pos, size_type n, const _Ty& val);

    iterator insert(const iterator pos, _Ty&& val);

    template<typename _Iter, typename std::enable_if<
        TinySTL::is_input_iterator<_Iter>::value, int>::type>
    iterator insert(const iterator pos, _Iter begin, _Iter end) {
        pNode node = nullptr;
        while (begin != end) {
            pNode tmp = insert(pos, *begin);
            if (!node) {
                node = tmp;
            }
        }
        return iterator(node);
    }

    //ɾ��posָ���Ԫ��
    bool earse(const iterator pos);
    //ɾ��һ�������ڵ�Ԫ��
    bool earse(const iterator begin, const iterator end);

    //push/pop����
    iterator push_back(const _Ty& val) {
        return insert(end(), val);
    }
    iterator push_back(_Ty&& val) {
        return insert(end(), val);
    }
    iterator push_front(const _Ty& val) {
        return insert(begin(), val);
    }
    iterator push_front(_Ty&& val) {
        return insert(begin(), val);
    }

    bool pop_back() {
        if (empty()) {
            return false;
        }
        iterator pos = end();
        pos--;
        earse(pos);
        return true;
    }
    bool pop_front() {
        if (empty()) {
            return false;
        }
        earse(begin());
    }
    //����
    void sort() {
        quick_sort(begin(), --end());
    }

    template<typename _Pred>
    void sort(_Pred pred) {
        quick_sort(begin(), --end(), pred);
    }

    void swap(list& rhs) {
        pNode* tmp = this->_head;
        this->_head = rhs->_head;
        rhs->_head = tmp;
        size_type size = this->_size;
        this->_size = rhs->_size;
        rhs->_size = size;
    }

    //list��ز���
    //ɾ��������val��ȵĽ��
    void remove(const _Ty& val) {
        remove_if([=](const _Ty& _val)->bool {
            return _val == val;
            });
    }
    //ɾ���������������Ľ��
    template<typename _Pred>
    void remove_if(_Pred pred);

    //��ת����
    void reverse();

    //ƴ������
    void splice(iterator pos,list& l);
    void splice(iterator pos, list& l, iterator it);
    void splice(iterator pos, list& l, iterator begin, iterator end);

    //��������ȥ��
    void unique() {
        unique(equal_to<_Ty>());
    }

    template<typename BinaryPred>
    void unique(BinaryPred pred);

    void merge(list& l) {
        merge(l, less<_Ty>());
    }
    template<typename _Pred>
    void merge(list& l, _Pred pred);

    
private:
    //˽�и�������
    
    //��ȡһ�����
    pNode BuyNode(const _Ty& val, pNode prev, pNode next) {
        pNode node = _Allocator::allocate();
        _Allocator::construct(node, val, prev, next);
        return node;
    }

    template<typename...Args>
    pNode GetNode(Args...args) {
        pNode node = _Allocator::allocate();
        try {
            date_allocator::construct(&(node->_val), std::forward<Args>(args)...);
            node->_next = nullptr;
            node->_prev = nullptr;
        }
        catch (std::exception e) {
            _Allocator::deallocate(node);
            throw;
        }
        return node;
    }

    //ָ����С�ͳ�ʼֵ�ĳ�ʼ��
    void FillInit(size_type n, const _Ty& value);
    
    template<typename _Iter>
    void CopyInit(_Iter begin, _Iter end);

    //����һ�����
    void DestroyNode(pNode node);

    //��[begin,end)��Ľ��������Ͽ�����
    void unlinkNode(pNode begin, pNode end);

    template<typename _Pred = less<_Ty>>
    void quick_sort(iterator begin, iterator end, _Pred pred = _Pred());

    template<typename _Pred = less<_Ty>>
    pNode Qsort(pNode begin, pNode end, _Pred pred = _Pred());

    //��pos������[begin,end]�Ľ��
    void LinkNodes(pNode pos, pNode begin, pNode end) {
        pos->_next->_prev = end;
        end->_next = pos->_next;
        pos->_next = begin;
        begin->_prev = pos;
    }

    //��posǰ����[begin,end]�Ľ��
    void LinkNodesBefore(pNode pos, pNode begin, pNode end) {
        LinkNodes(pos->_prev, begin, end);
    }

    //��������pos֮ǰ
    void LinkNode(iterator pos, pNode node) {
        node->_next = pos._content;
        pos._content->_prev->_next = node;
        node->_prev = pos._content->_prev;
        pos._content->_prev = node;
    }

    void swap(pNode lhs, pNode rhs) {
        _Ty tmp = lhs->_val;
        lhs->_val = rhs->_val;
        rhs->_val = tmp;
    }

    void fill_assign(size_type n, const _Ty& val);
    template<typename _Iter>
    void copy_assign(_Iter begin, _Iter end);
};

template<class _Ty, class _Allocator>
typename list<_Ty, _Allocator>::iterator
list<_Ty, _Allocator>::insert(const iterator pos, const _Ty& val) {
    _size++;
    pNode curr = pos._content;
    pNode node = BuyNode(val, nullptr, nullptr);
    if (_head->_prev == nullptr) {
        node->_next = _head;
        node->_prev = _head;
        _head->_next = node;
        _head->_prev = node;
    }
    else {
        curr->_prev->_next = node;
        node->_prev = curr->_prev;
        curr->_prev = node;
        node->_next = curr;
    }
    return iterator(node);
}

template<class _Ty, class _Allocator>
typename list<_Ty, _Allocator>::iterator
list<_Ty, _Allocator>::insert(const iterator pos, size_type n, const _Ty& val) {
    iterator iter = nullptr;
    while (n > 0) {
        iterator tmp = insert(pos, val);
        if (!iter) {
            iter = tmp;
        }
        n--;
    }
    return iter;
}

template<class _Ty, class _Allocator>
typename list<_Ty, _Allocator>::iterator
list<_Ty, _Allocator>::insert(const iterator pos, _Ty&& val) {
    _size++;
    pNode curr = pos._content;
    pNode node = BuyNode(val, nullptr, nullptr);
    if (_head->_prev == nullptr) {
        node->_next = _head;
        node->_prev = _head;
        _head->_next = node;
        _head->_prev = node;
    }
    else {
        curr->_prev->_next = node;
        node->_prev = curr->_prev;
        curr->_prev = node;
        node->_next = curr;
    }
    return iterator(node);
}

//ɾ��posָ���Ԫ��
template<class _Ty, class _Allocator>
bool list<_Ty, _Allocator>::earse(iterator pos) {
    _size--;
    if (pos == end()) {
        return false;
    }
    pNode tmp = pos._content;
    tmp->_prev->_next = tmp->_next;
    tmp->_next->_prev = tmp->_prev;
    DestroyNode(tmp);
    _Allocator::deallocate(tmp);
    return true;
}

//ɾ��һ�������ڵ�Ԫ��
template<class _Ty, class _Allocator>
bool list<_Ty, _Allocator>::earse(iterator begin, iterator end) {
    if (distance(begin, end) > size()) {
        return false;
    }
    unlinkNode(begin._content, end._content);
    while (begin != end) {
        pNode curr = begin._content;
        ++begin;
        DestroyNode(curr);
        --_size;
    }
    return true;
}

template<class _Ty, class _Allocator>
void list<_Ty, _Allocator>::FillInit(size_type n, const _Ty& value) {
    _head = _Allocator::allocate();
    _head->UnLink();
    _size = n;
    try {
        for (;n > 0;n--) {
            auto node = BuyNode(value, nullptr, nullptr);
            _head->_prev->_next = node;
            node->_prev = _head->_prev;
            _head->_prev = node;
            node->_next = _head;
        }
    }
    catch (...) {
        clear();
        _Allocator::deallocate(_head);
        _head = nullptr;
        throw;
    }
}

template<class _Ty, class _Allocator>
template<typename _Iter>
void list<_Ty, _Allocator>::CopyInit(_Iter begin, _Iter end) {
    _head = _Allocator::allocate();
    _head->UnLink();
    size_type n = distance(begin, end);
    _size = n;
    try {
        for (;n > 0;--n, ++begin) {
            auto node = BuyNode(*begin, nullptr, nullptr);
            _head->_prev->_next = node;
            node->_prev = _head->_prev;
            _head->_prev = node;
            node->_next = _head;
        }
    }
    catch (...) {
        clear();
        _Allocator::deallocate(_head);
        _head = nullptr;
        throw;
    }
}

template<class _Ty, class _Allocator>
void list<_Ty, _Allocator>::DestroyNode(pNode node) {
    _Allocator::destroy(node);

}

//��[begin,end)�������н��
template<class _Ty, class _Allocator>
void list<_Ty, _Allocator>::unlinkNode(pNode begin, pNode end) {
    begin->_prev->_next = end;
    end->_prev = begin->_prev;
}

template<class _Ty, class _Allocator>
void list<_Ty, _Allocator>::fill_assign(size_type n, const _Ty& val) {
    auto i = begin();
    auto j = end();
    for (;n > 0 && i != j;n--, ++i) {
        *i = val;
    }
    if (n > 0) {
        //����ʣ�µ�
        insert(end(), n, val);
    }
    if (i != j) {
        earse(i, j);
    }
}

template<class _Ty, class _Allocator>
template<typename _Iter>
void list<_Ty, _Allocator>::copy_assign(_Iter begin, _Iter end) {
    auto i = begin();
    auto j = end();
    for (;i != j && begin != end;++begin, ++i) {
        *i = *begin;
    }
    if (begin != end) {
        insert(end(), begin, end);
    }
    if (i != j) {
        earse(i, j);
    }
}

/**************************************************************************************************/
//���з���

template<class _Ty, class _Allocator>
template<typename _Pred>
typename list<_Ty, _Allocator>::pNode
list<_Ty, _Allocator>::Qsort(pNode begin, pNode end, _Pred pred) {
    //��begin��Ϊ��Ԫ�ֳ����ѣ�������Ԫλ��
    if (begin == end) {
        return begin;
    }
    pNode i = begin;
    pNode j = end;
    _Ty tmp = i->_val;
    //i = i->_next;
    while (i != j) {
        while (i != j && pred(tmp, j->_val)) {
            j = j->_prev;
        }
        i->_val = j->_val;
        while (i != j && pred(i->_val, tmp)) {
            i = i->_next;
        }
        //����i��j
        j->_val = i->_val;
    }
    i->_val = tmp;
    return i;
}

template<class _Ty, class _Allocator>
template<typename _Pred>
void list<_Ty, _Allocator>::quick_sort(iterator begin, iterator end, _Pred pred) {
    pNode left = begin._content;
    pNode right = end._content;
    if (left->_prev == right) {
        return;
    }
    if (left == right) {
        return;
    }
    if (left->_next == right) {
        if (pred(right->_val, left->_val)) {
            swap(left, right);
        }
        return;
    }
    pNode pivit = Qsort(left, right, pred);
    if (pivit->_prev != _head && pivit != left) {
        quick_sort(begin, pivit->_prev, pred);
    }
    if (pivit->_next != _head && pivit != right) {
        quick_sort(pivit->_next, end, pred);
    }
}

template<class _Ty, class _Allocator>
template<typename _Pred>
void list<_Ty, _Allocator>::remove_if(_Pred pred) {
    pNode tmp = _head->_next;
    while (tmp != _head) {
        pNode next = tmp->_next;
        if (pred(tmp->_val)) {
            earse(iterator(tmp));
        }
        tmp = next;
    }
}

template<class _Ty, class _Allocator>
void list<_Ty, _Allocator>::reverse() {
    pNode tmp = _head->_next;
    pNode prev = _head;
    pNode curr = _head->_next;
    pNode next = nullptr;
    do{
        next = curr->_next;
        prev->_prev = curr;
        curr->_next = prev;
        prev = curr;
        curr = next;
    } while (curr != tmp);
}

//��l�����������뵽pos��
template<class _Ty, class _Allocator>
void list<_Ty, _Allocator>::splice(iterator pos, list& l) {
    splice(pos, l, l.begin(), l.end());
}

template<class _Ty, class _Allocator>
void list<_Ty, _Allocator>::splice(iterator pos, list& l, iterator it) {
    splice(pos, l, it, iterator(it._content->_next));
}

//��[begin,end)����posǰ
template<class _Ty, class _Allocator>
void list<_Ty, _Allocator>::splice(iterator pos, list& l, iterator begin, iterator end) {
    size_type n = distance(begin, end);
    pNode tmp = end._content->_prev;
    pNode left = begin._content->_prev;
    pNode right = end._content;
    l.unlinkNode(begin._content, end._content);
    left->_next = right;
    right->_prev = left;
    LinkNodes(pos._content->_prev, begin._content, tmp);
    _size += n;
    l._size -= n;
}

template<class _Ty, class _Allocator>
template<typename BinaryPred>
void list<_Ty, _Allocator>::unique(BinaryPred pred) {
    auto i = begin();
    auto j = end();
    auto k = i;
    ++k;
    while (k != j) {
        if (pred(*i, *k)) {
            earse(k);
        }
        else {
            i = k;
        }
        k = i;
        ++k;
    }
}

//��������ϳ�
template<class _Ty, class _Allocator>
template<typename _Pred>
void list<_Ty, _Allocator>::merge(list& l, _Pred pred) {
    auto begin1 = this->begin();
    auto end1 = this->end();
    auto begin2 = l.begin();
    auto end2 = l.end();

    auto i = this->begin();
    auto j = l.begin();
    while (i != end1 && j != end2) {
        if (pred(*i, *j)) {
            ++i;
        }
        else {
            //j��С����l����������������ӵ�i֮ǰ
            auto k = j;
            while (j != end2 && pred(*j, *i)) {
                ++j;
            }
            auto tmp = j._content->_prev;
            l.unlinkNode(k._content, j._content);
            LinkNodesBefore(i._content, k._content, tmp);
        }
    }
    //�ƶ�l��ʣ��Ľ��
    while (j != end2) {
        auto tmp = end2._content->_prev;
        l.unlinkNode(j, end2);
        LinkNodesBefore(end1._content, j._content, tmp);
    }
    _size += l._size;
    l._size = 0;
}

template<class _Ty, class _Allocator>
void list<_Ty, _Allocator>::resize(size_type n, const _Ty val) {
    assign(n, val);
}

}


#endif