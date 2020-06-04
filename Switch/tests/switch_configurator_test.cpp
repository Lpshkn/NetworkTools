#include <gtest/gtest.h>
#include "switch_configurator.h"

class SwitchConfiguratorTest : public ::testing::Test {
protected:
    SwitchConfigurator *configurator{};

    void SetUp() override {
        configurator = new SwitchConfigurator("Test");
    }

    void TearDown() override {
        delete configurator;
    }
};

TEST_F(SwitchConfiguratorTest, GetParametersWithoutParsin) {
    ASSERT_EQ(configurator->getFilter(), "");
    ASSERT_EQ(configurator->getInterfaces(), nullptr);
}

TEST_F(SwitchConfiguratorTest, ParseArgumentsIncorrect) {
    int argc1 = 3; char *argv1[] = {(char*)"Test", (char*)"-t", (char*)"15"};
    // Redirect stderr to /dev/null
    std::cerr.rdbuf(nullptr);
    // System exit, because of not passed positional argument
    ASSERT_DEATH(configurator->parseArguments(argc1, argv1), "");

    // System exit, because of incorrect optional argument
    int argc2 = 3; char *argv2[] = {(char*)"Test", (char*)"-f", (char*)"wlo1"};
    ASSERT_DEATH(configurator->parseArguments(argc2, argv2), "");

    // System exit, because of it's not int in '-t' parameter
    int argc3 = 4; char *argv3[] = {(char*)"Test", (char*)"-t", (char*)"gdfg", (char*)"wlo1"};
    ASSERT_DEATH(configurator->parseArguments(argc3, argv3), "");

    // System exit, because of there is no positional parameter
    int argc4 = 4; char *argv4[] = {(char*)"Test", (char*)"-t", (char*)"15", (char*)"wlo1"};
    ASSERT_DEATH(configurator->parseArguments(argc4, argv4), "");
    int argc5 = 1; char *argv5[] = {(char*)"Test"};
    ASSERT_DEATH(configurator->parseArguments(argc5, argv5), "");

    // System exit, because of there is less than 2 arguments in positional parameter
    int argc6 = 2; char *argv6[] = {(char*)"Test", (char*)"wlo1"};
    ASSERT_DEATH(configurator->parseArguments(argc6, argv6), "");
}

TEST_F(SwitchConfiguratorTest, ParseArgumentsCorrect) {
    // There are 2 parameters with 'i' option and the default value (60) with the 't' option
    int argc1 = 3; char *argv1[] = {(char*)"Test", (char*)"wlo1", (char*)"eth"};
    ASSERT_NO_THROW(configurator->parseArguments(argc1, argv1));
    ASSERT_EQ(configurator->getLifeTime(), 60);
    auto ifaces1 = configurator->getInterfaces();
    ASSERT_TRUE(std::equal(ifaces1->begin(), ifaces1->end(), std::vector<std::string>{"wlo1", "eth"}.begin()));

    auto conf = SwitchConfigurator("Test");
    int argc2 = 6; char *argv2[] = {(char*)"Test", (char*)"-t", (char*)"35", (char*)"wlo1", (char*)"eth", (char*)"eth2"};
    ASSERT_NO_THROW(conf.parseArguments(argc2, argv2));
    ASSERT_EQ(conf.getLifeTime(), 35);
    auto ifaces2 = conf.getInterfaces();
    ASSERT_TRUE(std::equal(ifaces2->begin(), ifaces2->end(), std::vector<std::string>{"wlo1", "eth", "eth2"}.begin()));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}