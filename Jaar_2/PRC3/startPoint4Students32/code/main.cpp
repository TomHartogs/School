#include <iostream>

#include "FileStructure.h"
#include "Key.h"

Key* findSmallestAsHead(Key* smallest, Key* current)
{
	static Key* beforeSmallest;
	static Key* previous;
	if(current == NULL)
	{
		beforeSmallest->setNext(smallest->getNext());
		return smallest;
	}
	else
	{
		if(current->getText() < smallest->getText())
		{
			beforeSmallest = previous;
			smallest = current;
		}
		previous = current;
		return findSmallestAsHead(smallest, current->getNext());
	}
}

bool sort(Key* current)
{
	static bool somethingHasChanged;
	static Key* previous;
	if(current == NULL)
	{
		return somethingHasChanged;
	}
	else
	{
		if(current->getText() > current->getNext()->getText())
		{
			Key* temp = current->getNext();
			std::cout << current->getText() << std::endl;
			previous->setNext(temp);
			current->setNext(current->getNext()->getNext());
			temp->setNext(current);
			previous = current;
			somethingChanged = true;
		}
		previous = current;
		return sort(current->getNext()->getNext());
	}
}


int main()
{
    FileStructure f;
    Key head;
    
    //print gibberish
    f.loadFile("data/gibberish.bin", head);
    
    //print sorted
	//f.loadFile("sorted.bin", head);
	
    //head.print();

	Key* newHead = &head;
	newHead = findSmallestAsHead(&head, &head);
	newHead->setNext(&head);
	
	//Same as recursive solution above
	/*Key* previous;
	Key* current = &head;
	Key* newHead = &head;
	newHead->setText(head.getText());
	
	while(current->getNext() != NULL)
	{
		if(current->getText() < newHead->getText())
		{
			//Misschien gevaarlijk?? Checken!!
			previous->setNext(current->getNext());
			newHead = current;
			newHead->setNext(&head);
		}
		previous = current;
		current = current->getNext();
	}
    std::cout << newHead->getText() << std::endl;*/
    
    

    //while(sort(newHead))
   	Key* previous = newHead;
	Key* current = newHead;
	bool somethingChanged = true;
	
    while(somethingChanged)
    {
		somethingChanged = false;
		while(current->getNext() != NULL)
		{
			if(current->getText() > current->getNext()->getText())
			{	
				Key* temp = current->getNext();
				std::cout << current->getText() << std::endl;
				previous->setNext(temp);
				current->setNext(current->getNext()->getNext());
				temp->setNext(current);
				previous = current;
				somethingChanged = true;
			}
			else
			{
				previous = current;
				current = current->getNext();
			}
		}
		previous = newHead;
		current = newHead;
		std::cout << "head: " << current->getText() << std::endl;
		std::cout << "after head: " << current->getNext()->getText() << std::endl;
	}
	
    //Print new keylist
    current = newHead;
    while(current != NULL)
    {
		std::cout << current->getText() << std::endl;
		current = current->getNext();
	}
    
    
    /*Key* current = new Key();
    current->setNext(head.getNext());
    current->setText(head.getText());
    
    //Waarom mag dit wel maar Key* next, temp; next = new Key(); temp = new Key(); niet?
    Key* next = new Key();
    Key* temp = new Key();
    next->setNext(current->getNext());
    next->setText(next->getNext()->getText());
    std::cout << "Head: " << head.getText() << std::endl;
    std::cout << "Current: " << current->getText() << std::endl;
    std::cout << "Next: " << next->getText() << std::endl;
    if(current->getText() > next->getText())
	{
		std::cout << "swapping" << std::endl;
		temp->setNext(head.getNext());
		head.setNext(current->getNext());
		current->setNext(next->getNext());
		next->setNext(temp->getNext());
	}
	std::cout << "Head: " << head.getText() << std::endl;
    std::cout << "Current: " << current->getText() << std::endl;
    std::cout << "Next: " << next->getText() << std::endl;*/
    //if(head.getText() > current->getText())
		//swap head and current
		
	/*while(current->getText().length() == 2)
	{
		//std::cout << current->getText() << std::endl;
		current->setNext(current->getNext()->getNext());
		//current->setText(current->getNext()->getText());
	}*/
    //current.setNext(head.getNext());
    //std::cout << current.getNext() << std::endl;
    //if(current.getText() > current.getNext()->getText())
	//	swap(current, current.getNext());
    
    // save sorted data into a new file called sorted.bin
    //f.saveFile(*smallest->getNext(), "sorted.bin");
    
    return 0;
}
