#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "../node/node.h"

using namespace std;

//Linked List General Functions:
template <typename T>
void _print_list(node<T> *head, ostream &outs = cout);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head, node<T> *true_head, ostream &outs = cout);

//return ptr to key or NULL
template <typename T>
node<T> *_search_list(node<T> *head,
                      T key);

template <typename T>
node<T> *_insert_head(node<T> *&head,
                      T insert_this);

//insert after ptr
template <typename T>
node<T> *_insert_after(node<T> *&head,
                       node<T> *after_this,
                       T insert_this);

//insert before ptr
template <typename T>
node<T> *_insert_before(node<T> *&head,
                        node<T> *before_this,
                        T insert_this);

//ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *head,
                        node<T> *prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T> *&head,
               node<T> *delete_this);

//duplicate the list...
template <typename T>
node<T> *_copy_list(node<T> *head);

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

//delete all the nodes
template <typename T>
void _clear_list(node<T> *&head);

//_item at this position
template <typename T>
T &_at(node<T> *head, int pos);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                              Sorted List Routines.
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
node<T> *_insert_sorted(node<T> *&head,
                        T item,
                        bool ascending = true);

//insert or add if a dup
template <typename T>
node<T> *_insert_sorted_and_add(node<T> *&head,
                                T item,
                                bool ascending = true);
//node after which this item goes order: 0 ascending
template <typename T>
node<T> *_where_this_goes(node<T> *head,
                          T item,
                          bool ascending = true);
//Last Node in the list
template <typename T>
node<T> *_last_node(node<T> *head);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                              DEFINITIONS
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
void _print_list(node<T> *head, ostream &outs)
{
    //uses walker that starts at head pointer
    //walker gets set to the _next pointer of the node it points at each iteration
    //loops until walker reaches the end (nullptr)
    //uses overloaded node operater << to print _item of each node

    outs << "H->";
    for (node<T> *walker = head; walker != nullptr; walker = walker->next)
    {
        outs << *walker << "->";
    }
    outs << "|||";
}

template <typename T>
void _print_list_backwards(node<T> *head, node<T> *true_head, ostream &outs)
{
    //true_head is passed in to keep track of the original head of the list
    //only used to print the final <-H & probably unnecessary, but done for consistency among print functions

    //first sets temp pointer to head
    //if the temp pointer is nullptr (indicating the end of the list), ||| is printed and the function returns
    //otherwise, the function is recursively called from within itself, passing in temp->next as the new head
    //true_head is also passed in, so that <-H is printed after the first node (last to be printed) is printed

    node<T> *temp = head;

    if (temp == nullptr)
    {
        outs << "|||";
        return;
    }

    _print_list_backwards(temp->next, true_head);
    outs << "<-" << *temp;

    if (temp == true_head)
    {
        outs << "<-H";
    }
}

template <typename T>
node<T> *_search_list(node<T> *head, T key)
{
    //uses walker that starts at head pointer
    //walker gets set to the _next pointer of the node it points at each iteration
    //loops until walker reaches the end (nullptr)
    //if the _item of the node that walker points at == key, walker is returned (address of the node)
    //otherwise, nullptr is returned indicating that the key was not found

    for (node<T> *walker = head; walker != nullptr; walker = walker->next)
    {
        if (walker->_item == key)
        {
            return walker;
        }
    }

    return nullptr;
}

template <typename T>
node<T> *_insert_head(node<T> *&head, T insert_this)
{
    //create a temp node using new
    //point the temp node to the same thing head points to
    //point head to the temp node
    //return head now that it points to the new node

    node<T> *temp = new node<T>(insert_this);
    temp->next = head;
    head = temp;

    return head;
}

template <typename T>
node<T> *_insert_after(node<T> *&head, node<T> *after_this, T insert_this)
{
    //special case to after_this is nullptr (indicating empty list or that item should be inserted before head), if it is, _insert_head is called
    //otherwise, a temp node is created using new
    //temp->_next is set to after_this->_next (temp->_next now points to the node after after_this)
    //after_this->_next is set to point to temp
    //the address of the newly inserted node is returned

    if (after_this == nullptr)
    {
        return _insert_head(head, insert_this);
    }
    else
    {
        node<T> *temp = new node<T>(insert_this);
        temp->next = after_this->next;
        after_this->next = temp;

        return temp;
    }
}

template <typename T>
node<T> *_insert_before(node<T> *&head, node<T> *before_this, T insert_this)
{
    //special case to check if _insert_before is called on head pointer, if it is, _insert_head is called
    //if before_this has the address that head points to (the first node), then _insert_head is called
    //otherwise, a temp node is created using new
    //temp->_next is set to point to the node before_this
    //the node originally previous to before_this is set to point to the new temp node
    //the address of the newly inserted node is returned

    if (before_this == head)
    {
        return _insert_head(head, insert_this);
    }
    else
    {
        node<T> *temp = new node<T>(insert_this);
        temp->next = before_this;
        _previous_node(head, before_this)->next = temp;

        return temp;
    }
}

template <typename T>
node<T> *_previous_node(node<T> *head, node<T> *prev_to_this)
{
    //special case to check if prev_to_this is the first node, nullptr is returned if so
    //assert to check if prev_to_this is nullptr
    //assert occurs after special case because prev_to_this can be nullptr but only if the list is empty
    //uses walker that starts at head pointer
    //walker gets set to the _next pointer of the node it points at each iteration
    //loops until walker reaches the end (nullptr)
    //if the _next pointer of the node that the walker points to has the address of prev_to_this, walker is returned (address of previous node)
    //assert statement is called if prev_to_this is not found on the list

    if (prev_to_this == head)
    {
        return nullptr;
    }
    else
    {
        assert(prev_to_this != nullptr && "prev_to_this cannot be nullptr");

        for (node<T> *walker = head; walker != nullptr; walker = walker->next)
        {
            if (walker->next == prev_to_this)
            {
                return walker;
            }
        }

        assert(false && "prev_to_this was not found on the list");
    }
}

template <typename T>
T _delete_node(node<T> *&head, node<T> *delete_this)
{
    //assert that delete_this is not nullptr
    //if delete_this is the first node of the list, the head pointer is set to delete_this->_next
    //otherwise, the previous node's _next pointer is set to delete_this->_next
    //an item of type ITEM_TYPE is created and set to delete_this->_item
    //delete_this is deleted in the last step before returning item

    assert(delete_this != nullptr && "delete_this cannot be nullptr");

    if (delete_this == head)
    {
        head = head->next;
    }
    else
    {
        _previous_node(head, delete_this)->next = delete_this->next;
    }

    T item = delete_this->_item;
    delete delete_this;
    delete_this = nullptr;

    return item;
}

template <typename T>
node<T> *_copy_list(node<T> *head)
{
    //special case to check if src list is empty, if so, dest_head is set to nullptr and empty list is returned
    //dest_head is created and initialized to a node that contains the item in src head
    //dest_walker is created and set to dest_head
    //uses src_walker that initially starts at src head->_next (second node of the source list)
    //src_walker gets set to the _next pointer of the node it points with each iteration
    //dest walker gets set to the _next pointer of the node it points with each iteration
    //_insert_after is called to insert a copy of src_walker->_item into the destination node each iteration
    //loops until walker reaches the end (nullptr)

    node<T> *dest_head;

    if (head == nullptr)
    {
        dest_head = nullptr;
        return dest_head;
    }
    else
    {
        dest_head = new node<T>(head->_item);
        node<T> *dest_walker = dest_head;

        for (node<T> *src_walker = head->next; src_walker != nullptr; src_walker = src_walker->next)
        {
            _insert_after(dest_head, dest_walker, src_walker->_item);
            dest_walker = dest_walker->next;
        }

        return dest_head;
    }
}

template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
    //special case to check if src list is empty, if so, dest is set to nullptr and empty list is returned
    //dest is initialized to a node that contains the item in src head
    //dest_walker is created and set to dest
    //uses src_walker that initially starts at src head->_next (second node of the source list)
    //src_walker gets set to the _next pointer of the node it points with each iteration
    //dest walker gets set to the _next pointer of the node it points with each iteration
    //_insert_after is called to insert a copy of src_walker->_item into the destination node each iteration
    //loops until walker reaches the end (nullptr)

    if (src == nullptr)
    {
        dest = nullptr;
        return dest;
    }
    else
    {
        dest = new node<T>(src->_item);
        node<T> *dest_walker = dest;

        for (node<T> *src_walker = src->next; src_walker != nullptr; src_walker = src_walker->next)
        {
            _insert_after(dest, dest_walker, src_walker->_item);
            dest_walker = dest_walker->next;
        }

        return dest_walker;
    }
}

template <typename T>
void _clear_list(node<T> *&head)
{
    while (head != nullptr)
    {
        _delete_node(head, head);
    }
}

template <typename T>
T &_at(node<T> *head, int pos)
{
    //assert to check whether index is valid
    //uses for loop that runs while int i is less than int pos and increments i each time
    //walker is initialized to point to head node
    //walker is set to walker->_next each loop, essentially moving to the next index position
    //the item at the node that walker points to is returned

    assert(pos >= 0 && "index position cannot be negative");

    node<T> *walker = head;

    for (int i = 0; i < pos; i++)
    {
        walker = walker->next;
    }

    return walker->_item;
}

template <typename T>
node<T> *_insert_sorted(node<T> *&head, T item, bool ascending)
{
    //_insert_after gets called and inserts using the node pointer returned by _where_this_goes
    //if _where_this_goes returns nullptr, _insert_after takes care of it and calls _insert_head

    return _insert_after(head, _where_this_goes(head, item, ascending), item);
}

template <typename T>
node<T> *_insert_sorted_and_add(node<T> *&head, T item, bool ascending)
{
    //special case to check if head == nullptr (indicating empty list)
    //if it is, then _insert_head is called

    //otherwise, check is done to see if _where_this_goes returned nullptr (indicating to insert at front of list)
    //if it did, then a check is performed to see if the item stored at the head node is equal to the item passed in
    //if the items are equal, the item passed in is added to the item at the head node and head is returned

    //otherwise, a check is done to see if _where_this_goes returned the last node in the list
    //if it did NOT, then another check is done to see if the item passed in is a duplicate
    //if it is, then it is added to the existing item at the node returned by _where_this_goes

    //otherwise, _insert_sorted is called by default

    node<T> *insert_here = _where_this_goes(head, item, ascending);

    if (head == nullptr)
    {
        return _insert_head(head, item);
    }
    else if (insert_here == nullptr)
    {
        if (item == head->_item)
        {
            head->_item = head->_item + item;
            return head;
        }
    }
    else if (insert_here->next != nullptr)
    {
        if (item == insert_here->next->_item)
        {
            insert_here->next->_item = insert_here->next->_item + item;
            return insert_here->next;
        }
    }

    return _insert_sorted(head, item, ascending);
}

template <typename T>
node<T> *_where_this_goes(node<T> *head, T item, bool ascending)
{
    //special case to check if head == nullptr (indicating empty list)
    //if it is, the nullptr is returned (indicating that the item should be inserted at the head)
    //otherwise, two pointers, walker and follower, are initialized to the head pointer

    //a check is performed to see if the list is ascending or descending
    //a check is performed to see if the item is greater than the follower node item and less than or equal to the walker item
    //if this condition is true, then the follower is returned (address after which the item should be inserted)
    //in a while loop where the condition is walker->next != nullptr, walker is first set to walker->next
    //because of this, walker will always be a step ahead of follower until the final loop

    //the checks for a descending list are almost identical

    //upon the termination condition of the while loop, both walker and follower will be at the same address, meaning walker will never be nullptr

    if (head == nullptr)
    {
        return nullptr;
    }

    node<T> *walker = head;
    node<T> *follower = head;

    if (ascending)
    {
        if (item <= head->_item)
        {
            return nullptr;
        }

        while (walker->next != nullptr)
        {
            walker = walker->next;

            if (item > follower->_item && item <= walker->_item)
            {
                return follower;
            }

            follower = follower->next;
        }
    }
    else
    {
        if (item >= head->_item)
        {
            return nullptr;
        }

        while (walker->next != nullptr)
        {
            walker = walker->next;

            if (item < follower->_item && item >= walker->_item)
            {
                return follower;
            }

            follower = follower->next;
        }
    }

    return follower;
}

template <typename T>
node<T> *_last_node(node<T> *head)
{
    //uses walker that starts at head pointer
    //walker gets set to the _next pointer of the node it points at each iteration
    //loops until walker reaches the end (nullptr)
    //if the _next pointer of the node that the walker points to is nullptr, the walker is returned (address of last node)
    //nullptr is returned by default, signalling an empty list

    node<T> *walker = head;
    while (walker->next != nullptr)
    {
        walker = walker->next;
    }
    return walker;
}

#endif