//
// Created by urban on 15/06/2020.
//

#include <array>
#include <catch2/catch.hpp>

#include "range.h"

TEMPLATE_TEST_CASE("Test value falls in range", "[template]", int, float, double, long) {
    using namespace ATA;

    const static std::array<TestType, 7> testValues{0, 10, -10, 5, -5, 100, -100};
    const static std::array<bool, 7> testAssertions{true, true, false, true, false, false, false };
    const static std::array<bool, 7> negativeTestAssertions{true, false, true, false, true, false, false };

    const static TestType rangeSize = 10;
    auto range = Range<TestType>(0, rangeSize);
    auto negativeRange = Range<TestType>(-rangeSize, 0);

    int b = 0;
    for(size_t i = 0; i < 7; ++i, ++b) {
        CHECK(range.inRange(testValues[i]) == testAssertions[i]);
    }

    b = 0;
    for(size_t i = 0; i < 7; ++i, ++b) {
        CHECK(negativeRange.inRange(testValues[i]) == negativeTestAssertions[i]);
    }
}