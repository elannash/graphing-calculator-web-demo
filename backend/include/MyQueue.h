#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "linked_list_functions.h"
using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator
    {
    public:
        friend class Queue; //give access to list to access _ptr

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

    Queue();

    Queue(const Queue<T> &copyMe);
    ~Queue();
    Queue &operator=(const Queue<T> &RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const; //Iterator to the head node
    Iterator end() const;   //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template <typename TT>
    friend ostream &operator<<(ostream &outs, const Queue<TT> &printMe);

    int error() const; //returns _error
    void clear();      //clears error
    string error_desc() const;

private:
    node<T> *_front;
    node<T> *_rear;
    int _size;

    int _is_error() const; //checks for errors, does not set _error
    int _error;
};

template <typename T>
Queue<T>::Queue()
{
    //_front and _rear initialized to nullptr (empty list)
    //size 0 by default

    _front = _rear = nullptr;
    _size = 0;
    _error = _is_error();
}

template <typename T>
Queue<T>::Queue(const Queue<T> &copyMe)
{
    //_rear set to pointer returned by _copy_list (final node)
    //_front set within _copy_list

    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
    _error = _is_error();
}

template <typename T>
Queue<T>::~Queue()
{
    _clear_list(_front);
    _rear = nullptr;
    _size = 0;
}

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &RHS)
{
    if (this == &RHS)
    {
        return *this;
    }

    _clear_list(_front);
    _rear = _copy_list(_front, RHS._front);
    _size = RHS._size;
    _error = _is_error();

    return *this;
}

template <typename T>
bool Queue<T>::empty()
{
    assert((_front == nullptr && _rear == nullptr && _size == 0) || (_front != nullptr && _rear != nullptr && _size != 0));

    return _size == 0;
}

template <typename T>
T Queue<T>::front()
{
    assert(_front != nullptr && "_front cannot be nullptr");

    return _front->_item;
}

template <typename T>
T Queue<T>::back()
{
    assert(_rear != nullptr && "_rear cannot be nullptr");

    return _rear->_item;
}

template <typename T>
void Queue<T>::push(T item)
{
    //pushed from back

    _rear = _insert_after(_front, _rear, item);
    _size++;
    _error = _is_error();
}

template <typename T>
T Queue<T>::pop()
{
    //popped from front
    //if _front was the first node, _rear will be pointing at garbage when the node is deleted
    //so _rear gets set to nullptr in this case (if the list is empty after popping)

    assert(_front != nullptr && "_front cannot be nullptr");

    T popped = _delete_node(_front, _front);

    if (_front == nullptr)
    {
        _rear = nullptr;
    }

    _size--;
    _error = _is_error();

    return popped;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return Iterator(_front);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    return Iterator(nullptr);
}

template <typename T>
void Queue<T>::print_pointers()
{
    //prints items at _front and _rear

    cout << "_front: " << *_front << endl
         << "_rear: " << *_rear << endl;
}

template <typename TT>
ostream &operator<<(ostream &outs, const Queue<TT> &printMe)
{
    //uses iterator instead of walkers
    //loops until printMe.end() (iterator marking end of list)
    //iterator increments each loop

    typename Queue<TT>::Iterator i(printMe._front);

    outs << "H->";
    for (; i != printMe.end(); i++)
    {
        outs << "[" << *i << "]"
             << "-> ";
    }
    outs << "|||";

    return outs;
}

template <class T>
void Queue<T>::clear()
{
    _clear_list(_front);
    _rear = nullptr;
    _size = 0;
    _error = _is_error();
}

template <class T>
string Queue<T>::error_desc() const
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
int Queue<T>::_is_error() const
{
    if (_size < 0)
    {
        return 1;
    }
    return 0;
}

#endif