//
// Created by David Price on 02/06/2020.
//

#include "catch.hpp"

#include "grid.h"
#include "grid_view.h"

TEST_CASE("Test Initialization of a matching grid view") {
    using namespace ATA;
    auto testGrid = Grid2D<int>({{20,2,3,4,5},
                                 {1,2,3,4,5},
                                 {1,2,3,4,5},
                                 {1,2,3,4,5},
                                 {1,2,3,4,10}});

   auto gridView = GridView(testGrid);

   CHECK(*gridView.begin() == 20);
   CHECK(*--gridView.end() == 10);
}

TEST_CASE("Test Initialization of a smaller grid view") {
    using namespace ATA;
    auto testGrid = Grid2D<int>({{1,2,3,4,5},
                                 {6,7,8,9,10},
                                 {11,12,13,14,15},
                                 {16,17,18,19,20},
                                 {21,22,23,24,25}});

    auto gridView = GridView(testGrid, 1, 1, 3, 3);

    CHECK(*gridView.begin() == 7);
    CHECK(*--gridView.end() == 19);
}

TEST_CASE("Test Initialization of a smaller grid view with vector2") {
    using namespace ATA;
    auto testGrid = Grid2D<int>({{1,2,3,4,5},
                                 {6,7,8,9,10},
                                 {11,12,13,14,15},
                                 {16,17,18,19,20},
                                 {21,22,23,24,25}});

    auto testBottomLeft = Vector2<int>(1,1);
    auto testTopRight = Vector2<int>(3,3);

    auto gridView = GridView(testGrid, testBottomLeft, testTopRight);

    CHECK(*gridView.begin() == 7);
    CHECK(*--gridView.end() == 19);
}

TEST_CASE("Test gridview iterator iterates through the array correctly") {
    using namespace ATA;
    auto testGrid = Grid2D<int>({{1,2,3,4,5},
                                 {6,7,8,9,10},
                                 {11,12,13,14,15},
                                 {16,17,18,19,20},
                                 {21,22,23,24,25}});

    auto gridView = GridView(testGrid);

    auto it = gridView.begin();
    for(int i = 0; i < 25; ++i) {
        CHECK(*it == i + 1);
        ++it;
    }

    auto testBottomLeft = Vector2<int>(1,1);
    auto testTopRight = Vector2<int>(3,3);

    auto smallGridView = GridView(testGrid, testBottomLeft, testTopRight);
    int outputArray[] = { 7, 8, 9, 12, 13, 14, 17, 18, 19};
    auto smallIt = smallGridView.begin();
    for(int output : outputArray) {
        CHECK(*smallIt == output);
        ++smallIt;
    }
}

TEST_CASE("Test gridview iterator iterates in reverse through the array correctly") {
    using namespace ATA;
    auto testGrid = Grid2D<int>({{1,2,3,4,5},
                                 {6,7,8,9,10},
                                 {11,12,13,14,15},
                                 {16,17,18,19,20},
                                 {21,22,23,24,25}});

    auto gridView = GridView(testGrid);

    auto it = gridView.end();
    for(int i = 24; i > -1; --i) {
        CHECK(*--it == i + 1);
    }

    auto testBottomLeft = Vector2<int>(1,1);
    auto testTopRight = Vector2<int>(3,3);

    auto smallGridView = GridView(testGrid, testBottomLeft, testTopRight);
    int outputArray[] = { 19, 18, 17, 14, 13, 12, 9, 8, 7};
    auto smallIt = smallGridView.end();
    for(int output : outputArray) {
        CHECK(*--smallIt == output);
    }
}