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
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}