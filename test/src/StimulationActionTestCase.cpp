#include "../../src/StimulationAction.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mocks/ChannelMock.h"


class StimulationActionTest : public ::testing::Test{
public:
	StimulationActionTest(){
		action = new StimulationAction();
		channel = new ChannelMock();
	}
	~StimulationActionTest(){
		delete action;
		delete channel;
	}
	StimulationAction* action;
	ChannelMock* channel;
	Json::Value parameters;
};


TEST_F(StimulationActionTest, InitWithEmptyChannelShouldThrow){
	EXPECT_THROW(action->init(nullptr), std::exception*);
}

TEST_F(StimulationActionTest, ActionInitSuccess){
	action->init(channel);

	ASSERT_EQ(action->getChannel(), channel);
}

