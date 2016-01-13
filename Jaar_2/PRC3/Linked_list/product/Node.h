/*
 * Node.h
 *
 *  Created on: Sep 25, 2013
 *  Author: P. Lambooij
 */

#ifndef NODE_H
#define NODE_H

class Node
{
  private:
    int value;
    Node* next;

  public:
	Node(void);
	/*	pre :
		post: object Node has next == NULL and value == 0
	*/

    Node(int value);
	/*	pre :
		post: object Node has next == NULL and value == value
	*/

	virtual ~Node(void);
    /*  pre :
        post: object Node was deleted
    */

    int getValue(void) const;
	/*	pre :
		post: return value
	*/

    void setValue(int value);
	/*	pre :
		post: value == value
	*/

    Node* getNext(void);
	/*	pre : -
		post: return next
	*/

    void setNext(Node* next);
	/*	pre : -
		post: next == next
	*/

};

#endif /* NODE_H_ */
