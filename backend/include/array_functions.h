#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

const int MINIMUM_CAPACITY = 3;

template<typename T>
T* allocate(int capacity = MINIMUM_CAPACITY);           //allocate 'capacity' 
                                                        //      elements. 
                                                        //  return array

template <typename T>
T* reallocate(T* a, int size, int capacity);            //take array, resize it 
                                                        //  return new array. 
                                                        //  delete old array

template <typename T>
void print_array(T* a, int size, int capacity = 0, ostream& outs = cout);    //prints 
                                                        //  (size/capacity)
                                                        //  for debugging

template <typename T>
void print(T* a, unsigned int how_many, ostream& outs = cout);  //print array

template <typename T>
T* search_entry(T* a, int size, const T& find_me);      //search for 'find me'

template <typename T>
int search(T* a, int size, const T& find_me);           //search for 'find_me' 

template <typename T>
void shift_left(T* a, int& size, int shift_here);       //shift left @ pos:
                                                        //    erases @ pos
template <typename T>
void shift_left(T* a, int& size, T* shift_here);        //shift left @ pos: 
                                                        //    erases @ pos

template <typename T>
void shift_right(T *a, int &size, int shift_here);      //shift right: 
                                                        //      make a hole

template <typename T>
void shift_right(T *a, int &size, T* shift_here);       //shift right: 
                                                        //   make a hole

template <typename T>
void copy_array(T *dest, const T* src, int many_to_copy);      //copy from src to dest

template <typename T>
T* copy_array(const T *src, int size);                  //return a 
                                                        //  copy of src

template <typename T>
string array_string(const T *a, int size);              //return array 
                                                        //  as a string

template <typename T>
void init_array(T *a, int size, const T &item = T());
/*======================================================================================*/


template <typename T>
T* allocate(int capacity)
{
    const bool debug = false;

    if (debug) 
    {
        cout << "allocate: capacity: " << capacity <<endl;
    }

    return new T[capacity];
}

template <typename T>
T* reallocate(T* a, int size, int capacity)
{
    T *start = allocate<T>(capacity);

    copy_array(start, a, size);

    delete[] a;
    
    return start;
}

template <typename T>
void print_array(T* a, int size, int capacity, ostream& outs)
{
    T *start = a;
    T *end = a + size;

    if (capacity != 0)
    {
        outs << "(" << size << "/" << capacity << ")";
    } else
    {
        outs << "(" << size << ")";
    }

    outs << "\t" << "[ ";
    for (T *p = start; p != end; p++)
    {
        outs << " " << *p << " ";
    }
    outs << " ]" << endl;
}

template <typename T>
void print(T* a, unsigned int how_many, ostream& outs)
{
    T *start = a;
    T *end = a + how_many;

    outs << "\t" << "[ ";
    for (T *p = start; p != end; p++)
    {
        outs << " " << *p << " ";
    }
    outs << " ]" << endl;
}

template <typename T>
T *search_entry(T *a, int size, const T &find_me)
{
    T *start = a;
    T *end = a + size;

    for (T *p = start; p != end; p++)
    {
        if (*p == find_me)
        {
            return p;
        }
    }

    return nullptr;
}

template <typename T>
int search(T* a, int size, const T& find_me)
{
    T *start = a;
    T *end = a + size;

    for (T *p = start; p != end; p++)
    {
        if (*p == find_me)
        {
            return p - start;                       //p - size gives the index position
        }
    }

    return -1;                                      //returns -1 if nothing is found
}

template <typename T>
void shift_left(T* a, int& size, int shift_here)
{
    T *start = a + shift_here;
    T *last_element = a + size - 1;                 //must be size - 1 since we are changing the next element

    for (T *p = start; p != last_element; p++)
    {
        T *walker = p + 1;
        *p = *walker;
    }
    size--;
}

template <typename T>
void shift_left(T *a, int &size, T *shift_here)
{
    T *start = shift_here;
    T *last_element = a + size - 1;

    for (T *p = start; p != last_element; p++)
    {
        T *walker = p + 1;
        *p = *walker;
    }
    size--;
}

template <typename T>
void shift_right(T *a, int &size, int shift_here)
{
    size++;                                         //increment size first to make sure array has space
    T *start = a + shift_here;
    T *last_element = a + size - 1;

    for (T *p = last_element; p != start; p--)      //start from end of array instead of beginning
    {
        T *walker = p - 1;
        *p = *walker;
    }
}

template <typename T>
void shift_right(T *a, int &size, T* shift_here)
{
    size++;                                         //increment size first to make sure array has space
    T *start = shift_here;
    T *last_element = a + size - 1;

    for (T *p = last_element; p != start; p--)      //start from end of array instead of beginning
    {
        T *walker = p - 1;
        *p = *walker;
    }
}

template <typename T>
void copy_array(T *dest, const T* src, int many_to_copy)
{
    T *start = dest;
    T *end = dest + many_to_copy;

    for (T *p = start; p != end; p++)
    {
        *p = *src;
        src++;  
    }
}

template <typename T>
T* copy_array(const T *src, int size)
{
    T *start = allocate<T>(size);
    T *end = start + size;

    for (T *p = start; p != end; p++)
    {
        *p = *src;
        src++;  
    }

    return start;
}

template <typename T>
string array_string(const T *a, int size)
{
    stringstream s;     //using stringstream was the best solution I found
                        //using to_string() led to char arrays printing junk
                        //plus this felt like the most "templated" solution
    s << "[   ";                                    
    for (int i = 0; i < size; i++)
    {
        s << " " << *a << " ";
        a++;
    }
    s << "   ]";
    
    return s.str();
}

template <typename T>
void init_array(T *a, int size, const T &item)
{
    T *start = a;
    T *end = a + size;

    for (T *p = start; p != end; p++)
    {
        *p = item;
    }
}

#endif

//| 1 | 2 | 3 | 4 | 5 |
//| 1 | 2 | 3 | 4 | 5 |  |
//start           last end=start+5

//1000              1004
//size = 5
//1000 + size - 1