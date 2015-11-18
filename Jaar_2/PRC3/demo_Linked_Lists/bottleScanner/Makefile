CFLAGS=-Wall -Werror -pedantic -ggdb -O0 -std=c++98 -Iproduct
CFLAGS_NORMAL=$(CFLAGS) -Iproduct

SCANLIST_SOURCE=product/ScanList.cpp
SCAN_SOURCE=product/Scan.cpp

SCANLISTTEST_SOURCES=test/ScanListTest.cpp \
                  $(SCAN_SOURCE) \
                  $(SCANLIST_SOURCE)

SCANTEST_SOURCES=test/ScanTest.cpp \
				   $(SCAN_SOURCE) \

TEST_LIBS=-lgtest -lgtest_main -lpthread

GCC=g++

.phony: all clean scanlist	scan

ScanlistTest: $(SCANLISTTEST_SOURCES) Makefile product/*.h
	@$(GCC) $(CFLAGS_NORMAL) $(SCANLISTTEST_SOURCES) $(TEST_LIBS) -o $@

ScanTest: $(SCANTEST_SOURCES) Makefile product/*.h
	@$(GCC) $(CFLAGS_NORMAL) $(SCANTEST_SOURCES) $(TEST_LIBS) -o $@

clean:
	@rm -rf ScanListTest ScanTest

scanlist: ScanListTest
	@./ScanListTest

scan: ScanTest
	@./ScanTest
