//
// Created by urban on 15/06/2020.
//

#include <array>

#include "catch.hpp"
#include "range.h"

TEMPLATE_TEST_CASE("Test value falls in range", "[template]", int, float, double, long) {
    using namespace ATA;

    const static std::array<TestType, 7> testValues{0, 10, -10, 5, -5, 100, -100};
    const static std::array<bool, 7> testAssertions{true, true, false, true, false, false, false };
    const static std::array<bool, 7> negativeTestAssertions{true, false, true, false, true, false, false };

    const static int rangeSize = 10;
    auto range = Range(0, rangeSize);
    auto negativeRange = Range(-rangeSize, 0);


    int b = 0;
    for(int i = 0; i < 7; ++i, ++b) {
        CHECK(range.inRange(testValues.at(i)) == testAssertions.at(i));
    }

    b = 0;
    for(int i = 0; i < 7; ++i, ++b) {
        CHECK(negativeRange.inRange(testValues.at(i)) == negativeTestAssertions.at(i));
    }
}