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
    Node<T> *end;
};

// Inicializa a lista vazia.
template <typename T>
void create(DoublyLinkedList<T> &list)
{
    list.amount = 0;
    list.start = NULL;
    list.end = NULL;
}

// Libera todos os nos e reseta os metadados da lista.
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
    list.end = NULL;
}

// Retorna true quando a lista nao possui elementos.
template <typename T>
bool isEmpty(const DoublyLinkedList<T> &list)
{
    return list.amount == 0;
}

// Verifica se um elemento existe na lista.
template <typename T>
bool hasIn(const DoublyLinkedList<T>& list, const T& element)
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

// Insere um item na posicao informada.
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
    {
        list.start = newElement;
        list.end = newElement;
    }
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
        else
            list.end = newElement;

        current->next = newElement;
    }

    list.amount++;
}

// Remove o item da posicao informada.
template <typename T>
void remove(DoublyLinkedList<T> &list, int pos)
{
    if(list.amount==0)
        throw "Underflow!";
    if(pos < 1 || pos > list.amount)
        throw "Invalid position!";
    Node<T>* toDelete = list.start;

    for (int i = 1; i < pos; i++) {
        toDelete = toDelete->next;
    }

    if (toDelete->prev != NULL)
        toDelete->prev->next = toDelete->next;
    else
        list.start = toDelete->next;

    if (toDelete->next != NULL)
        toDelete->next->prev = toDelete->prev;
    else
        list.end = toDelete->prev;

    delete toDelete;
    list.amount--;
}

#endif