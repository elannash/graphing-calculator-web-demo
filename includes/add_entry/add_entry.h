#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H

#include <iostream>
#include "../array_functions/array_functions.h"

using namespace std;

template <typename T>
T *add_entry(T *list, const T &new_entry, int &size, int &capacity);

template <typename T>
T *remove_entry(T *list, const T &delete_me, int &size, int &capacity);

template <typename T>
T *remove_last_entry(T *list, T &popped, int &size, int &capacity);

template <typename T>
T *insert_entry(T *list, const T &insert_this, int insert_here, int &size, int &capacity);

template <typename T>
T *erase_entry(T *list, int index, int &size, int &capacity);

/*=============================================================================================*/

template <typename T>
T *add_entry(T *list, const T &new_entry, int &size, int &capacity)
{
    if (size >= capacity)
    {
        capacity *= 2;
        list = reallocate(list, size, capacity);
    }

    size++;                            //increment size
    T *last_element = list + size - 1; //set end of list to one past end of array
    *last_element = new_entry;         //value at end gets set to new_entry

    return list;
}

template <typename T>
T *remove_entry(T *list, const T &delete_me, int &size, int &capacity)
{
    T *shift_here = search_entry(list, size, delete_me); //set pointer shift_here to point to where delete_me is found
    shift_left(list, size, shift_here);                  //call shift_left at shift_here

    if (size <= capacity / 4)
    {
        capacity /= 2;
        list = reallocate(list, size, capacity);
    }
    
    return list;
}

template <typename T>
T *remove_last_entry(T *list, T &popped, int &size, int &capacity)
{
    T *last_entry = list + size - 1;    //last_entry points to last element of array
    popped = *last_entry;               //set popped equal to whatever is in last cell
    shift_left(list, size, last_entry); //call shift_left at last_entry

    if (size <= capacity / 4)
    {
        capacity /= 2;
        list = reallocate(list, size, capacity);
    }

    return list;
}

template <typename T>
T *insert_entry(T *list, const T &insert_this, int insert_here, int &size, int &capacity)
{
    if (size >= capacity)
    {
        capacity *= 2;
        list = reallocate(list, size, capacity);
    }

    shift_right(list, size, insert_here);
    T *insert_here_ptr = list + insert_here; //creating pointer to point to a[insert_here]
    *insert_here_ptr = insert_this;

    return list;
}

template <typename T>
T *erase_entry(T *list, int index, int &size, int &capacity)
{
    T *shift_here = list + index;           //creating pointer to point to a[index]
    shift_left(list, size, shift_here);

    if (size <= capacity / 4)
    {
        capacity /= 2;
        list = reallocate(list, size, capacity);
    }

    return list;
}

#endif