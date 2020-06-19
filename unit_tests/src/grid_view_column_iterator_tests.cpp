//
// Created by david Price on 19/06/2020.
//

#include "catch.hpp"

#include <numeric>

#include "grid.h"
#include "grid_view.h"

TEMPLATE_TEST_CASE("Test grid view column begin is correctly retrieved.", "[template]", int, long, float, double) {
    using namespace ATA;
    static const int sGridSize = 12;
    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };

    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);

    CHECK(*testGridView.columnBegin() == 6);
    CHECK(*testGridView.columnBegin(1) == 7);
    CHECK(*testGridView.columnBegin(2) == 8);
}

TEMPLATE_TEST_CASE("Test grid view column end is correctly retrieved.", "[template]", int, long, float, double) {
    using namespace ATA;
    static const int sGridSize = 12;
    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };

    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);

    CHECK(*testGridView.columnEnd() == 21);
    CHECK(*testGridView.columnEnd(1) == 22);
    CHECK(*testGridView.columnEnd(2) == 23);
}

TEMPLATE_TEST_CASE("Test grid view column is correctly retrieved.", "[template]", int, long, float, double) {
    using namespace ATA;
    static const int sGridSize = 12;
    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };

    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);

    static const std::array<TestType, 9> outputArray{ 6, 7, 8, 11, 12, 13, 16, 17, 18 };
    for(int r = 0; r < 3; ++r) {
        for(int c = 0; c < 3; ++c) {
            CHECK(*testGridView.column(c, r) == outputArray.at(c + (r * 3)));
        }
    }
}

TEMPLATE_TEST_CASE("Test grid view column front is correctly retrieved.", "[template]", int, long, float, double) {
    using namespace ATA;
    static const int sGridSize = 12;
    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };

    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);

    CHECK(testGridView.columnFront() == 6);
    CHECK(testGridView.columnFront(1) == 7);
    CHECK(testGridView.columnFront(2) == 8);
}


TEMPLATE_TEST_CASE("Test grid view column back is correctly retrieved.", "[template]", int, long, float, double) {
    using namespace ATA;
    static const int sGridSize = 12;
    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };

    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);

    CHECK(testGridView.columnBack() == 16);
    CHECK(testGridView.columnBack(1) == 17);
    CHECK(testGridView.columnBack(2) == 18);
}

TEMPLATE_TEST_CASE("Test grid view column iterator increments correctly", "[template]", int, long, float, double) {
    using namespace ATA;
    static const int sGridSize = 12;
    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };

    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);

    CHECK(*++testGridView.columnBegin() == 11);
    CHECK(*++testGridView.columnBegin(1) == 12);
    CHECK(*++testGridView.columnBegin(2) == 13);

    CHECK(*(testGridView.columnBegin() + 2) == 16);
    CHECK(*(testGridView.columnBegin(1) + 2) == 17);
    CHECK(*(testGridView.columnBegin(2) + 2) == 18);
}

TEMPLATE_TEST_CASE("Test grid view column iterator decrements correctly", "[template]", int, long, float, double) {
    using namespace ATA;
    static const int sGridSize = 12;
    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };

    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);

    CHECK(*--testGridView.columnEnd() == 16);
    CHECK(*--testGridView.columnEnd(1) == 17);
    CHECK(*--testGridView.columnEnd(2) == 18);

    CHECK(*(testGridView.columnEnd() - 2) == 11);
    CHECK(*(testGridView.columnEnd(1) - 2) == 12);
    CHECK(*(testGridView.columnEnd(2) - 2) == 13);
}

TEMPLATE_TEST_CASE("Test grid view columns work with accumulate correctly.", "[template]", int, long, float, double) {
    using namespace ATA;
    static const int sGridSize = 12;
    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };

    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);

    CHECK(std::accumulate(testGridView.columnBegin(), testGridView.columnEnd(), 0.0) == 33);
    CHECK(std::accumulate(testGridView.columnBegin(1), testGridView.columnEnd(1), 0.0) == 36);
    CHECK(std::accumulate(testGridView.columnBegin(2), testGridView.columnEnd(2), 0.0) == 39);
}