#ifndef DOUBLYLINKEDLIST_H_INCLUDED
#define DOUBLYLINKEDLIST_H_INCLUDED

#include <iostream>

using namespace std;

template <typename T>
struct Node
{
    T elem;
    Node<T> *next;
    Node<T> *prev;
};

template <typename T>
struct DoublyLinkedList
{
    int amount;
    Node<T> *start;
};

template <typename T>
void create(DoublyLinkedList<T> &list)
{
    list.amount = 0;
    list.start = NULL;
}

template <typename T>
void destroy(DoublyLinkedList<T> &list)
{
    Node<T> *p;
    while (list.start != NULL)
    {
        p = list.start;
        list.start = list.start->next;
        delete p;
    }

    list.amount = 0;
}

template <typename T>
bool isEmpty(DoublyLinkedList<T> list)
{
    return list.amount == 0;
}

template <typename T>
bool hasIn(DoublyLinkedList<T> &list, T element)
{
    Node<T> *p = list.start;
    while (p != NULL)
    {
        if (p->elem == element)
            return true;
        p = p->next;
    }
    return false;
}

template <typename T>
void insert(DoublyLinkedList<T> &list, T element, int pos)
{
    if (pos < 1 || pos > list.amount + 1)
        throw "Invalid position!";

    Node<T> *newElement = new Node<T>;
    newElement->elem = element;
    newElement->next = NULL;
    newElement->prev = NULL;

    if (list.start == NULL)
        list.start = newElement;
    else if (pos == 1)
    {
        newElement->next = list.start;
        list.start->prev = newElement;
        list.start = newElement;
    }
    else
    {
        Node<T> *current = list.start;
        for (int i = 1; i < pos - 1; i++)
            current = current->next;

        newElement->next = current->next;
        newElement->prev = current;

        if (current->next != NULL)
            current->next->prev = newElement;

        current->next = newElement;
    }

    list.amount++;
}

template <typename T>
void remove(DoublyLinkedList<T> &list, T element, int pos)
{
    if(list.amount==0)
        throw "Underflow!";
    if(pos < 1 || pos > list.amount)
        throw "Invalid position!";
    //Continue this later
}

#endif