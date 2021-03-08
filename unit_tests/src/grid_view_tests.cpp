//
// Created by David Price on 02/06/2020.
//

#include <catch2/catch.hpp>

#include "grid.h"
#include "grid_view.h"

TEMPLATE_TEST_CASE("Test Initialization of a smaller grid view ", "[template]", int, long, float, double) {
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

   CHECK(*testGridView.begin() == 6);
   CHECK(*--testGridView.end() == 18);
}

TEMPLATE_TEST_CASE("Test Initialization of a matching grid view", "[template]", int, long, float, double) {
    using namespace ATA;
    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid);

    CHECK(*testGridView.begin() == 0);
    CHECK(*--testGridView.end() == 24);
}

TEMPLATE_TEST_CASE("Test gridview iterator iterates through the array correctly", "[template]", int, long, float, double) {
    using namespace ATA;
    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid);

    static const auto sGridLength = 25;
    auto it = testGridView.begin();
    for(int i = 0; i < sGridLength; ++i) {
        CHECK(static_cast<float>(*it) == static_cast<float>(i));
        ++it;
    }

    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };
    static const std::array<TestType, 9> outputArray{ 6, 7, 8, 11, 12, 13, 16, 17, 18};

    static auto testSmallGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);
    auto smallIt = testSmallGridView.begin();
    for(TestType output : outputArray) {
        CHECK(*smallIt == output);
        ++smallIt;
    }
}

TEMPLATE_TEST_CASE("Test gridview iterator iterates in reverse through the array correctly", "[template]", int, long, float, double) {
    using namespace ATA;
    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid);
    static const auto sGridLength = 25;

    auto it = testGridView.end();
    for(int i = sGridLength - 1; i > -1; --i) {
        CHECK(static_cast<float>(*--it) == static_cast<float>(i));
    }

    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };
    static const std::array<TestType, 9> outputArray{ 18, 17, 16, 13, 12, 11, 8, 7, 6};

    static auto testSmallGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);
    auto smallIt = testSmallGridView.end();
    for(TestType output : outputArray) {
        CHECK(*--smallIt == output);
    }
}

TEMPLATE_TEST_CASE("Test gridview iterator with a variable offset added", "[template]", int, long, float, double) {
    using namespace ATA;
    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid);

    CHECK(*(testGridView.begin() + 3) == 3);
    CHECK(*(testGridView.begin() + 6) == 6);

    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };

    static auto testSmallGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);
    CHECK(*(testSmallGridView.begin() + 1) == 7);
    CHECK(*(testSmallGridView.begin() + 4) == 12);
    CHECK(*(testSmallGridView.begin() + 6) == 16);
    CHECK(*(testSmallGridView.begin() + 8) == 18);
}

TEMPLATE_TEST_CASE("Test gridview iterator with a variable offset subtracted", "[template]", int, long, float, double) {
    using namespace ATA;
    static const std::initializer_list<std::initializer_list<TestType>> testGridValues = {
            { 0, 1, 2, 3, 4 },
            { 5, 6, 7, 8, 9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 }};

    static auto testGrid = Grid2D<TestType>(testGridValues);
    static auto testGridView = GridView<TestType>(testGrid);

    CHECK(*(--testGridView.end() - 3) == 21);
    CHECK(*(--testGridView.end() - 6) == 18);

    static const Vector2<int> sGridViewStart{ 1, 1 };
    static const Vector2<int> sGridViewEnd{ 3, 3 };

    static auto testSmallGridView = GridView<TestType>(testGrid, sGridViewStart, sGridViewEnd);
    CHECK(*(--testSmallGridView.end() - 1) == 17);
    CHECK(*(--testSmallGridView.end() - 4) == 12);
    CHECK(*(--testSmallGridView.end() - 6) == 8);
    CHECK(*(--testSmallGridView.end() - 8) == 6);
}

TEMPLATE_TEST_CASE("Test Grid View Operator() retrieves values correctly", "[template]", int, long, float, double) {
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
            CHECK(testGridView(c, r) == outputArray[static_cast<unsigned long>(c + (r * 3))]);
        }
    }
}