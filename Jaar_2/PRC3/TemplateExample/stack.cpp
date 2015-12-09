#include "stack.h"
#include <stdio.h>
#include <string>
#include <iostream>

template <typename T>
void print(T value)
{
	std::cout << value << std::endl;
}

int main()
{
	Stack<int> _intStack;
	_intStack.push(10);
	_intStack.push(15);
	print(_intStack.pop());
	print(_intStack.pop());
	
	Stack<std::string> _stringStack;
	_stringStack.push("jan");
	_stringStack.push("henk");
	print(_stringStack.pop());
	print(_stringStack.pop());

	return 0;
}
