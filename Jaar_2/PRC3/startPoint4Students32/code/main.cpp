#include "FileStructure.h"
#include "Key.h"
#include "Sort.h"

int main()
{
    FileStructure f;
    Key* head = new Key();
   
    f.loadFile("data/gibberish.bin", *head);

	Key* tempNext = head;
	head = findSmallest(head, head);
	head->setNext(tempNext);   
    
	bool somethingHasChanged = true;
    while(somethingHasChanged)
    {    
		somethingHasChanged = false;
		swapWithNextIfItsBigger(head, &somethingHasChanged);
	}
	
	Key* current = head;
	while(current != NULL)
	{
		Value* temp = current->getValuePtr();
		Value* smallestValue = current->getValuePtr();
		smallestValue = findSmallest(current->getValuePtr(), current->getValuePtr());
		if(temp != smallestValue)
			smallestValue->setNext(temp);
		current->setValuePtr(smallestValue);
		somethingHasChanged = true;
		while(somethingHasChanged)
		{    
			somethingHasChanged = false;
			swapWithNextIfItsBigger(current->getValuePtr(), &somethingHasChanged);
		}
		
		current = current->getNext();
	}
	
	//f.saveFile(*head, "sorted.bin");

	delete head;
	
    return 0;
}
