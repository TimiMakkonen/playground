#include <fstream> // std::ifstream
#include <string>  // std::string
#include <sstream> // std::ostringstream

#include <gtest/gtest.h>

#include <test_config.h>

#include <playground/seesaw.h>

  class PlaygroundSeesawTest : public ::testing::Test {
  protected:
    // used for setting up fields for testing
    void SetUp() override { readTestData(); }

    void readTestData() {

        testDataGreeting = fileContentsToString(playground::TEST_DATA[playground::test_data____txt]);
    }

    // declarations:
    std::string testDataGreeting;

    // utility methods
    std::string fileContentsToString(const std::string& filePath) const {

        std::ifstream file(filePath);
        std::ostringstream ss;
        ss << file.rdbuf();

        return ss.str();
    }
};

// using PlaygroundSeesawDeathTest = PlaygroundSeesawTest;

TEST_F(PlaygroundSeesawTest, GreetingTest) {

    playground::Seesaw seesaw;

     EXPECT_EQ(seesaw.getGreeting(), "Hello from the Seesaw class!");

    EXPECT_EQ(testDataGreeting, "Hello from the test_data.txt!");
}
