#include "gtest/gtest.h"

#include "ScanList.h"

class ScanListTest : public ::testing::Test
{
    protected:
        ScanListTest()
        {
            testPtr = new ScanList();
        }
        
        ScanList* testPtr;
};

TEST_F(ScanListTest, test_add_normal_Scan_to_empty_list)
{
	testPtr->addScan(6);
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(6, foundScan->getSerialNumber());
}

TEST_F(ScanListTest, test_add_negative_Scan_to_empty_list)
{
	testPtr->addScan(-1);
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(-1, foundScan->getSerialNumber());
}

TEST_F(ScanListTest, test_add_exisiting_Scan_to_list)
{
	testPtr->addScan(1);
	testPtr->addScan(2);
	testPtr->addScan(3);
	testPtr->addScan(4);
	testPtr->addScan(5);
	testPtr->addScan(5);
	testPtr->addScan(5);
	testPtr->addScan(5);
	
	Scan* foundScan = testPtr->getScanByNr(4);
	EXPECT_EQ(3, foundScan->getTimesRecycled());
}

TEST_F(ScanListTest, test_add_Scan_in_middle_sorted_to_list)
{
	testPtr->addScan(5);
	testPtr->addScan(7);
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(5, foundScan->getSerialNumber());
	foundScan = testPtr->getScanByNr(1);
	EXPECT_EQ(7, foundScan->getSerialNumber());
	testPtr->addScan(6);
	foundScan = testPtr->getScanByNr(1);
	EXPECT_EQ(6, foundScan->getSerialNumber());
	foundScan = testPtr->getScanByNr(2);
	EXPECT_EQ(7, foundScan->getSerialNumber());
}

TEST_F(ScanListTest, test_add_Scan_in_beginning_sorted_to_list)
{
	testPtr->addScan(7);
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(7, foundScan->getSerialNumber());
	testPtr->addScan(5);
	foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(5, foundScan->getSerialNumber());
	foundScan = testPtr->getScanByNr(1);
	EXPECT_EQ(7, foundScan->getSerialNumber());
}

TEST_F(ScanListTest, test_add_Scan_in_end_sorted_to_list)
{
	testPtr->addScan(5);
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(5, foundScan->getSerialNumber());
	testPtr->addScan(7);
	foundScan = testPtr->getScanByNr(1);
	EXPECT_EQ(7, foundScan->getSerialNumber());
}

TEST_F(ScanListTest, test_add_Negative_in_sorted_to_list)
{
	testPtr->addScan(5);
	testPtr->addScan(-1);
	Scan* foundScan = testPtr->getScanByNr(1);
	EXPECT_EQ(5, foundScan->getSerialNumber());
	foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(-1, foundScan->getSerialNumber());
}

TEST_F(ScanListTest, test_find_existing_Scan)
{
	testPtr->addScan(1);
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(1, foundScan->getSerialNumber());
}

TEST_F(ScanListTest, test_find_none_existing_Scan)
{
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(0, foundScan);
}

TEST_F(ScanListTest, test_remove_Scan_from_list)
{
	testPtr->addScan(5);
	EXPECT_TRUE(testPtr->removeScan(5));
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(0, foundScan);
}

TEST_F(ScanListTest, test_remove_middle_Scan_from_ordered_list)
{
	testPtr->addScan(5);
	testPtr->addScan(6);
	testPtr->addScan(7);
	EXPECT_TRUE(testPtr->removeScan(6));
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(5, foundScan->getSerialNumber());
	foundScan = testPtr->getScanByNr(1);
	EXPECT_EQ(7, foundScan->getSerialNumber());
}

TEST_F(ScanListTest, test_remove_first_Scan_from_ordered_list)
{
	testPtr->addScan(5);
	testPtr->addScan(6);
	testPtr->addScan(7);
	EXPECT_TRUE(testPtr->removeScan(5));
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(6, foundScan->getSerialNumber());
	foundScan = testPtr->getScanByNr(1);
	EXPECT_EQ(7, foundScan->getSerialNumber());
}

TEST_F(ScanListTest, test_remove_Last_Scan_from_ordered_list)
{
	testPtr->addScan(5);
	testPtr->addScan(6);
	testPtr->addScan(7);
	EXPECT_TRUE(testPtr->removeScan(7));
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(5, foundScan->getSerialNumber());
	foundScan = testPtr->getScanByNr(1);
	EXPECT_EQ(6, foundScan->getSerialNumber());
}

TEST_F(ScanListTest, test_get_times_recycled)
{
	testPtr->addScan(5);
	Scan* foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(0, foundScan->getTimesRecycled());
	testPtr->addScan(5);
	foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(1, foundScan->getTimesRecycled());
	testPtr->addScan(5);
	foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(2, foundScan->getTimesRecycled());
	testPtr->addScan(5);
	foundScan = testPtr->getScanByNr(0);
	EXPECT_EQ(3, foundScan->getTimesRecycled());
}
