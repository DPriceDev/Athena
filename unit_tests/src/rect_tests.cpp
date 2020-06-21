//
// Created by David Price on 19/06/2020.
//

#include "catch.hpp"
#include "rect.h"

TEMPLATE_TEST_CASE("Test Rect initialized correctly", "[template]", int, long, float, double) {
    using namespace ATA;
    static const TestType sRectSize = 10;
    auto rect = Rect(sRectSize, sRectSize);

    CHECK(rect.position() == Vector2<TestType>());
    CHECK(rect.size() == Vector2<TestType>(10, 10));

    static const TestType sRectPositionX = 5;
    static const TestType sRectPositionY = 6;
    auto offsetRect = Rect(sRectPositionX, sRectPositionY, sRectSize, sRectSize);

    CHECK(offsetRect.position() == Vector2<TestType>(5, 6));
    CHECK(offsetRect.size() == Vector2<TestType>(10, 10));

    static const auto sRectPositionVector = Vector2(sRectPositionX, sRectPositionY);
    static const auto sRectSizeVector = Vector2(sRectSize, sRectSize);
    auto offsetVectorRect = Rect(sRectPositionVector, sRectSizeVector);

    CHECK(offsetVectorRect.position() == Vector2<TestType>(5, 6));
    CHECK(offsetVectorRect.size() == Vector2<TestType>(10, 10));
}

TEMPLATE_TEST_CASE("Test Rect corners are correct", "[template]", int, long, float, double) {
    using namespace ATA;
    static const TestType sRectSize = 10;
    static const TestType sRectPositionX = -5;
    static const TestType sRectPositionY = -5;
    auto rect = Rect(sRectPositionX, sRectPositionY, sRectSize, sRectSize);

    CHECK(rect.topLeft() == Vector2<TestType>(-5, 5));
    CHECK(rect.topRight() == Vector2<TestType>(5, 5));
    CHECK(rect.bottomLeft() == Vector2<TestType>(-5, -5));
    CHECK(rect.bottomRight() == Vector2<TestType>(5, -5));
}

TEMPLATE_TEST_CASE("Test Rect vertices are correct", "[template]", int, long, float, double) {
    using namespace ATA;
    static const TestType sRectSize = 10;
    static const TestType sRectPositionX = -5;
    static const TestType sRectPositionY = -5;
    auto rect = Rect(sRectPositionX, sRectPositionY, sRectSize, sRectSize);

    static const std::array<Vector2<TestType>, 4> sOutputArray{
            Vector2<TestType>(-5, 5),
            Vector2<TestType>(5, 5),
            Vector2<TestType>(5, -5),
            Vector2<TestType>(-5, -5)};

    CHECK(rect.vertices() == sOutputArray);
}

TEMPLATE_TEST_CASE("Test Rect overlapping another Rect", "[template]", int, long, float, double) {
    using namespace ATA;
    static const TestType sRectSize = 10;
    static const TestType sRectPositionX = -5;
    static const TestType sRectPositionY = -5;
    static const TestType sOverlappingOffset = 9;
    static const TestType sNonOverlappingOffset = 11;

    auto rect = Rect(sRectPositionX, sRectPositionY, sRectSize, sRectSize);
    auto overlappingRect = Rect(sRectPositionX + sOverlappingOffset, sRectPositionY + sOverlappingOffset, sRectSize, sRectSize);
    CHECK(rect.isOverlapping(overlappingRect));

    auto negativeOverlappingRect = Rect(sRectPositionX - sOverlappingOffset, sRectPositionY - sOverlappingOffset, sRectSize, sRectSize);
    CHECK(rect.isOverlapping(negativeOverlappingRect));

    auto nonOverlappingRect = Rect(sRectPositionX + sNonOverlappingOffset, sRectPositionY + sNonOverlappingOffset, sRectSize, sRectSize);
    CHECK(!rect.isOverlapping(nonOverlappingRect));

    auto negativeNonOverlappingRect = Rect(sRectPositionX - sNonOverlappingOffset, sRectPositionY - sNonOverlappingOffset, sRectSize, sRectSize);
    CHECK(!rect.isOverlapping(negativeNonOverlappingRect));
}

TEMPLATE_TEST_CASE("Test Rect overlapping another Rect edge cases", "[template]", int, long, float, double) {
    using namespace ATA;
    static const TestType sRectSize = 10;
    static const TestType sOffset = -10;

    auto topLeftRect = Rect<TestType>(sOffset, 0, sRectSize, sRectSize);
    auto topRightRect = Rect<TestType>(-0, 0, sRectSize, sRectSize);
    auto bottomLeftRect = Rect<TestType>(sOffset, sOffset, sRectSize, sRectSize);
    auto bottomRightRect = Rect<TestType>(sOffset, sOffset, sRectSize, sRectSize);

    CHECK(topLeftRect.isOverlapping(topRightRect));
    CHECK(topRightRect.isOverlapping(bottomRightRect));
    CHECK(bottomRightRect.isOverlapping(bottomLeftRect));
    CHECK(bottomLeftRect.isOverlapping(topLeftRect));
}

TEMPLATE_TEST_CASE("Test Rect midpoint retrieved correctly", "[template]", int, long, float, double) {
    using namespace ATA;
    static const TestType sRectSize = 10;
    static const TestType sRectPositionX = 10;
    static const TestType sRectPositionY = 14;

    static const Vector2<float> output{15, 19};
    auto rect = Rect(sRectPositionX, sRectPositionY, sRectSize, sRectSize);
    CHECK(rect.midpoint() == output);

    static const TestType sNegativeRectPositionX = -10;
    static const TestType sNegativeRectPositionY = -14;
    static const Vector2<float> negativeOutput{-5, -9};
    auto negativeRect = Rect(sNegativeRectPositionX, sNegativeRectPositionY, sRectSize, sRectSize);

    CHECK(negativeRect.midpoint() == negativeOutput);
}


TEMPLATE_TEST_CASE("Test Rect area retrieved correctly", "[template]", int, long, float, double) {
    using namespace ATA;
    static const TestType sRectSize = 10;
    static const TestType sRectPositionX = 10;
    static const TestType sRectPositionY = 14;

    static const double output{100.0};
    auto rect = Rect(sRectPositionX, sRectPositionY, sRectSize, sRectSize);
    CHECK(rect.area() == output);

    static const TestType sNegativeRectPositionX = -10;
    static const TestType sNegativeRectPositionY = -14;
    static const Vector2<TestType> negativeOutput{-5, -9};
    auto negativeRect = Rect(sNegativeRectPositionX, sNegativeRectPositionY, sRectSize, sRectSize);

    CHECK(negativeRect.area() == output);

    static const TestType sRectSizeY = 5;
    static const TestType shortOutput{50};
    auto shortRect = Rect(sNegativeRectPositionX, sNegativeRectPositionY, sRectSize, sRectSizeY);
    CHECK(shortRect.area() == shortOutput);
}