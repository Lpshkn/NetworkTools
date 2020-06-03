#include <gtest/gtest.h>
#include "configurator.h"

class ConfiguratorTest : public ::testing::Test {
protected:
    Configurator *configurator{};

    void SetUp() override {
        configurator = new Configurator("Test");
    }

    void TearDown() override {
        delete configurator;
    }

};

TEST_F(ConfiguratorTest, GetMethodsWithoutInitialize) {
    ASSERT_NO_THROW(configurator->getFilter());
    ASSERT_NO_THROW(configurator->getInterface());
    ASSERT_EQ("", configurator->getFilter());
    ASSERT_EQ("", configurator->getInterface());
}

TEST_F(ConfiguratorTest, ParseArguments) {
    int argc1 = 3; char *argv1[] = {(char*)"Test", (char*)"-f", (char*)"ip and udp"};
    // Redirect stderr to /dev/null
    std::cerr.rdbuf(nullptr);
    // System exit, because of not passed positional argument
    ASSERT_DEATH(configurator->parseArguments(argc1, argv1), "");

    int argc2 = 3; char *argv2[] = {(char*)"Test", (char*)"wlo1", (char*)"-f"};
    ASSERT_DEATH(configurator->parseArguments(argc2, argv2), "");
}

TEST_F(ConfiguratorTest, GetInterfaceAndFilter) {
    int argc1 = 4; char *argv1[] = {(char*)"Test", (char*)"wlo1", (char*)"-f", (char*)"ip and udp"};
    ASSERT_NO_THROW(configurator->parseArguments(argc1, argv1));
    ASSERT_EQ("wlo1", configurator->getInterface());
    ASSERT_EQ("ip and udp", configurator->getFilter());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}