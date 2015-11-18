/*
 * NodeList.h
 *
 *  Created on: Sep 25, 2013
 *  Author: P. Lambooij
 */

#ifndef NODELIST_H
#define NODELIST_H

#include "Node.h"

class NodeList
{
  private:
    Node* head;

  public:
	NodeList(void);
	/*	pre :
		post: object NodeList has head == NULL
	*/

	virtual ~NodeList(void);
    /*  pre : -
        post: object Node was deleted
    */

    void show() const;
    /*  pre : -
        post: all values of nodes in the list have been printed to cout
    */

    Node* getHead(void);
	/*	pre : -
		post: return head of list
	*/

    Node* getNodeByNr(int n);
	/*	pre : -
		post: IF (0 <= n < nr of nodes in the list) THEN return a pointer to the n-th node in the list ELSE return NULL
	*/

    bool insertAfter(Node* position, Node* newNode);
	/*	pre : -
		post: IF position points at one of the Nodes in the linked list
		      THEN insert newNode after that position and return true
		      ELSE do nothing and return false
	*/

    bool insertBefore(Node* position, Node* newNode);
	/*	pre : -
		post: IF position points at one of the Nodes in the linked list
		      THEN insert newNode after that position and return true
		      ELSE do nothing and return false
    */

    bool removeNode(Node* nodeToRemove);
	/*	pre : -
		post: IF nodeToRemove points at one of the Nodes in the linked list
		      THEN remove that node and return true
		      ELSE do nothing and return false
	*/
};

#endif /* NODELIST_H_ */
