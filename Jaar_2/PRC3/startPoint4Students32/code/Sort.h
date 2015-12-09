#pragma once

template <typename T>
T* findSmallest(T* smallest, T* current)
{
	static T* beforeSmallest;
	static T* previous;
	if(current == NULL)
	{
		if(beforeSmallest != NULL)
			beforeSmallest->setNext(smallest->getNext());
		beforeSmallest = NULL;
		previous = NULL;
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
