#include <string>
#include <stdexcept>
#include "gtest/gtest.h"
using namespace std;

#include "Car.h"
/*
static void CheckCarProperties(Car* carPtr, string model, string material, int diameter, int nrWheels)
{
    EXPECT_EQ(model, carPtr->getModel());
    EXPECT_EQ(nrWheels, carPtr->getNrWheels());
    for(int i = 0; i < nrWheels; i++)
    {
		EXPECT_EQ(material, carPtr->getWheel(i)->getMaterial());
		EXPECT_EQ(diameter, carPtr->getWheel(i)->getDiameter());
	}
}

class CarTest : public ::testing::Test
{
    protected:
        CarTest()
        {
            testPtr = new Car("Mercedes", "Rubber", 10, 4);
        }
        
        Car* testPtr;
};

TEST_F(CarTest, test_construction_values_copied_correctly)
{
    CheckCarProperties(testPtr, "Mercedes", "Rubber", 10, 4);
}

TEST_F(LimousineTest, test_car_needsCleaning)
{
    EXPECT_TRUE(testPtr->Rent());
    EXPECT_FALSE(testPtr->NeedsCleaning());
    EXPECT_EQ(LimousinePricePerKm * 1, testPtr->Return(1));
    EXPECT_TRUE(testPtr->NeedsCleaning());
}*/
