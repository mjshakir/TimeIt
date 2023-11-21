#include <gtest/gtest.h>
#include "TimeIt.hpp"
#include <thread>
#include <functional>

// Helper function for testing
void sleepFunction() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

// Test Fixture for TimeIt::TimeIt
class TimeItTest : public ::testing::Test {
protected:
    std::string test_name;

    void SetUp() override {
        test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    }
};

// Test default constructor
TEST_F(TimeItTest, DefaultConstructor) {
    TimeIt::TimeIt timer(test_name);
    sleepFunction();
    double elapsed_time = timer.get_time();
    ASSERT_GT(elapsed_time, 0.0); // Elapsed time should be greater than 0
}

// Test constructor with function name
TEST_F(TimeItTest, ConstructorWithFunctionName) {
    TimeIt::TimeIt timer(test_name);
    sleepFunction();
    double elapsed_time = timer.get_time();
    ASSERT_GT(elapsed_time, 0.0); // Elapsed time should be greater than 0
}

// Test get_time method
TEST_F(TimeItTest, GetTime) {
    TimeIt::TimeIt timer(test_name);
    sleepFunction();
    double elapsed_time = timer.get_time();
    ASSERT_GT(elapsed_time, 0.0); // Elapsed time should be greater than 0
}

// Test get_time_unit method
TEST_F(TimeItTest, GetTimeUnit) {
    TimeIt::TimeIt timer(test_name);
    sleepFunction();
    auto [elapsed_time, unit] = timer.get_time_unit();
    ASSERT_GT(elapsed_time, 0.0); // Elapsed time should be greater than 0
    ASSERT_FALSE(unit.empty());   // Unit should not be empty
}

// Test timing accuracy
TEST_F(TimeItTest, TimingAccuracy) {
    TimeIt::TimeIt timer(test_name);
    auto start = std::chrono::high_resolution_clock::now();
    sleepFunction();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> expected_duration = end - start;

    auto [elapsed_time, unit] = timer.get_time_unit();
    ASSERT_NEAR(elapsed_time, expected_duration.count(), 5.0); // Allow some tolerance
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}