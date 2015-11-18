#!/bin/bash
echo "I'll be testing" $1 "for you"

if [ ! -f $1 ]; then
	echo "ERROR: File not found."
	exit
fi

echo "Running GCC"

if gcc --std=c++98 -c "$1" -o /tmp/test.o; then
	echo ""
	echo -e "\e[32mGCC Has compiled your file succesfully!\e[39m"
else
	echo ""
	echo -e "\e[31mGCC Failed to compile. The error have been listed above\e[39m"
fi
