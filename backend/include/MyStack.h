#ifndef MY_STACK_H
#define MY_STACK_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "linked_list_functions.h"
using namespace std;

template <typename T>
class Stack
{
public:
    class Iterator
    {
    public:
        friend class Stack; //give access to list to access _ptr

        Iterator() : _ptr(nullptr){}; //default ctor

        Iterator(node<T> *p) : _ptr(p){}; //Point Iterator to where p
                                                    //is pointing to

        T &operator*()
        {
            //assert _ptr is not nullptr
            //return _item at _ptr
            assert(_ptr);
            return _ptr->_item;
        }

        T *operator->()
        {
            //assert _ptr is not nullptr
            //return address of item in node

            assert(_ptr);
            return &(_ptr->_item);
        }

        bool is_null()
        {
            //true if _ptr is NULL
            return _ptr == nullptr;
        }

        friend bool operator!=(const Iterator &left, const Iterator &right)
        {
            //true if left != right
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator &left, const Iterator &right)
        {
            //true if left == right
            return left._ptr == right._ptr;
        }

        Iterator &operator++()
        {
            //assert _ptr is not nullptr
            //point _ptr to the address of the next node
            //return the iterator being incremented

            assert(_ptr);
            _ptr = _ptr->next;
            return *this;
        }

        friend Iterator operator++(Iterator &it, int unused)
        {
            //friend operator: it++
            assert(it._ptr);
            Iterator hold = it;
            it._ptr = it._ptr->next;
            return hold;
        }

    private:
        node<T> *_ptr; //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<T> &copyMe);
    ~Stack();
    Stack<T> &operator=(const Stack<T> &RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template <typename TT>
    friend ostream &operator<<(ostream &outs,
                               const Stack<TT> &printMe);

    Iterator begin() const; //Iterator to the head node
    Iterator end() const;   //Iterator to NULL
    int size() const { return _size; }

    int error() const; //returns _error
    void clear();      //clears error
    string error_desc() const;

private:
    node<T> *_top;
    int _size;

    int _is_error() const; //checks for errors, does not set _error
    int _error;
};

template <typename T>
Stack<T>::Stack()
{
    _top = nullptr;
    _size = 0;
    _error = _is_error();
}

template <typename T>
Stack<T>::Stack(const Stack<T> &copyMe)
{
    _top = _copy_list(copyMe._top);
    _size = copyMe._size;
    _error = _is_error();
}

template <typename T>
Stack<T>::~Stack()
{
    _clear_list(_top);
    _size = 0;
    _error = _is_error();
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &RHS)
{
    //self reference check to see if LHS is the same as RHS
    //if so, *this gets returned
    //LHS list gets cleared using _clear_list
    //other member variables from RHS copied into LHS

    if (this == &RHS)
    {
        return *this;
    }

    _clear_list(_top);
    _top = _copy_list(RHS._top);
    _size = RHS._size;
    _error = _is_error();

    return *this;
}

template <typename T>
T Stack<T>::top()
{
    //return item at top without popping

    assert(_top != nullptr && "_top cannot be nullptr");

    return _top->_item;
}

template <typename T>
bool Stack<T>::empty()
{
    assert((_top == nullptr && _size == 0) || (_top != nullptr && _size != 0));

    return _size == 0;
}

template <typename T>
void Stack<T>::push(T item)
{
    //calls _insert_head on _top node ptr

    _insert_head(_top, item);
    _size++;
    _error = _is_error();
}

template <typename T>
T Stack<T>::pop()
{
    assert(_top != nullptr && "_top cannot be nullptr");

    T popped = _delete_node(_top, _top);
    _size--;
    _error = _is_error();

    return popped;
}

template <typename TT>
ostream &operator<<(ostream &outs, const Stack<TT> &printMe)
{
    //uses iterator instead of walkers
    //loops until printMe.end() (iterator marking end of list)
    //iterator increments each loop

    typename Stack<TT>::Iterator i(printMe._top);

    outs << "H->";
    for (; i != printMe.end(); i++)
    {
        outs << "[" << *i << "]"
             << "-> ";
    }
    outs << "|||";

    return outs;
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::begin() const
{
    //constructs and returns an iterator initialized using _head_ptr

    return Iterator(_top);
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const
{
    //constructs and returns an iterator initialized using nullptr

    return Iterator(nullptr);
}

template <class T>
void Stack<T>::clear()
{
    _clear_list(_top);
    _size = 0;
    _error = _is_error();
}

template <class T>
string Stack<T>::error_desc() const
{
    switch (error())
    {
    case 0:
        return "No known errors.";
    case 1:
        return "ERROR: size is negative";
    }
}

template <class T>
int Stack<T>::_is_error() const
{
    if (_size < 0)
    {
        return 1;
    }
    return 0;
}

#endif