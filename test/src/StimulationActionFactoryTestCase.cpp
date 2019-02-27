/*
 * StimulationActionFactory.cpp
 *
 *  Created on: Dec 18, 2017
 *      Author: cnbi
 */

#include "../../src/StimulationActionFactory.h"
#include "../../src/IncrementerFactory.h"
#include "mocks/FESStimulatorMock.h"
#include "mocks/ChannelMock.h"
#include "mocks/IncrementerMock.h"
#include "gmock/gmock.h"
#include <fstream>
#include "../../src/errors/JsonException.h"

class IncrementerFactoryMock: public IncrementerFactory{
public:
	MOCK_METHOD2(createIncrementerFromString, Incrementer*(std::string, std::vector<double>));
};

class StimulationActionFactoryTest : public ::testing::Test{
public:
	StimulationActionFactoryTest(){
		factory = new StimulationActionFactory();
		incrementerFactory = new IncrementerFactoryMock();
		stimulator = new FESStimulatorMock();
	}
	~StimulationActionFactoryTest(){
		delete stimulator;
		delete factory;
	}
	Json::Value initTest(std::string file){
		std::ifstream ifs(file.c_str());
		if (!ifs.is_open()) {
			throw json::errors::JsonException(file.c_str());
		}
		Json::Reader reader;
		Json::Value obj;
		reader.parse(ifs, obj);
		ifs.close();
		return obj;
	}

	StimulationActionFactory* factory;
	IncrementerFactoryMock* incrementerFactory;
	FESStimulatorMock* stimulator;
};

TEST_F(StimulationActionFactoryTest, InitializationSuccess){
	factory->init(stimulator, incrementerFactory);
	ASSERT_EQ(factory->getStimulator(),stimulator);
	ASSERT_EQ(factory->getIncrementerFactory(),incrementerFactory);
}

TEST_F(StimulationActionFactoryTest, LinearGivenShouldCreateLinear){
	factory->init(stimulator, incrementerFactory);
	Json::Value obj = initTest("test/resources/LinearStimActionSuccess.json");

	ChannelMock* channel = new ChannelMock();
	IncrementerMock* incrementer = new IncrementerMock();

	EXPECT_CALL(*stimulator, getChannelByChannelNumber(::testing::_)).WillOnce(::testing::Return(channel));
	EXPECT_CALL(*incrementerFactory, createIncrementerFromString(::testing::_,::testing::_)).Times(4).WillRepeatedly(::testing::Return(incrementer));

	TimeLimitedAction* action = dynamic_cast<TimeLimitedAction*>(factory->createStimulationActionFromJson(&(obj["sequence"][0])));

	EXPECT_FALSE(action == nullptr);
	ASSERT_EQ(action->getDelay(),obj["sequence"][0]["delay"].asInt());
	ASSERT_EQ(action->getDuration(),obj["sequence"][0]["duration"].asInt());

	delete channel;
	delete action;
}

TEST_F(StimulationActionFactoryTest, SetterGivenShouldCreateSetter){
	factory->init(stimulator, incrementerFactory);
	Json::Value obj = initTest("test/resources/SetterStimActionSuccess.json");

	ChannelMock* channel = new ChannelMock();

	EXPECT_CALL(*stimulator, getChannelByChannelNumber(::testing::_)).WillOnce(::testing::Return(channel));

	SetterAction* action = dynamic_cast<SetterAction*>(factory->createStimulationActionFromJson(&(obj["sequence"][0])));

	EXPECT_FALSE(action == nullptr);
	ASSERT_EQ(action->getCurrent(),obj["sequence"][0]["current"].asInt());
	EXPECT_TRUE(abs(action->getPulseWidth() - obj["sequence"][0]["pulseWidth"].asDouble()) < 0.001);

	delete channel;
	delete action;
}

TEST_F(StimulationActionFactoryTest, BadTypeGivenShouldThrow){
	factory->init(stimulator, incrementerFactory);
	Json::Value obj = initTest("test/resources/BadGrammarActionType.json");

	EXPECT_THROW(factory->createStimulationActionFromJson(&(obj["sequence"][0])),
			json::errors::BadGrammarException*);

}

TEST_F(StimulationActionFactoryTest, BadGrammarSetterShouldThrow){
	factory->init(stimulator, incrementerFactory);
	Json::Value obj = initTest("test/resources/BadGrammarSetterAction.json");
	EXPECT_THROW(factory->createStimulationActionFromJson(&(obj["sequence"][0])),
			json::errors::MissingParameterException*);

}

TEST_F(StimulationActionFactoryTest, BadGrammarLinearJsonShouldThrow){
	factory->init(stimulator, incrementerFactory);
	Json::Value obj = initTest("test/resources/BadGrammarLinearAction.json");
	EXPECT_THROW(factory->createStimulationActionFromJson(&(obj["sequence"][0])),
			json::errors::MissingParameterException*);
}





