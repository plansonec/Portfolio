#include "LinkedListNode.hpp"

template <class item_t>
LinkedList<item_t>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <class item_t>
LinkedList<item_t>::~LinkedList()
{
    LinkedListNode<item_t>* current = head;

    while (current != nullptr)
    {
        LinkedListNode<item_t>* nextNode = current->getNext();
        delete current;
        current = nextNode;
    }
}

template <class item_t>
LinkedListNode<item_t>* LinkedList<item_t>::getNode(int index) const
{
    LinkedListNode<item_t>* current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->getNext();
    }
    return current;
}

template <class item_t>
void LinkedList<item_t>::pushFront(const item_t& item)
{
    LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(head, item);
    head = newNode;
    if (size == 0)
    {
        tail = newNode;
    }
    size++;
}

template <class item_t>
void LinkedList<item_t>::pushBack(const item_t& item)
{
    LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(nullptr, item);
    if (size == 0)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->setNext(newNode);
        tail = newNode;
    }
    size++;
}

template <class item_t>
const item_t& LinkedList<item_t>::getFront() const
{
    return head->getItem();
}

template <class item_t>
const item_t& LinkedList<item_t>::getBack() const
{
    return tail->getItem();
}

template <class item_t>
void LinkedList<item_t>::popFront()
{
    LinkedListNode<item_t>* nodeToDelete = head;
    head = head->getNext();
    delete nodeToDelete;
    size--;
    if (size == 0)
    {
        tail = nullptr;
    }
}

template <class item_t>
void LinkedList<item_t>::popBack()
{
    if (size == 1)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        LinkedListNode<item_t>* secondLast = getNode(size - 2);
        delete tail;
        tail = secondLast;
        tail->setNext(nullptr);
    }
    size--;
}

template <class item_t>
void LinkedList<item_t>::insert(int index, const item_t& item)
{
    if (index == 0)
    {
        pushFront(item);
    }
    else if (index == size)
    {
        pushBack(item);
    }
    else
    {
        LinkedListNode<item_t>* prevNode = getNode(index - 1);
        LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(prevNode->getNext(), item);
        prevNode->setNext(newNode);
        size++;
    }
}

template <class item_t>
void LinkedList<item_t>::remove(int index)
{
    if (index == 0)
    {
        popFront();
    }
    else if (index == size - 1)
    {
        popBack();
    }
    else
    {
        LinkedListNode<item_t>* prevNode = getNode(index - 1);
        LinkedListNode<item_t>* nodeToDelete = prevNode->getNext();
        prevNode->setNext(nodeToDelete->getNext());
        delete nodeToDelete;
        size--;
    }
}

template <class item_t>
const item_t& LinkedList<item_t>::getItem(int index) const
{
    LinkedListNode<item_t>* node = getNode(index);
    return node->getItem();
}

template <class item_t>
void LinkedList<item_t>::setItem(int index, const item_t& item)
{
    LinkedListNode<item_t>* node = getNode(index);
    node->setItem(item);
}

template <class item_t>
int LinkedList<item_t>::getSize() const
{
    return size;
}

template <class item_t>
bool LinkedList<item_t>::isEmpty() const
{
    return size == 0;
}