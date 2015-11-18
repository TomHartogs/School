#include "ScanList.h"

// Scan* Scanlist::GetPreviousScan(Scan* wantedScan) toevoegen?? Voorkomt code duplicatie

ScanList::ScanList(void)
	:head(0)
{}

ScanList::~ScanList()
{
	Scan* current;
	Scan* previous;
	current = head;
	while(current != 0)
	{
		previous = current;
		current = current->getNext();
		delete previous;
	}
	delete current;
	head = 0;
}

void ScanList::addScan (int serialNumber) //Beter tegelijk serial nummers vergelijken of eerst enkel zoeken of hij in de lijst staat?
{
	if(head == 0) //empty list
	{
		Scan* newScan = new Scan(serialNumber);
		newScan->setNext(0);
		head = newScan;
		return;
	}
	
	Scan* current = head;
	Scan* previous = head;
	if(current->getSerialNumber() == serialNumber) //Check if first item isn't the same (kan beter anders?)
	{
		current->recycle();
		return;
	}
	
	Scan* newScan = new Scan(serialNumber);
	newScan->setNext(0);
	
	while(current->getNext() != 0 || current->getSerialNumber() > serialNumber) //Search entire list
	{
		if(current->getSerialNumber() == serialNumber)//Check if current items serial number equals our serial number
		{
			current->recycle();
			return;
		}
		else if(current->getSerialNumber() < serialNumber)
		{
			previous = current;
		}
		else if(current->getSerialNumber() > serialNumber)
		{
			newScan->setNext(current);
			if(previous != current)
				previous->setNext(newScan);
			else
				head = newScan;
			return;
		}
		current = current->getNext();
	}
	if(current->getSerialNumber() == serialNumber)
		current->recycle();
	else
		current->setNext(newScan);
}

Scan* ScanList::getScanByNr(int position)
{
	if(head == 0)
		return 0;
	if(position == 0)
		return head;
	Scan* temp = head;
	int positionCount = 0;
	while(temp->getNext() != 0 || positionCount == position)
	{
		if(positionCount == position)
			return temp;
		temp = temp->getNext();
		positionCount++;
	}
	return 0;
}

bool ScanList::removeScan (int serialNumber)
{
	if(head == 0)
		return false;
	Scan* currentScan;
	Scan* previousScan;
	currentScan = head;
	previousScan = 0;
	
	while(currentScan->getNext() != 0 || currentScan->getSerialNumber() == serialNumber)
	{
		if(currentScan->getSerialNumber() == serialNumber)
		{
			if(previousScan == 0)
				head = currentScan->getNext();
			else
				previousScan->setNext(currentScan->getNext());
			delete currentScan;
			return true;
		}
		previousScan = currentScan;
		currentScan = currentScan->getNext();
	}
	return false;		
}

int ScanList::getTimesRecycled(int serialNumber)
{
	if(head == 0)
		return 0;
		
	Scan* temp = head;
	while(temp->getSerialNumber() != serialNumber)
	{
		temp = temp->getNext();
		if(temp == 0)
			return 0;
	}
	return temp->getTimesRecycled();
}
