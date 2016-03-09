#pragma once

#include <cstddef>

const int MaxNrElems = 10;

template <typename T>
class Stack
{
	private:
	T elemens[MaxNrElems];
	int nrElems;
	
	public:
	Stack();
	void push(const T&);
	T pop();
	int GetNrElems();
	bool isEmpty() const;
	bool isFull() const;
};

template <typename T>
Stack<T>::Stack()
	: nrElems(0)
{
}

template <typename T>
void Stack<T>::push(const T& value)
{
	if(!isFull())
	{
		elemens[nrElems] = value;
		nrElems++;
	}
}

template <typename T>
T Stack<T>::pop()
{
	if(!isEmpty())
	{
		nrElems--;
		return elemens[nrElems];
	}
	return (T)NULL;
}

template <typename T>
int Stack<T>::GetNrElems()
{
	return nrElems;
}

template <typename T>
bool Stack<T>::isEmpty() const
{
	return nrElems == 0 ? true : false;
}

template <typename T>
bool Stack<T>::isFull() const
{
	return nrElems == MaxNrElems ? true : false;
}

