//
// Created by David Price on 28/05/2020.
//

#include "../include/catch.hpp"

#include <algorithm>
#include <numeric>

#include "grid.h"

TEST_CASE("Test Grid is created correctly.") {
    using namespace ATA;
    const static size_t sGridWidth = 100L;
    const static size_t sGridHeight = 200L;

    auto grid = Grid2D<int>(sGridWidth, sGridHeight);

    auto testParams = grid.gridParameters();
    CHECK(testParams.mHeight == 200L);
    CHECK(testParams.mWidth == 100L);
    CHECK(testParams.mOriginX == 0L);
    CHECK(testParams.mOriginY == 0L);

    CHECK(grid.size().x == 100L);
    CHECK(grid.size().y == 200L);
    CHECK(grid.origin().x == 0L);
    CHECK(grid.origin().y == 0L);

    CHECK(grid.getBounds().top() == 200L);
    CHECK(grid.getBounds().right() == 100L);
    CHECK(grid.getBounds().bottom() == 0L);
    CHECK(grid.getBounds().left() == 0L);
}

TEST_CASE("Test Grid, with offset origin is created correctly.") {
    using namespace ATA;
    const static size_t sGridWidth = 100L;
    const static size_t sGridHeight = 200L;
    const static long sGridOffset = -50L;

    auto grid = Grid2D<int>(sGridWidth, sGridHeight, sGridOffset, sGridOffset);

    auto testParams = grid.gridParameters();
    CHECK(testParams.mHeight == 200L);
    CHECK(testParams.mWidth == 100L);
    CHECK(testParams.mOriginX == -50L);
    CHECK(testParams.mOriginY == -50L);

    CHECK(grid.size().x == 100L);
    CHECK(grid.size().y == 200L);
    CHECK(grid.origin().x == -50L);
    CHECK(grid.origin().y == -50L);

    CHECK(grid.getBounds().top() == 150L);
    CHECK(grid.getBounds().right() == 50L);
    CHECK(grid.getBounds().bottom() == -50L);
    CHECK(grid.getBounds().left() == -50L);
}

TEST_CASE("Test Grid parameters of one grid can be used to construct another.") {
    using namespace ATA;
    const static size_t sGridWidth = 100L;
    const static size_t sGridHeight = 200L;

    auto initialGrid = Grid2D<int>(sGridWidth, sGridHeight);
    auto grid = Grid2D<float>(initialGrid.gridParameters());

    CHECK(grid.size().x == 100L);
    CHECK(grid.size().y == 200L);
    CHECK(grid.origin().x == 0L);
    CHECK(grid.origin().y == 0L);

    CHECK(grid.getBounds().top() == 200L);
    CHECK(grid.getBounds().right() == 100L);
    CHECK(grid.getBounds().bottom() == 0L);
    CHECK(grid.getBounds().left() == 0L);
}

TEST_CASE("Test single initializer list constructor") {
    using namespace ATA;
    auto testGrid = Grid2D({0, 1, 2, 3}, 2);

    CHECK(testGrid.size().x == 2);
    CHECK(testGrid.size().y == 2);
}

TEST_CASE("Test double initializer list constructor") {
    using namespace ATA;
    const auto testGrid = Grid2D<int>({{0, 1, 2, 3, 4}, {5, 6, 7, 8, 9}});

    CHECK(testGrid.size().x == 5);
    CHECK(testGrid.size().y == 2);
}

TEST_CASE("Test if an index is in the grid") {
    using namespace ATA;
    const static size_t sGridWidth = 100L;
    const static size_t sGridHeight = 200L;
    const static long sGridOffset = -50L;

    auto grid = Grid2D<int>(sGridWidth, sGridHeight);
    auto offsetGrid = Grid2D<int>(sGridWidth, sGridHeight, sGridOffset, sGridOffset);

    CHECK(grid.isPointInGrid(50, 50));
    CHECK(grid.isPointInGrid(99, 199));
    CHECK(!grid.isPointInGrid(100, 199));
    CHECK(!grid.isPointInGrid(99, 200));
    CHECK(grid.isPointInGrid(0, 0));
    CHECK(!grid.isPointInGrid(-1, 0));
    CHECK(!grid.isPointInGrid(0, -1));

    CHECK(offsetGrid.isPointInGrid(25, 50));
    CHECK(offsetGrid.isPointInGrid(49, 149));
    CHECK(!offsetGrid.isPointInGrid(50, 149));
    CHECK(!offsetGrid.isPointInGrid(49, 150));
    CHECK(offsetGrid.isPointInGrid(0, 0));
    CHECK(!offsetGrid.isPointInGrid(-51, 0));
    CHECK(!offsetGrid.isPointInGrid(0, -51));
}

TEST_CASE("Test getting position by at()") {
    using namespace ATA;
    const static size_t sGridWidth = 100L;
    const static size_t sGridHeight = 200L;
    const static long sGridOffset = -50L;

    auto grid = Grid2D<int>(sGridWidth, sGridHeight);
    auto offsetGrid = Grid2D<int>(sGridWidth, sGridHeight, sGridOffset, sGridOffset);

    grid.at(0, 0) = 10;
    grid.at(sGridWidth - 1, sGridHeight - 1) = 20;
    grid.at(std::make_pair(40, 30)) = 30;
    grid.at(Vector2(20, 20)) = 40;
    CHECK(grid.at(0, 0) == 10);
    CHECK(grid.at(99, 199) == 20);
    CHECK(grid.at(40, 30) == 30);
    CHECK(grid.at(20, 20) == 40);

    offsetGrid.at(-50, -50) = 10;
    offsetGrid.at(49, 149) = 20;
    offsetGrid.at(std::make_pair(-40, 30)) = 30;
    offsetGrid.at(Vector2(-20, 20)) = 40;
    CHECK(offsetGrid.at(-50, -50) == 10);
    CHECK(offsetGrid.at(49, 149) == 20);
    CHECK(offsetGrid.at(-40, 30) == 30);
    CHECK(offsetGrid.at(-20, 20) == 40);

    CHECK_THROWS_AS(grid.at(100, 200) == 40, std::out_of_range);
    CHECK_THROWS_AS(offsetGrid.at(100, 200) == 40, std::out_of_range);
}

TEST_CASE("Test operator()") {
    using namespace ATA;
    auto grid = Grid2D<int>(100, 200);
    auto offsetGrid = Grid2D<int>(100, 200, -50L, -50L);

    grid(0, 0) = 50;
    offsetGrid(-50, -50) = 20;

    CHECK(grid.at(0, 0) == 50);
    CHECK(offsetGrid.at(-50, -50) == 20);
}

TEST_CASE("Test full grid vector begin and end iterators") {
    using namespace ATA;
    auto grid = Grid2D<int>(100, 200);
    auto offsetGrid = Grid2D<int>(100, 100, -50L, -50L);

    int index = 0;
    int sum = 0;
    for (const auto &point : grid) {
        sum += point;
        ++index;
    }
    CHECK(index == 20000);

    int offsetIndex = 0;
    int offsetSum = 0;
    for (const auto &point : offsetGrid) {
        offsetSum += point;
        ++offsetIndex;
    }
    CHECK(offsetIndex == 10000);
}

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
    for (int i = 0; i < 10; ++i, ++arrayIndex ) {
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

TEST_CASE("Test row front and back returns the correct value") {
    using namespace ATA;
    auto testGrid = Grid2D<int>({{1, 2},
                                 {3, 4},
                                 {5, 6},
                                 {7, 8},
                                 {9, 10}});

    CHECK(testGrid.rowFront(0) == 1);
    CHECK(testGrid.rowFront(1) == 3);
    CHECK(testGrid.rowFront(2) == 5);
    CHECK(testGrid.rowFront(3) == 7);
    CHECK(testGrid.rowFront(4) == 9);

    CHECK(testGrid.rowBack(0) == 2);
    CHECK(testGrid.rowBack(1) == 4);
    CHECK(testGrid.rowBack(2) == 6);
    CHECK(testGrid.rowBack(3) == 8);
    CHECK(testGrid.rowBack(4) == 10);
}

TEST_CASE("Test Data pointer is retrieved correctly") {
    using namespace ATA;
    auto testGrid = Grid2D<int>({{1, 2},
                                 {3, 4}});

    int* testPointer = testGrid.data();

    CHECK(*testPointer == 1);
    CHECK(*++testPointer == 2);
    CHECK(*++testPointer == 3);
    CHECK(*++testPointer == 4);
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