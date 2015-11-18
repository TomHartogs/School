#include "integer_file.h"
#include "unity.h"

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)


#define TESTFILE "test.txt"
static const int StartValue = 8320;
static const int EndValue = 7321;

void setUp(void)
{
    // This is run before EACH test
    create_file(TESTFILE, StartValue, EndValue);
}

void tearDown(void)
{
    // This is run after EACH test
    delete_file(TESTFILE);
}


void test_CreateFileNullCheck(void)
{
    TEST_ASSERT_EQUAL(-1, create_file(NULL, 12, 10));
}

void test_CreateFileInvaludHighAndLow(void)
{
    TEST_ASSERT_EQUAL(-1, create_file(TESTFILE, 10, 12));
}

void test_DeleteFileNullCheck(void)
{
    TEST_ASSERT_EQUAL(-1, delete_file(NULL));
}

void test_ReadValueNullCheck(void)
{
    TEST_ASSERT_EQUAL(-1, read_value(NULL, 12));
}

void test_ReadingFirstValueInFile(void)
{
    FILE* fileptr = fopen(TESTFILE, "rb");
    TEST_ASSERT_NOT_NULL(fileptr);

    TEST_ASSERT_EQUAL(StartValue, read_value(fileptr, 0));

    fclose(fileptr);
}

void test_ReadingValueInMiddleOfFile(void)
{
    FILE* fileptr = fopen(TESTFILE, "rb");
    TEST_ASSERT_NOT_NULL(fileptr);

    TEST_ASSERT_EQUAL(StartValue-250, read_value(fileptr, 250));

    fclose(fileptr);
}

void test_ReadingLastValueInFile(void)
{
    FILE* fileptr = fopen(TESTFILE, "rb");
    TEST_ASSERT_NOT_NULL(fileptr);

    TEST_ASSERT_EQUAL(EndValue, read_value(fileptr, 999));

    fclose(fileptr);
}

int main(void)
{
    UnityBegin();

    MY_RUN_TEST(test_CreateFileNullCheck);
    MY_RUN_TEST(test_CreateFileInvaludHighAndLow);
    MY_RUN_TEST(test_DeleteFileNullCheck);
    MY_RUN_TEST(test_ReadValueNullCheck);
    MY_RUN_TEST(test_ReadingFirstValueInFile);
    MY_RUN_TEST(test_ReadingValueInMiddleOfFile);
    MY_RUN_TEST(test_ReadingLastValueInFile);

    return UnityEnd();
}
