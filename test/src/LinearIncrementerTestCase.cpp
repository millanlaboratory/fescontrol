#include "../../src/LinearIncrementer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class LinearIncrementerTestCase : public ::testing::Test{
public:
	LinearIncrementerTestCase();
	virtual ~LinearIncrementerTestCase();
};

TEST(LinearIncrementerTestCase, CreateLinearIncrementSuccess){
	double minimumValue = 0;
	double maximumValue = 2;
	double duration = 1;
	LinearIncrementer* incrementer = new LinearIncrementer(minimumValue, maximumValue, duration);
	ASSERT_EQ(incrementer->startingValue, minimumValue);
	ASSERT_EQ(incrementer->endingValue, maximumValue);
	ASSERT_EQ(incrementer->getDuration(), duration);
	delete incrementer;
}

TEST(LinearIncrementerTestCase, CreateLinearIncrementWithVectorOfParametersSuccess){
	double minimumValue = 0;
	double maximumValue = 2;
	double duration = 1;
	std::vector<double> parameters = {minimumValue, maximumValue, duration};
	LinearIncrementer* incrementer = new LinearIncrementer(parameters);
	ASSERT_EQ(incrementer->startingValue, minimumValue);
	ASSERT_EQ(incrementer->endingValue, maximumValue);
	ASSERT_EQ(incrementer->getDuration(), duration);
	delete incrementer;
}

TEST(LinearIncrementerTestCase, GetLinearDecrementSuccess){
	double minimumValue = 0;
	double maximumValue = 2;
	double duration = 1;
	std::vector<double> parameters = {minimumValue, maximumValue, duration};
	LinearIncrementer* incrementer = new LinearIncrementer(parameters);
	LinearIncrementer* decrementer = (LinearIncrementer*)incrementer->getDecrementer();
	ASSERT_EQ(decrementer->startingValue, maximumValue);
	ASSERT_EQ(decrementer->endingValue, minimumValue);
	ASSERT_EQ(decrementer->getDuration(), duration);
	delete incrementer;
	delete decrementer;
}

TEST(LinearIncrementerTestCase, CreateLinearIncrementWithWrongVectorOfParameterShouldThrow){
	double minimumValue = 0;
	double maximumValue = 2;
	std::vector<double> parameters = {minimumValue, maximumValue};
	EXPECT_THROW(new LinearIncrementer(parameters), stim::errors::WrongParametersException);
}

TEST(LinearIncrementerTestCase, GetLinearIncrementSuccess){
	double minimum = 0;
	double maximum = 1;
	double duration = 2;
	LinearIncrementer* incrementer = new LinearIncrementer(minimum, maximum, duration);
	EXPECT_TRUE(abs(incrementer->getIncrement(0.1, 0) - double(0.05)) < 0.0001);
	delete incrementer;
}

TEST(LinearIncrementerTestCase, GetLinearDecrementExpectNegativeValue){
	double minimum = 0;
	double maximum = 1;
	double duration = 2;
	LinearIncrementer* incrementer = new LinearIncrementer(minimum, maximum, duration);
	EXPECT_TRUE(incrementer->getDecrement(0.1, 1) < 0);
	delete incrementer;
}

TEST(LinearIncrementerTestCase, GetLinearIncrementWithCurrentValueEqualToMaxSuccess){
	double minimum = 0;
	double maximum = 1;
	double duration = 2;
	LinearIncrementer* incrementer = new LinearIncrementer(minimum, maximum, duration);
	ASSERT_EQ(incrementer->getIncrement(0.1, 1),0);
	delete incrementer;
}

TEST(LinearIncrementerTestCase, GetLinearDecrementWithCurrentValueEqualToMinSuccess){
	double minimum = 0;
	double maximum = 1;
	double duration = 2;
	LinearIncrementer* incrementer = new LinearIncrementer(minimum, maximum, duration);
	ASSERT_EQ(incrementer->getDecrement(0.1, 0),0);
	delete incrementer;
}

TEST(LinearIncrementerTestCase, GetLinearIncrementWithCurrentValueCloseToMaxValue){
	LinearIncrementer* incrementer = new LinearIncrementer(0, 1, 2);
	EXPECT_TRUE(abs(incrementer->getIncrement(0.1, 0.96) - 0.04) < 0.0001);
	delete incrementer;
}

TEST(LinearIncrementerTestCase, GetLinearDecrementWithCurrentValueCloseToMinValue){
	LinearIncrementer* incrementer = new LinearIncrementer(0, 7, 3000);
	EXPECT_TRUE(abs(incrementer->getDecrement(300, 0.42) + 0.42) < 0.0001);
	delete incrementer;
}

TEST(LinearIncrementerTestCase, GetLinearIncrementWithNoDuration){
	LinearIncrementer* incrementer = new LinearIncrementer(0, 2, 0);
	ASSERT_EQ(incrementer->getIncrement(0.1, 0),2);
	delete incrementer;
}

TEST(LinearIncrementerTestCase, GetLinearDecrementWithNoDuration){
	LinearIncrementer* incrementer = new LinearIncrementer(0, 2, 0);
	ASSERT_EQ(incrementer->getDecrement(0.1, 1),-2);
	delete incrementer;
}
