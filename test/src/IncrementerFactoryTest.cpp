/*
 * IncrementerFactory.cpp
 *
 *  Created on: Oct 3, 2017
 *      Author: cnbiadministrator
 */
#include "../../src/IncrementerFactory.h"
#include "../../src/LinearIncrementer.h"
#include "gmock/gmock.h"

TEST(IncrementerFactoryTest, LinearGivenShouldCreateLinear){
	IncrementerFactory* factory = new IncrementerFactory();
	std::vector<double> parameters = {2.0,1.0,3.0};
	LinearIncrementer* incrementer = dynamic_cast<LinearIncrementer*>(factory->createIncrementerFromString("linear", parameters));
	ASSERT_EQ(incrementer != nullptr, true);
	ASSERT_EQ(incrementer->startingValue, parameters[0]);
	ASSERT_EQ(incrementer->endingValue, parameters[1]);
	ASSERT_EQ(incrementer->getDuration(), parameters[2]);
	delete incrementer;
}

TEST(IncrementerFactoryTest, BadStringGivenShouldThrow){
	IncrementerFactory* factory = new IncrementerFactory();
	std::vector<double> parameters = {2.0,1.0,3.0};
	EXPECT_THROW(factory->createIncrementerFromString("Quadratic", parameters), stim::errors::IncrementerException);
}



