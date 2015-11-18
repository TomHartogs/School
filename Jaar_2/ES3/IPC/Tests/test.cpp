#include <iostream>

int main()
{
	std::string	name;
	int 	age;
	std::cout	<< "Whats your name?\n";
	std::getline (std::cin, name);
	std::cout 	<< "How old are you?\n";
	std::cin 	>> age;
	std::cout 	<< "Your name is: " << name << std::endl
			<< "You are: " << age << " years old.\n";
			return 0;
}
