/*
 *  main.cpp
 *
 *  Created on: Sep 25, 2013
 *  Author: P. Lambooij
 */

#include <string>
#include <iostream>
using namespace std;

#include "NodeList.h"
#include "Node.h"

int main()
{
  std::cout << "Illustration Linked List Operations" << std::endl;

  NodeList * MyNodeList = new NodeList();
  Node * newNode;
  Node * position;

  MyNodeList->show();

  newNode = new Node(10);
  MyNodeList->insertBefore(NULL, newNode);
  MyNodeList->show();

  newNode = new Node(20);
  position = MyNodeList->getNodeByNr(0);
  MyNodeList->insertAfter(position, newNode);
  MyNodeList->show();

  newNode = new Node(30);
  position = MyNodeList->getNodeByNr(1);
  MyNodeList->insertBefore(position, newNode);
  MyNodeList->show();

  newNode = new Node(40);
  position = MyNodeList->getNodeByNr(2);
  MyNodeList->insertAfter(position, newNode);
  MyNodeList->show();

  position = MyNodeList->getNodeByNr(1);
  MyNodeList->removeNode(position);
  MyNodeList->show();

  std::cout << std::endl << "deleting NodeList" << std::endl;;
  delete MyNodeList;
}
