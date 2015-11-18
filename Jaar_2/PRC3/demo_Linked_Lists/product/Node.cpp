#include "Node.h"
#include <iostream>

Node::Node(void)
    : value(0)
    , next(NULL)
{
}

Node::Node(int value)
    : value(value)
    , next(NULL)
{
}

Node::~Node(void)
{
    std::cout << "deleted Node with value: " << value << std::endl;
}

int Node::getValue(void) const
{
    return value;
}

void Node::setValue(int value)
{
    this->value = value;
}

Node* Node::getNext(void)
{
    return next;
}

void Node::setNext(Node* next)
{
    this->next = next;
}
