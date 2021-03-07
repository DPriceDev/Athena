//
// Created by urban on 10/06/2020.
//

#include <catch2/catch.hpp>

#include "athena_maths.h"
#include "vector.h"
//
//TEST_CASE("Test Line Intersects at zero correctly") {
//    using namespace ATA;
//    auto lineStartA = Vector2(1, 1);
//    auto lineFinishA = Vector2(-1, -1);
//    auto lineStartB = Vector2(-1, 1);
//    auto lineFinishB = Vector2(1, -1);
//
//    auto intersection = lineIntersection(lineStartA, lineFinishA, lineStartB, lineFinishB);
//
//    CHECK(intersection.value().x == 0);
//    CHECK(intersection.value().y == 0);
//}
//
//TEST_CASE("Test Line Intersects correctly") {
//    using namespace ATA;
//    auto lineStartA = Vector2(1, 10);
//    auto lineFinishA = Vector2(1, -10);
//    auto lineStartB = Vector2(-10, 1);
//    auto lineFinishB = Vector2(10, 1);
//
//    auto intersection = lineIntersection(lineStartA, lineFinishA, lineStartB, lineFinishB);
//
//    CHECK(intersection.value().x == 1);
//    CHECK(intersection.value().y == 1);
//}