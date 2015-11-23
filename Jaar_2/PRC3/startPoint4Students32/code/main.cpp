#include <iostream>

#include "FileStructure.h"
#include "Key.h"

template <typename T>
T* findSmallest(T* smallest, T* current)
{
	static T* beforeSmallest;
	static T* previous;
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
		return findSmallest(smallest, current->getNext());
	}
}

template <typename T>
void swapWithNextIfItsBigger(T* current, bool* somethingHasChanged)
{
	static T* previous;
	if(current->getNext() != NULL)
	{
		if(current->getText() > current->getNext()->getText())
		{
			T* tempNext = current->getNext();
			previous->setNext(tempNext);
			current->setNext(current->getNext()->getNext());
			tempNext->setNext(current);
			previous = tempNext;
			*somethingHasChanged = true;
		}
		else
		{
			previous = current;
			current = current->getNext();
		}
		swapWithNextIfItsBigger(current, somethingHasChanged);
	}
}


int main()
{
    FileStructure f;
    Key head;
   
    f.loadFile("data/gibberish.bin", head);
	
    //head.print();

	Key* newHead = &head;
	newHead = findSmallest(newHead, newHead);
	newHead->setNext(&head);   
    
	bool somethingHasChanged = true;
    while(somethingHasChanged)
    {    
		somethingHasChanged = false;
		swapWithNextIfItsBigger(newHead, &somethingHasChanged);
	}
	
	Key* current = newHead;
	while(current != NULL)
	{
		Value* smallestValue = current->getValuePtr();
		smallestValue = findSmallest(current->getValuePtr(), current->getValuePtr());
		current->setValuePtr(smallestValue);
		
		somethingHasChanged = true;
		while(somethingHasChanged)
		{    
			somethingHasChanged = false;
			swapWithNextIfItsBigger(current->getValuePtr(), &somethingHasChanged);
		}
		
		current = current->getNext();
	}
	
    // save sorted data into a new file called sorted.bin
    f.saveFile(*newHead, "sorted.bin");
    
    return 0;
}

//Functions before rewriting to recursive

	/*Same as recursive solution above
	Key* previous;
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
    std::cout << newHead->getText() << std::endl;

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
				Key* tempNext = current->getNext();
				std::cout << "Previous: " << previous->getText() << std::endl;
				std::cout << "current: " << current->getText() << std::endl;
				std::cout << "Next: " << tempNext->getText() << std::endl;
				std::cout << std::endl;
				previous->setNext(tempNext);
				current->setNext(current->getNext()->getNext());
				tempNext->setNext(current);
				previous = tempNext;
				somethingChanged = true;
			}
			else
			{
				previous = current;
				current = current->getNext();
				std::cout << "bigger text :" << current->getText() << std::endl;
			}
		}
		std::cout << "Last key: " << current->getText() << std::endl;
		previous = newHead;
		current = newHead;
		//std::cout << "head: " << current->getText() << std::endl;
		//std::cout << "after head: " << current->getNext()->getText() << std::endl;
	}
	
    //Print new keylist
    Key* current = newHead;
    while(current != NULL)
    {
		std::cout << current->getText() << std::endl;
		current = current->getNext();
	}
    
    
    Key* current = new Key();
    current->setNext(head.getNext());
    current->setText(head.getText());
*/
