//
// Created by David Price on 05/06/2020.
//

#include <catch2/catch.hpp>
#include <algorithm>
#include <numeric>

#include "grid.h"

TEST_CASE("Test column begin is correctly retrieved.") {
    static const int sGridSize = 10;
    static const int sGridOffset = -5;
    using namespace ATA;
    auto testGrid = Grid2D<int>(sGridSize, sGridSize);

    for (int i = 0; i < sGridSize; ++i) {
        auto it = testGrid.columnBegin(i);
        *it = i * sGridSize;
        CHECK(*it == testGrid.at(i, 0));
    }

    auto testOffsetGrid = Grid2D<int>(sGridSize, sGridSize, sGridOffset, sGridOffset);

    for (int i = sGridOffset; i < sGridOffset + sGridSize; ++i) {
        auto it = testOffsetGrid.columnBegin(i);
        *it = i * sGridSize;
        CHECK(*it == testOffsetGrid.at(i, -5));
    }
}

TEST_CASE("Test column end is correctly retrieved.") {
    using namespace ATA;
    static const int sGridSize = 10;
    static const int sGridOffset = -5;
    auto testGrid = Grid2D<int>(sGridSize, sGridSize);
    const auto outputArray = std::array<int, 10>{0, 10, 20, 30, 40,
                                                 50, 60, 70, 80, 90};

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

    const auto outputOffsetArray = std::array<int, 10>{-50, -40, -30, -20, -10,
                                                       0, 10, 20, 30, 40};

    auto testOffsetGrid = Grid2D<int>(sGridSize, sGridSize, sGridOffset, sGridOffset);

    size_t arrayIndex = 0L;
    for (int i = sGridOffset; i < sGridOffset + sGridSize; ++i) {
        auto it = --testOffsetGrid.columnEnd(i);
        *it = i * sGridSize;

        CHECK(*it == testOffsetGrid.at(i, 4));
        CHECK(outputOffsetArray[arrayIndex] == testOffsetGrid.at(i, 4));
        CHECK(*it == outputOffsetArray[arrayIndex]);
        ++arrayIndex;
    }
}

TEST_CASE("Test column iterator is correctly retrieved.") {
    static const int sGridSize = 10;
    using namespace ATA;
    auto testGrid = Grid2D<int>(sGridSize, sGridSize);

    for (int i = 0; i < sGridSize; ++i) {
        for (int j = 0; j < sGridSize; ++j) {
            auto it = testGrid.column(i, j);
            *it = (i + 1) * sGridSize;
            CHECK(*it == testGrid.at(i, j));
        }
    }
}

TEST_CASE("Test column iterators increment and offset work correctly.") {
    static const int sGridSize = 10;
    using namespace ATA;
    auto testGrid = Grid2D<int>(sGridSize, sGridSize);

    auto it = testGrid.columnBegin(0);

    int index = 0;
    while (it != testGrid.columnEnd(0)) {
        ++it;
        ++index;
    }

    CHECK(index == 10);
}

TEST_CASE("Test column iterators work with std algorithms") {
    static const int sGridSize = 10;
    using namespace ATA;
    auto testGrid = Grid2D<int>(sGridSize, sGridSize);

    for (int i = 0; i < sGridSize; ++i) {
        testGrid.at(0, i) = (i + 1) * sGridSize;
    }

    int output = std::accumulate(testGrid.columnBegin(0), testGrid.columnEnd(0), 0);
    CHECK(output == 550);

    static const int fillValue = 100;
    std::fill(testGrid.columnBegin(1), testGrid.columnEnd(1), fillValue);

    for (int i = 0; i < sGridSize; ++i) {
        CHECK(testGrid.at(1, i) == 100);
    }
}

TEST_CASE("Test Transform with column iterators") {
    static const int sGridSize = 10;
    using namespace ATA;
    auto testGrid = Grid2D<int>(sGridSize, sGridSize);

    std::generate(testGrid.columnBegin(0), testGrid.columnEnd(0), []() {
        static int i{1};
        return i++;
    });


    const auto unaryTransform = [](const auto &value) {
        static int i{1};
        return value * i++;
    };

    std::transform(testGrid.columnBegin(0),
                   testGrid.columnEnd(0),
                   testGrid.columnBegin(1),
                   unaryTransform);

    const std::array<int, 10> outputArray = {1, 4, 9, 16, 25,
                                             36, 49, 64, 81, 100};

    size_t arrayIndex = 0;
    for (int i = 0; i < sGridSize; ++i, ++arrayIndex) {
        CHECK(testGrid.at(1, i) == outputArray[arrayIndex]);
    }

    const auto binaryTransform = [](const auto &valueA, const auto &valueB) {
        return valueA * valueB;
    };

    std::transform(testGrid.columnBegin(0), testGrid.columnEnd(0),
                   testGrid.columnBegin(1),
                   testGrid.columnBegin(2),
                   binaryTransform);

    const std::array<int, 10> outputBinaryArray = {1, 8, 27, 64, 125,
                                                   216, 343, 512, 729, 1000};

    arrayIndex = 0;
    for (int i = 0; i < sGridSize; ++i, ++arrayIndex) {
        CHECK(testGrid.at(2, i) == outputBinaryArray[arrayIndex]);
    }
}

TEST_CASE("Test Column front and back returns the correct value") {
    using namespace ATA;
    using namespace std;
    static const initializer_list<initializer_list<int>> initList = {{1, 2, 3, 4, 5},
                                                                     {6, 7, 8, 9, 10}};
    auto testGrid = Grid2D<int>(initList);

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