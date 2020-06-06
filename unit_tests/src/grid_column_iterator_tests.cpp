//
// Created by David Price on 05/06/2020.
//

#include "catch.hpp"

#include <algorithm>

#include "grid.h"

TEST_CASE("Test column begin is correctly retrieved.") {
    using namespace ATA;
    auto testGrid = Grid2D<int>(10, 10);

    for (int i = 0; i < 10; ++i) {
        auto it = testGrid.columnBegin(i);
        *it = i * 10;
        CHECK(*it == testGrid.at(i, 0));
    }

    auto testOffsetGrid = Grid2D<int>(10, 10, -5, -5);

    for (int i = -5; i < 5; ++i) {
        auto it = testOffsetGrid.columnBegin(i);
        *it = i * 10;
        CHECK(*it == testOffsetGrid.at(i, -5));
    }
}

TEST_CASE("Test column end is correctly retrieved.") {
    using namespace ATA;
    const static size_t sGridSize = 10;
    auto testGrid = Grid2D<int>(sGridSize, sGridSize);
    const auto outputArray = std::array<int, 10>{0, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    const static int sMultiplier = 10;
    int index = 0;
    for (size_t i = 0; i < sGridSize; ++i) {
        auto it = --testGrid.columnEnd(index);
        *it = index * sMultiplier;
        CHECK(*it == testGrid.at(index, 9));
        CHECK(outputArray[i] == testGrid.at(index, 9));
        CHECK(*it == outputArray[i]);
        ++index;
    }

    auto outputOffsetArray = std::array<int, 10>{-50, -40, -30, -20, -10, 0, 10, 20, 30, 40};
    auto testOffsetGrid = Grid2D<int>(10, 10, -5, -5);

    size_t arrayIndex = 0L;
    for (int i = -5; i < 5; ++i) {
        auto it = --testOffsetGrid.columnEnd(i);
        *it = i * 10;

        CHECK(*it == testOffsetGrid.at(i, 4));
        CHECK(outputOffsetArray[arrayIndex] == testOffsetGrid.at(i, 4));
        CHECK(*it == outputOffsetArray[arrayIndex]);
        ++arrayIndex;
    }
}

TEST_CASE("Test column iterator is correctly retrieved.") {
    using namespace ATA;
    auto testGrid = Grid2D<int>(10, 10);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            auto it = testGrid.column(i, j);
            *it = (i + 1) * 10;
            CHECK(*it == testGrid.at(i, j));
        }
    }
}

TEST_CASE("Test column iterators increment and offset work correctly.") {
    using namespace ATA;
    auto testGrid = Grid2D<int>(10, 10);

    auto it = testGrid.columnBegin(0);

    int index = 0;
    while (it != testGrid.columnEnd(0)) {
        ++it;
        ++index;
    }

    CHECK(index == 10);
}

TEST_CASE("Test column iterators work with std algorithms") {
    using namespace ATA;
    auto testGrid = Grid2D<int>(10, 10);

    for (int i = 0; i < 10; ++i) {
        testGrid.at(0, i) = (i + 1) * 10;
    }

    int output = std::accumulate(testGrid.columnBegin(0), testGrid.columnEnd(0), 0);
    CHECK(output == 550);

    std::for_each(testGrid.columnBegin(1), testGrid.columnEnd(1), [](auto &value) {
        value = 100;
    });

    for (int i = 0; i < 10; ++i) {
        CHECK(testGrid.at(1, i) == 100);
    }

    const auto binaryTransform = [](const auto &valueA, const auto &valueB) {
        return valueA * valueB;
    };

    std::transform(testGrid.columnBegin(0), testGrid.columnEnd(0),
                   testGrid.columnBegin(1),
                   testGrid.columnBegin(2),
                   binaryTransform);

    std::array<int, 10> outputArray = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

    size_t arrayIndex = 0;
    for (int i = 0; i < 10; ++i, ++arrayIndex) {
        CHECK(testGrid.at(2, i) == outputArray[arrayIndex]);
    }
}

TEST_CASE("Test Column front and back returns the correct value") {
    using namespace ATA;
    auto testGrid = Grid2D<int>({{1, 2, 3, 4, 5},
                                 {6, 7, 8, 9, 10}});

    CHECK(testGrid.columnFront(0) == 1);
    CHECK(testGrid.columnFront(1) == 2);
    CHECK(testGrid.columnFront(2) == 3);
    CHECK(testGrid.columnFront(3) == 4);
    CHECK(testGrid.columnFront(4) == 5);

    CHECK(testGrid.columnBack(0) == 6);
    CHECK(testGrid.columnBack(1) == 7);
    CHECK(testGrid.columnBack(2) == 8);
    CHECK(testGrid.columnBack(3) == 9);
    CHECK(testGrid.columnBack(4) == 10);
}