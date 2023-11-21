#include <gtest/gtest.h>
#include "TimeFunction.hpp"
#include <thread>
#include <functional>

// Helper functions for testing
void dummyFunction() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int dummyFunctionWithReturn() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 42;
}

// Test Fixture for TimeIt::TimeFunction
class TimeFunctionTest : public ::testing::Test {
protected:
    std::string test_name;

    void SetUp() override {
        test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    }
};

// Test timed_Function for non-void return type
TEST_F(TimeFunctionTest, TimedFunctionNonVoid) {
    auto result = TimeIt::TimeFunction::timed_Function<int>(test_name, std::function<int()>(dummyFunctionWithReturn));
    ASSERT_EQ(result, 42); // Function should return correct value
}

// Test timed_Function for void return type
TEST_F(TimeFunctionTest, TimedFunctionVoid) {
    ASSERT_NO_THROW(TimeIt::TimeFunction::timed_Function<void>(test_name, std::function<void()>(dummyFunction)));
}

TEST_F(TimeFunctionTest, TimedFunctionNonVoidNoName) {
    auto result = TimeIt::TimeFunction::timed_Function<int>(std::function<int()>(dummyFunctionWithReturn));
    ASSERT_EQ(result, 42); // Function should return correct value
}

// Test timed_Function for void return type
TEST_F(TimeFunctionTest, TimedFunctionVoidNoName) {
    ASSERT_NO_THROW(TimeIt::TimeFunction::timed_Function<void>(std::function<void()>(dummyFunction)));
}


// Test timed_unit_Function for non-void return type
TEST_F(TimeFunctionTest, TimedUnitFunctionNonVoid) {
    auto [result, elapsed_time, unit] = TimeIt::TimeFunction::timed_unit_Function<int>(std::function<int()>(dummyFunctionWithReturn));
    ASSERT_EQ(result, 42); // Function should return correct value
    ASSERT_GT(elapsed_time, 0.0); // Elapsed time should be greater than 0
    ASSERT_FALSE(unit.empty());   // Unit should not be empty
}

// Test timed_unit_Function for void return type
TEST_F(TimeFunctionTest, TimedUnitFunctionVoid) {
    auto [elapsed_time, unit] = TimeIt::TimeFunction::timed_unit_Function<void>(std::function<void()>(dummyFunction));
    ASSERT_GT(elapsed_time, 0.0); // Elapsed time should be greater than 0
    ASSERT_FALSE(unit.empty());   // Unit should not be empty
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
