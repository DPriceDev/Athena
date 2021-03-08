//
// Created by david Price on 19/06/2020.
//

#include <catch2/catch.hpp>

#include <numeric>

#include "grid.h"
#include "grid_view.h"

TEMPLATE_TEST_CASE("Test grid view row begin is correctly retrieved.", "[template]", int, long, float, double) {
    using namespace ATA;
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

    CHECK(*testGridView.rowBegin() == 6);
    CHECK(*testGridView.rowBegin(1) == 11);
    CHECK(*testGridView.rowBegin(2) == 16);
}

TEMPLATE_TEST_CASE("Test grid view row end is correctly retrieved.", "[template]", int, long, float, double) {
    using namespace ATA;
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

    CHECK(*testGridView.rowEnd() == 9);
    CHECK(*testGridView.rowEnd(1) == 14);
    CHECK(*testGridView.rowEnd(2) == 19);
}

TEMPLATE_TEST_CASE("Test grid view row is correctly retrieved.", "[template]", int, long, float, double) {
    using namespace ATA;
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
            CHECK(*testGridView.row(c, r) == outputArray[static_cast<unsigned long>(c + (r * 3))]);
        }
    }
}

TEMPLATE_TEST_CASE("Test grid view row front is correctly retrieved.", "[template]", int, long, float, double) {
    using namespace ATA;
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

    CHECK(testGridView.rowFront() == 6);
    CHECK(testGridView.rowFront(1) == 11);
    CHECK(testGridView.rowFront(2) == 16);
}


TEMPLATE_TEST_CASE("Test grid view row back is correctly retrieved.", "[template]", int, long, float, double) {
    using namespace ATA;
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

    CHECK(testGridView.rowBack() == 8);
    CHECK(testGridView.rowBack(1) == 13);
    CHECK(testGridView.rowBack(2) == 18);
}

TEMPLATE_TEST_CASE("Test grid view row iterator increments correctly", "[template]", int, long, float, double) {
    using namespace ATA;
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

    CHECK(*++testGridView.rowBegin() == 7);
    CHECK(*++testGridView.rowBegin(1) == 12);
    CHECK(*++testGridView.rowBegin(2) == 17);

    CHECK(*(testGridView.rowBegin() + 2) == 8);
    CHECK(*(testGridView.rowBegin(1) + 2) == 13);
    CHECK(*(testGridView.rowBegin(2) + 2) == 18);
}

TEMPLATE_TEST_CASE("Test grid view row iterator decrements correctly", "[template]", int, long, float, double) {
    using namespace ATA;
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

    CHECK(*--testGridView.rowEnd() == 8);
    CHECK(*--testGridView.rowEnd(1) == 13);
    CHECK(*--testGridView.rowEnd(2) == 18);

    CHECK(*(testGridView.rowEnd() - 2) == 7);
    CHECK(*(testGridView.rowEnd(1) - 2) == 12);
    CHECK(*(testGridView.rowEnd(2) - 2) == 17);
}

TEMPLATE_TEST_CASE("Test grid view rows work with accumulate correctly.", "[template]", int, long, float, double) {
    using namespace ATA;
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

    CHECK(std::accumulate(testGridView.rowBegin(), testGridView.rowEnd(), 0.0) == 21);
    CHECK(std::accumulate(testGridView.rowBegin(1), testGridView.rowEnd(1), 0.0) == 36);
    CHECK(std::accumulate(testGridView.rowBegin(2), testGridView.rowEnd(2), 0.0) == 51);
}