//
// Created by David Price on 28/05/2020.
//

#include "catch.hpp"

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
