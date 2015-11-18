ASSIGNMENT=stegano

UNITY_FOLDER=../../Unity
RESOURCE_CHECK_FOLDER=../../ResourceDetector
INC_DIRS=-I$(RESOURCE_CHECK_FOLDER) -Icode
TEST_INC_DIRS=$(INC_DIRS) -I$(UNITY_FOLDER)

SHARED_FILES=$(RESOURCE_CHECK_FOLDER)/resource_detector.c \
             $(RESOURCE_CHECK_FOLDER)/list.c

SRC_FILES=code/main.c \
          code/$(ASSIGNMENT).c \
		  code/header.c \
		  code/bit.c \
		  $(SHARED_FILES)

STEGANO_TEST=test/$(ASSIGNMENT)_test.c \
             code/$(ASSIGNMENT).c \
             code/header.c \
             code/bit.c \
             $(UNITY_FOLDER)/unity.c \
             $(SHARED_FILES)

HEADER_TEST=test/header_test.c \
            code/header.c \
            $(UNITY_FOLDER)/unity.c \
            $(SHARED_FILES)

BIT_TEST=test/bit_test.c \
         code/bit.c \
         $(UNITY_FOLDER)/unity.c \
         $(SHARED_FILES)

HEADER_FILES=code/*.h

STEGANOTEST=$(ASSIGNMENT)_test
HEADERTEST=header_test
BITTEST=bit_test

CC=gcc

SYMBOLS=-Wall -Werror -pedantic -O2 -std=c99
TEST_SYMBOLS=$(SYMBOLS) -DTEST

.PHONY: clean test

all: $(ASSIGNMENT)

$(ASSIGNMENT): $(SRC_FILES) $(HEADER_FILES) Makefile
	$(CC) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES) -o $(ASSIGNMENT)

$(STEGANOTEST): Makefile $(STEGANO_TEST) $(HEADER_FILES)
	$(CC) $(TEST_INC_DIRS) $(TEST_SYMBOLS) $(STEGANO_TEST) -o $(STEGANOTEST)

$(HEADERTEST): Makefile $(HEADER_TEST) $(HEADER_FILES)
	$(CC) $(TEST_INC_DIRS) $(TEST_SYMBOLS) $(HEADER_TEST) -o $(HEADERTEST)

$(BITTEST): Makefile $(BIT_TEST) $(HEADER_FILES)
	$(CC) $(TEST_INC_DIRS) $(TEST_SYMBOLS) $(BIT_TEST) -o $(BITTEST)

clean:
	@rm -f $(ASSIGNMENT) $(STEGANOTEST) $(HEADERTEST) $(BITTEST)

steganotest: $(STEGANOTEST)
	@./$(STEGANOTEST)

headertest: $(HEADERTEST)
	@./$(HEADERTEST)

bittest: $(BITTEST)
	@./$(BITTEST)

scripttest:
	@test/test.sh

