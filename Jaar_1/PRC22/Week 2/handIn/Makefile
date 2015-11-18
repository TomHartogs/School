ASSIGNMENT=file

UNITY_FOLDER=../../Unity
RESOURCE_CHECK_FOLDER=../../ResourceDetector
INC_DIRS=-I$(RESOURCE_CHECK_FOLDER)
TEST_INC_DIRS=$(INC_DIRS) -I$(UNITY_FOLDER)

SHARED_FILES=$(UNITY_FOLDER)/unity.c \
             $(RESOURCE_CHECK_FOLDER)/resource_detector.c \
             $(RESOURCE_CHECK_FOLDER)/list.c

FILE_TEST_FILES=$(SHARED_FILES) \
	            $(ASSIGNMENT)_test.c \
	            $(ASSIGNMENT).c

ELEMENT_TEST_FILES=$(SHARED_FILES) \
	               element_reader_test.c \
	               element_reader.c

HEADER_FILES=*.h

FILE_TEST = $(ASSIGNMENT)_test
ELEMENT_TEST = element_test
CC=gcc

SYMBOLS=-Wall -Werror -pedantic -O2 -std=c99
TEST_SYMBOLS=$(SYMBOLS) -DTEST

.PHONY: clean test

all: $(ELEMENT_TEST) $(FILE_TEST)

$(FILE_TEST): Makefile $(FILE_TEST_FILES)  $(HEADER_FILES)
	$(CC) $(TEST_INC_DIRS) $(TEST_SYMBOLS) $(FILE_TEST_FILES) -o $(FILE_TEST)

$(ELEMENT_TEST): Makefile $(ELEMENT_TEST_FILES)  $(HEADER_FILES)
	$(CC) $(TEST_INC_DIRS) $(TEST_SYMBOLS) $(ELEMENT_TEST_FILES) -o $(ELEMENT_TEST)

clean:
	rm -f $(ELEMENT_TEST) $(FILE_TEST)

file: $(FILE_TEST)
	@./$(FILE_TEST)

element: $(ELEMENT_TEST)
	@./$(ELEMENT_TEST)
