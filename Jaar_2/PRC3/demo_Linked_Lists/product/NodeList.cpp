#include "NodeList.h"
#include <iostream>

NodeList::NodeList(void)
    : head(NULL)
{
}

NodeList::~NodeList(void)
{
    while (head != NULL)
    {
        Node* temp = head;
        head = head->getNext();
        delete temp;
        temp = NULL;
    }
}

void NodeList::show() const
{
    Node* temp = head;
    std::cout << "current nodelist: ";
    while (temp != NULL)
    {
        std::cout << temp->getValue() << " -> ";
        temp = temp->getNext();
    }
    std::cout << "NULL" << std::endl;
}

Node* NodeList::getHead(void)
{
    return head;
}

Node* NodeList::getNodeByNr(int nr)
{
    if (nr < 0 || head == NULL)
    {
        return NULL;
    }

    Node* p = head;
    for (int i = 0; (i < nr) && (p != NULL); i++)
    {
        p = p->getNext();
    }
    return p;
}

bool NodeList::insertAfter(Node* position, Node* newNode)
{
    if (newNode == NULL || position == NULL)
    {
        return false;
    }

    // look for position in list
    Node* temp = head;
    while (temp != position && temp != NULL)
    {
        temp = temp->getNext();
    }

    if (temp != NULL)
    {
        newNode->setNext(position->getNext());
        position->setNext(newNode);
        return true;
    }

    return false;
}

bool NodeList::insertBefore(Node* position, Node* newNode)
{
    if (newNode == NULL)
    {
        return false;
    }
    
    if (head == NULL)
    {
        if (position == NULL)
        {
            newNode->setNext(head);
            head = newNode;
            return true;
        }
        return false;
    }

    if (position == NULL)
    {
        return false;
    }

    Node* temp = head;
    while (temp->getNext() != position && temp->getNext() != NULL)
    {
        temp = temp->getNext();
    }

    if (temp->getNext() == position)
    {
        newNode->setNext(position);
        temp->setNext(newNode);
        return true;
    }

    return false;
}

bool NodeList::removeNode(Node* nodeToRemove)
{
    if (nodeToRemove == NULL)
    {
        return false;
    }

    if (nodeToRemove == head)
    {
        Node* temp = head;
        head = head->getNext();
        delete temp;
        temp = NULL;
        return true;
    }

    Node* temp = head;
    while (temp->getNext() != nodeToRemove && temp != NULL)
    {
        temp = temp->getNext();
    }
    if (temp != NULL)
    {
        temp->setNext(nodeToRemove->getNext());
        // nodeToRemove has been "cut out of the list"
        delete nodeToRemove;
        nodeToRemove = NULL;
        return true;
    }

    return false;
}
