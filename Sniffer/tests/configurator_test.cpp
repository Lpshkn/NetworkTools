#include <gtest/gtest.h>
#include "configurator.h"

class ConfiguratorTest : public ::testing::Test {
protected:
    Configurator *configurator;

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}