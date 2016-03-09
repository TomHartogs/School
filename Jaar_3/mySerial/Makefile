CFLAGS=-Wall -Werror -pedantic -ggdb -O0 -std=c++98 -Iproduct

MYSERIALTEST_SOURCE=test/mySerialTest.cpp

TEST_LIBS=-lgtest -lgtest_main -lpthread

GCC=g++

.phony: all clean Execute

all: MySerialTest Execute clean

MySerialTest: $(MYSERIALTEST_SOURCE) Makefile product/*
	$(GCC) $(CFLAGS) $(MYSERIALTEST_SOURCE) $(TEST_LIBS) -o $@
	
Execute: MySerialTest
	./MySerialTest

clean:
	@rm -rf MySerialTest
