#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

template <typename T>
struct node
{
public:
    T _item;
    node<T> *next;

    node();
    node(T item);

    template <typename U>
    friend ostream &operator<<(ostream &outs, const node<U> &printMe);

    int error() const; //returns _error
    void clear();      //clears error
    string error_desc() const;
    int _is_error() const; //checks for errors, does not set _error
    int _error;
};

template <typename T>
node<T>::node() : _item(T()), next(nullptr), _error(0){};

template <typename T>
node<T>::node(T item) : _item(item), next(nullptr), _error(0){};

template <typename U>
ostream &operator<<(ostream &outs, const node<U> &printMe)
{
    outs << "[ " << printMe._item << " ]";

    return outs;
}

#endif