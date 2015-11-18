all: exercise1 exercise2

exercise1: Makefile exercise1.c
	@gcc -ggdb -Wall -Werror -O0 $@.c -o $@

exercise2: Makefile exercise2.c
	@gcc -ggdb -O0 $@.c -o $@ 2> /dev/null

clean:
	@rm -rf exercise[12] exercise[12].dSYM
