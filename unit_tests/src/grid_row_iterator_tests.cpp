//
// Created by David Price on 05/06/2020.
//

#include <catch2/catch.hpp>
#include <algorithm>
#include <numeric>

#include "grid.h"

TEST_CASE("Test row begin is correctly retrieved.") {
    using namespace ATA;
    auto testGrid = Grid2D<int>(10, 10);
    auto outputArray = std::array<int, 10>{0, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    size_t arrayIndex = 0;
    for (int i = 0; i < 10L; ++i) {
        auto it = testGrid.rowBegin(i);
        *it = i * 10;
        CHECK(*it == testGrid.at(0, i));
        CHECK(outputArray[arrayIndex] == testGrid.at(0, i));
        CHECK(*it == outputArray[arrayIndex]);
        ++arrayIndex;
    }

    auto testOffsetGrid = Grid2D<int>(10, 10, -5, -5);
    auto outputOffsetArray = std::array<int, 10>{-50, -40, -30, -20, -10, 0, 10, 20, 30, 40};

    arrayIndex = 0;
    for (int i = -5; i < 5; ++i) {
        auto it = testOffsetGrid.rowBegin(i);
        *it = i * 10;
        CHECK(*it == testOffsetGrid.at(-5, i));
        CHECK(outputOffsetArray[arrayIndex] == testOffsetGrid.at(-5, i));
        CHECK(*it == outputOffsetArray[arrayIndex]);
        ++arrayIndex;
    }
}

TEST_CASE("Test row end is correctly retrieved.") {
    using namespace ATA;
    auto testGrid = Grid2D<int>(10, 10);
    auto outputArray = std::array<int, 10>{0, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    size_t arrayIndex = 0;
    for (int i = 0; i < 10; ++i) {
        auto it = --testGrid.rowEnd(i);
        *it = i * 10;

        CHECK(*it == testGrid.at(9, i));
        CHECK(outputArray[arrayIndex] == testGrid.at(9, i));
        CHECK(*it == outputArray[arrayIndex]);
        ++arrayIndex;
    }

    auto outputOffsetArray = std::array<int, 10>{-50, -40, -30, -20, -10, 0, 10, 20, 30, 40};
    auto testOffsetGrid = Grid2D<int>(10, 10, -5, -5);

    arrayIndex = 0;
    for (int i = -5; i < 5; ++i) {
        auto it = --testOffsetGrid.rowEnd(i);
        *it = i * 10;

        CHECK(*it == testOffsetGrid.at(4, i));
        CHECK(outputOffsetArray[arrayIndex] == testOffsetGrid.at(4, i));
        CHECK(*it == outputOffsetArray[arrayIndex]);
        ++arrayIndex;
    }
}

TEST_CASE("Test row iterator is correctly retrieved.") {
    using namespace ATA;
    auto testGrid = Grid2D<int>(10, 10);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            auto it = testGrid.row(i, j);
            *it = (i + 1) * 10;
            CHECK(*it == testGrid.at(i, j));
        }
    }
}

TEST_CASE("Test row iterators increment and offset work correctly.") {
    using namespace ATA;
    auto testGrid = Grid2D<int>(10, 10);

    auto it = testGrid.rowBegin(0);

    int index = 0;
    while (it != testGrid.rowEnd(0)) {
        ++it;
        ++index;
    }

    CHECK(index == 10);
}

TEST_CASE("Test row iterators work with std algorithms") {
    using namespace ATA;
    auto testGrid = Grid2D<int>(10, 10);

    for (int i = 0; i < 10; ++i) {
        testGrid.at(i, 0) = (i + 1) * 10;
    }

    int output = std::accumulate(testGrid.rowBegin(0), testGrid.rowEnd(0), 0);
    CHECK(output == 550);

    std::for_each(testGrid.rowBegin(1), testGrid.rowEnd(1), [](auto &value) {
      value = 100;
    });

    for (int i = 0; i < 10; ++i) {
        CHECK(testGrid.at(i, 1) == 100);
    }

    const auto binaryTransform = [](const auto &valueA, const auto &valueB) {
      return valueA * valueB;
    };

    std::transform(testGrid.rowBegin(0), testGrid.rowEnd(0),
                   testGrid.rowBegin(1),
                   testGrid.rowBegin(2),
                   binaryTransform);

    const std::array<int, 10> outputArray = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    size_t arrayIndex = 0;
    for (int i = 0; i < 10; ++i, ++arrayIndex) {
        CHECK(testGrid.at(i, 2) == outputArray[arrayIndex]);
    }
}

TEST_CASE("Test row iterator is converted correctly from a column iterator") {
    using namespace ATA;
    auto testGrid = Grid2D<int>({{1, 2,},
                                 {3, 4}});

    auto columnIt = testGrid.columnBegin();

    CHECK(*columnIt == 1);
    CHECK(*++columnIt == 3);
    CHECK(*++columnIt.row() == 4);
}