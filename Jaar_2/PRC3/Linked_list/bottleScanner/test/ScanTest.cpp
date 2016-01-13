#include "gtest/gtest.h"

#include "Scan.h"

static void CheckScanProperties(Scan* ScanPtr, int serialNumber, int nrOfTimesRecycled)
{
    EXPECT_EQ(serialNumber, ScanPtr->getSerialNumber());
    EXPECT_EQ(nrOfTimesRecycled, ScanPtr->getTimesRecycled());
}

class ScanTest : public ::testing::Test
{
    protected:
        ScanTest()
        {
            testPtr = new Scan(10);
        }
        
        Scan* testPtr;
};

TEST_F(ScanTest, test_add_normal_Scan_to_empty_list)
{
	CheckScanProperties(testPtr, 10, 0);
}

TEST_F(ScanTest, test_recycle)
{
	ASSERT_EQ(0, testPtr->getTimesRecycled());
	testPtr->recycle();
	ASSERT_EQ(1, testPtr->getTimesRecycled());
}

TEST_F(ScanTest, test_set_and_get_next)
{
	Scan* newScan = new Scan(10);
	testPtr->setNext(newScan);
	ASSERT_EQ(newScan, testPtr->getNext());
}
