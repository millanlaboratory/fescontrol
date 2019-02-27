

#include "gmock/gmock.h"
#include "../../src/MovementAuthorizer.h"
#include "../../src/errors/JsonException.h"
#include "../../src/errors/AuthorizerException.h"



class MovementAuthorizerTestCase: public ::testing::Test{
public:
	MovementAuthorizerTestCase(){}
	void init(){
		authorizer = new MovementAuthorizer();
	}
	MovementAuthorizer* authorizer;
};

TEST_F(MovementAuthorizerTestCase, CreationSuccess){
	std::string fileName = "test/resources/AuthorizedMovements.json";
	init();
	authorizer->init(fileName);
	ASSERT_EQ(authorizer->getFileName(), fileName);
	ASSERT_EQ(authorizer->getMovementFileNameFromEventId(14), "flexion.json");
}

TEST_F(MovementAuthorizerTestCase, InitSuccess){
	std::string fileName = "test/resources/AuthorizedMovements.json";
	init();
	authorizer->setFileName(fileName);
	authorizer->init();
	ASSERT_EQ(authorizer->getFileName(), fileName);
	ASSERT_EQ(authorizer->getMovementFileNameFromEventId(14), "flexion.json");
}

TEST_F(MovementAuthorizerTestCase, NoFileErrorShouldThrow){
	init();
	std::string fileName = "test/resources/movements.json";
	ASSERT_THROW(authorizer->init(fileName), json::errors::JsonException*);
}

TEST_F(MovementAuthorizerTestCase, EmptyJsonShouldThrow){
	init();
	std::string fileName = "test/resources/empty.json";
	ASSERT_THROW(authorizer->init(fileName), json::errors::EmptyException*);
}

TEST_F(MovementAuthorizerTestCase, BadGrammarOnFirstMovementShouldThrow){
	init();
	std::string fileName = "test/resources/badGrammarAction1MovementAuthorizer.json";
	ASSERT_THROW(authorizer->init(fileName), json::errors::BadGrammarException*);
}

TEST_F(MovementAuthorizerTestCase, BadGrammarOnSecondMovementShouldThrow){
	init();
	std::string fileName = "test/resources/badGrammarAction2MovementAuthorizer.json";
	ASSERT_THROW(authorizer->init(fileName), json::errors::BadGrammarException*);
}

TEST_F(MovementAuthorizerTestCase, GetMovementFromUnknownEventIdShouldThrow){
	std::string fileName = "test/resources/AuthorizedMovements.json";
	init();
	authorizer->init(fileName);
	EXPECT_THROW(authorizer->getMovementFileNameFromEventId(5), auth::errors::UnauthorizedMovementIdException*);
}
