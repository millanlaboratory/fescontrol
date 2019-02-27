#include <gmock/gmock.h>
#include "../../src/FESJsonReader.h"
#include "mocks/ChannelMock.h"
#include "mocks/FESStimulatorMock.h"
#include "mocks/StimulationActionMock.h"
#include "../../src/LinearIncrementer.h"
#include "../../src/TimeLimitedAction.h"

class StimulationActionFactoryMock: public StimulationActionFactory{
public:
	MOCK_METHOD2(init, void(FESStimulator*, IncrementerFactory*));
	MOCK_METHOD1(throwIfBadGrammar, void(Json::Value*));
	MOCK_METHOD1(createStimulationActionFromJson, StimulationAction*(Json::Value*));
};

class FESJsonReaderTest : public ::testing::Test{
public:
	FESJsonReaderTest(){
	}
	~FESJsonReaderTest(){
		delete reader;
		delete stimulatorMock;
		delete channelMock;
	}
	void init(){
		reader = new FESJsonReader();
		stimulatorMock = new FESStimulatorMock();
		channelMock = new ChannelMock();
		factoryMock = new StimulationActionFactoryMock();
	}

	FESJsonReader* reader;
	FESStimulatorMock* stimulatorMock;
	ChannelMock* channelMock;
	StimulationActionFactoryMock* factoryMock;
};

TEST_F(FESJsonReaderTest, InitReaderSuccess){
	init();
	EXPECT_CALL(*factoryMock, init(::testing::_,::testing::_)).Times(1);
	reader->init(stimulatorMock, factoryMock);
	ASSERT_EQ(reader->getStimulator(), stimulatorMock);
	ASSERT_EQ(reader->getStimulationActionFactory(), factoryMock);
}

TEST_F(FESJsonReaderTest, NoFileErrorShouldThrow){
	init();
	ASSERT_THROW(reader->getSequenceFromJsonFile("test/resources/nofile.json"),
			json::errors::JsonException*);
}

TEST_F(FESJsonReaderTest, EmptyJsonShouldThrow){
	init();
	ASSERT_THROW(reader->getSequenceFromJsonFile("test/resources/empty.json"),
			json::errors::EmptyException*);
}

TEST_F(FESJsonReaderTest, NotEnoughActionParametersJsonShouldThrow){
	init();
	ASSERT_THROW(reader->getSequenceFromJsonFile("test/resources/parameters1.json"),
			json::errors::BadGrammarException*);
}

TEST_F(FESJsonReaderTest, SimultaneousStimulationOnSameChannelShouldThrow){
	init();
	EXPECT_CALL(*factoryMock, init(::testing::_,::testing::_)).Times(1);
	reader->init(stimulatorMock, factoryMock);
	StimulationActionMock* action = new StimulationActionMock();
	EXPECT_CALL(*factoryMock, throwIfBadGrammar(::testing::_)).Times(2);
	EXPECT_CALL(*factoryMock, createStimulationActionFromJson(::testing::_)).Times(2).WillRepeatedly(::testing::Return(action));
	EXPECT_CALL(*action, areSimultaneousActions(::testing::_)).WillOnce(::testing::Return(true));
	ASSERT_THROW(reader->getSequenceFromJsonFile("test/resources/simultaneousStimulation.json"),
			json::errors::SimultaneousStimulationException*);
	delete action;
}

TEST_F(FESJsonReaderTest, SuccessJson){
	init();
	EXPECT_CALL(*factoryMock, init(::testing::_,::testing::_)).Times(1);
	reader->init(stimulatorMock, factoryMock);
	StimulationActionMock* action = new StimulationActionMock();
	EXPECT_CALL(*factoryMock, throwIfBadGrammar(::testing::_)).Times(1);
	EXPECT_CALL(*factoryMock, createStimulationActionFromJson(::testing::_)).Times(1).WillRepeatedly(::testing::Return(action));
	std::vector<StimulationAction*> sequence = reader->getSequenceFromJsonFile("test/resources/file.json");
	ASSERT_EQ(sequence.size(),1);
	delete action;
}

TEST_F(FESJsonReaderTest, SuccessTwoActionsJson){
	init();
	EXPECT_CALL(*factoryMock, init(::testing::_,::testing::_)).Times(1);
	reader->init(stimulatorMock, factoryMock);
	StimulationActionMock* action = new StimulationActionMock();
	EXPECT_CALL(*factoryMock, throwIfBadGrammar(::testing::_)).Times(2);
	EXPECT_CALL(*factoryMock, createStimulationActionFromJson(::testing::_)).Times(2).WillRepeatedly(::testing::Return(action));
	EXPECT_CALL(*action, areSimultaneousActions(::testing::_)).WillOnce(::testing::Return(false));
	std::vector<StimulationAction*> sequence = reader->getSequenceFromJsonFile("test/resources/flexion.json");
	ASSERT_EQ(sequence.size(),2);
	delete action;
}
