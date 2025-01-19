#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

#include <iostream>
#include <cassert>
#include "add_entry.h"

using namespace std;

template <class T>
class Vector
{
public:
    Vector(int size = 0);
    Vector(T *arr, int size);

    //big three
    Vector(const Vector<T> &other);
    ~Vector();
    Vector<T> &operator=(const Vector<T> &rhs);

    //member access functions:
    T &operator[](int index);
    const T &operator[](int index) const;

    T &at(int index);             //return reference to item at position index
    const T &at(int index) const; //return a const item at position index

    T &front(); //return item at position 0.
    T &back();  //return item at the last position

    //Push and Pop functions:
    Vector &operator+=(const T &item); //push_back
    void push_back(const T &item);     //append to the end
    T pop_back();                      //remove last item and return it

    //Insert and Erase:
    void insert(int insert_here, const T &insert_this); //insert at pos
    void erase(int erase_this_index);                   //erase item at position
    int index_of(const T &item);                        //search for item. return index.

    //size and capacity:
    void set_size(int size); //enlarge the vector to this size
                             //buffer empty cells with 0
                             //can add extra parameter to specify what to resize with

    void set_capacity(int capacity);           //allocate this space
    int size() const { return _how_many; }     //return _size
    int capacity() const { return _capacity; } //return _capacity

    bool empty() const; //return true if vector is empty
                        //based on size

    //OUTPUT:
    template <class U>
    friend ostream &operator<<(ostream &outs, const Vector<U> &_a);

    int error() const; //returns error state
    void clear();      //clears error
    string error_desc() const;

private:
    int _capacity;
    int _how_many;
    T *_array;

    int _is_error() const; //checks for errors, does not set _error
    int _error;
};

template <class T>
Vector<T>::Vector(int size)
{
    const bool debug = false;

    assert(size >= 0 && "size must be greater than or equal to zero"); //i should be able to handle all errors in the ctors
                                                                       //just check error for user inputs and then clear error, or just add if statements to all member functions to prevent usage of class
    _how_many = size;
    _capacity = size + 2;
    _array = allocate<T>(_capacity);
    _error = 0;

    init_array(_array, size);
}

template <class T>
Vector<T>::Vector(T *arr, int size) //allocates new space and copies existing array
{
    const bool debug = false;

    assert(size >= 0 && "size must be greater than or equal to zero");

    _how_many = size;
    _capacity = size + 2;
    _array = allocate<T>(_capacity);
    copy_array(_array, arr, _how_many);
    _error = 0;
}

template <class T>
Vector<T>::Vector(const Vector<T> &other) //allocates new space and copies 'other' array
{
    const bool debug = false;

    _how_many = other._how_many;
    _capacity = other._capacity;
    _array = allocate<T>(_capacity);
    copy_array(_array, other._array, _how_many);
    _error = other._error;
}

template <class T>
Vector<T>::~Vector()
{
    const bool debug = false;

    delete[] _array;
    _array = nullptr;
}

template <class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &rhs)
{
    const bool debug = false;

    if (this == &rhs) //self reference check
    {
        return *this;
    }

    if (_capacity > 0)
    {
        delete[] _array;
        _array = nullptr;
    }

    _how_many = rhs._how_many; //copying everything from the 'other' vector
    _capacity = rhs._capacity;
    _array = allocate<T>(_capacity);
    copy_array(_array, rhs._array, _how_many);

    return *this;
}

template <class T>
T &Vector<T>::operator[](int index)
{
    const bool debug = false;

    assert(index < _how_many && "index must be less than size");
    assert(index >= 0 && "index must be greater than or equal to zero");

    T *walker = _array + index;
    return *walker;
}

template <class T>
const T &Vector<T>::operator[](int index) const
{
    const bool debug = false;

    assert(index < _how_many && "index must be less than size");
    assert(index >= 0 && "index must be greater than or equal to zero");

    T *walker = _array + index;
    return *walker;
}

template <class T>
T &Vector<T>::at(int index)
{
    const bool debug = false;

    assert(index < _how_many && "index must be less than size");
    assert(index >= 0 && "index must be greater than or equal to zero");

    T *walker = _array + index;
    return *walker;
}

template <class T>
const T &Vector<T>::at(int index) const
{
    const bool debug = false;

    assert(index < _how_many && "index must be less than size");
    assert(index >= 0 && "index must be greater than or equal to zero");

    T *walker = _array + index;
    return *walker;
}

template <class T>
T &Vector<T>::front()
{
    const bool debug = false;

    if (debug)
    {
        cout << "DEBUG: T &Vector<T>::front(): _array value: " << *_array << endl;
        print_array(_array, _how_many, _capacity);
    }

    return *_array; //item at position 0 (start of array)
}

template <class T>
T &Vector<T>::back()
{
    const bool debug = false;

    T *walker = _array + _how_many - 1; //setting walker to the last element of array

    if (debug)
    {
        cout << "DEBUG: T &Vector<T>::back(): walker value: " << *walker << endl;
        cout << "size: " << _how_many << " capacity: " << _capacity << endl;
        print_array(_array, _how_many, _capacity);
    }

    return *walker;
}

template <class T>
Vector<T> &Vector<T>::operator+=(const T &item)
{
    const bool debug = false;

    push_back(item);

    if (debug)
    {
        cout << "DEBUG: Vector<T> &Vector<T>::operator+=(const T &item): value at back: " << back() << endl;
        cout << "size: " << _how_many << " capacity: " << _capacity << endl;
    }

    return *this;
}

template <class T>
void Vector<T>::push_back(const T &item)
{
    const bool debug = false;

    _array = add_entry(_array, item, _how_many, _capacity);
}

template <class T>
T Vector<T>::pop_back()
{
    const bool debug = false;
    
    assert(_how_many > 0 && "size should be greater than zero");

    T popped; //popped is the element removed

    _array = remove_last_entry(_array, popped, _how_many, _capacity);

    return popped;
}

template <class T>
void Vector<T>::insert(int insert_here, const T &insert_this)
{
    const bool debug = false;

    if (debug)
    {
        cout << "DEBUG: BEFORE: IN void Vector<T>::insert(): size: " << _how_many << " capacity: " << _capacity << " insert_here: " << insert_here << " insert_this: " << insert_this << " array: " << endl;
        print_array(_array, _how_many, _capacity);
    }

    assert(insert_here <= _how_many && "index must be less than or equal to size");
    assert(insert_here >= 0 && "index must be greater or equal to zero");

    _array = insert_entry(_array, insert_this, insert_here, _how_many, _capacity);

    if (debug)
    {
        cout << "DEBUG: AFTER: IN void Vector<T>::insert(): size: " << _how_many << " capacity: " << _capacity << " insert_here: " << insert_here << " insert_this: " << insert_this << " array: " << endl;
        print_array(_array, _how_many, _capacity);
    }
}

template <class T>
void Vector<T>::erase(int erase_this_index)
{
    const bool debug = false;

    if (debug)
    {
        cout << "DEBUG: BEFORE: IN void Vector<T>::erase(): size: " << _how_many << " capacity: " << _capacity << " erase_this_index: " << erase_this_index << " array: " << endl;
        print_array(_array, _how_many, _capacity);
    }

    assert(erase_this_index < _how_many && "index must be less than or equal to size");
    assert(erase_this_index >= 0 && "index must be greater or equal to zero");

    _array = erase_entry(_array, erase_this_index, _how_many, _capacity);

    if (debug)
    {
        cout << "DEBUG: AFTER: IN void Vector<T>::erase(): size: " << _how_many << " capacity: " << _capacity << " erase_this_index: " << erase_this_index << " array: " << endl;
        print_array(_array, _how_many, _capacity);
    }
}

template <class T>
int Vector<T>::index_of(const T &item)
{
    const bool debug = false;

    return search(_array, _how_many, item);
}

template <class T>
void Vector<T>::set_size(int size)
{
    const bool debug = false;

    assert(size >= 0 && "size must be greater than or equal to zero");

    if (size < _how_many)
    {
        _how_many = size;
        _capacity = _how_many + 2;
    }
    else
    {
        _how_many = size;
        _capacity = _how_many + 2;
        reallocate<T>(_array, _how_many, _capacity);
    }

    if (debug)
    {
        print_array(_array, _how_many, _capacity);
    }
}

template <class T>
void Vector<T>::set_capacity(int capacity) //this does not initialize added capacity to any value
{
    const bool debug = false;

    assert(capacity >= 0 && "capacity must be greater than or equal to zero");

    if (capacity < _capacity)
    {
        _capacity = capacity;
        _how_many = capacity;
    }
    else
    {
        _capacity = capacity;
        reallocate<T>(_array, _how_many, _capacity);
    }

    if (debug)
    {
        print_array(_array, _how_many, _capacity);
    }
}

template <class T>
bool Vector<T>::empty() const
{
    const bool debug = false;

    if (debug)
    {
        cout << "DEBUG: IN bool Vector<T>::empty(): size: " << _how_many << " capacity: " << _capacity << " array: ";
        print_array(_array, _how_many, _capacity);
    }

    if (_how_many == 0)
    {
        return true;
    }

    return false;
}

template <class U>
ostream &operator<<(ostream &outs, const Vector<U> &_a)
{
    const bool debug = false;

    const U *start = _a._array;
    const U *end = _a._array + _a._how_many;

    if (_a._capacity != 0)
    {
        outs << "(" << _a._how_many << "/" << _a._capacity << ")";
    }
    else
    {
        outs << "(" << _a._how_many << ")";
    }

    outs << "\t"
         << "[ ";
    for (const U *p = start; p != end; p++)
    {
        outs << " " << *p << " ";
    }
    outs << " ]" << endl;

    return outs;
}

template <class T>
int Vector<T>::_is_error() const
{
    if (_how_many < 0)
    {
        return 1;
    }
    if (_how_many > _capacity)
    {
        return 2;
    }

    return 0;
}

template <class T>
int Vector<T>::error() const
{
    const bool debug = false;

    return _error;
}

template <class T>
void Vector<T>::clear()
{
    const bool debug = false;

    int size = 0;

    _how_many = size;
    _capacity = size + 2;
    _array = allocate<T>(_capacity);
    _error = 0;

    init_array(_array, size);
}

template <class T>
string Vector<T>::error_desc() const
{
    const bool debug = false;

    string error_desc = "No errors so far.";

    if (_error == 1)
    {
        error_desc = "ERROR: size is negative.";
    }
    if (_error == 2)
    {
        error_desc = "ERROR: size is greater than capacity.";
    }

    return error_desc;
}

#endif