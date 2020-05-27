//
// Created by David Price on 27/05/2020.
//
#include "catch2/catch.hpp"

#include <vector>
#include <array>
#include <map>

#include "athena_functions.h"

TEST_CASE("Test All vector values are transformed if predicate is true") {
    auto testVectorIn = std::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto testVectorOut = std::vector<int>();

    auto const predicate = [] (const auto & value) {
        return true;
    };

    auto const transform = [] (const auto & value) {
        return value * 2;
    };

    ATA::transform_if(testVectorIn.begin(), testVectorIn.end(), std::back_inserter(testVectorOut),
                      transform, predicate);

    CHECK(testVectorOut == std::vector<int>{ 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 });
}

TEST_CASE("Test All vector values are transformed if predicate is false") {
    auto testVectorIn = std::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto testVectorOut = std::vector<int>();

    auto const predicate = [] (const auto & value) {
        return false;
    };

    auto const transform = [] (const auto & value) {
        return value * 2;
    };

    ATA::transform_if(testVectorIn.begin(), testVectorIn.end(), std::back_inserter(testVectorOut),
                      transform,
                      predicate);

    CHECK(testVectorOut.empty());
}

TEST_CASE("Test only odd vector values are transformed") {
    auto testVectorIn = std::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto testVectorOut = std::vector<int>();

    auto const predicate = [] (const auto & value) {
        return value % 2 != 0;
    };

    auto const transform = [] (const auto & value) {
        return value * 2;
    };

    ATA::transform_if(testVectorIn.begin(), testVectorIn.end(), std::back_inserter(testVectorOut),
                      transform,
                      predicate);

    CHECK(testVectorOut == std::vector<int>{ 2, 6, 10, 14, 18 });
}

TEST_CASE("Test transform if works for arrays and maps if values are odd") {
    auto testArrayIn = std::array<int, 5>{ 0, 1, 2, 3, 4 };
    auto testArrayOut = std::array<int, 5>{ };

    auto testMapIn = std::map<int, int>{ { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 } };
    auto testMapOut = std::map<int, int>{ };

    auto const predicate = [] (const auto & value) {
        return value % 2 != 0;
    };

    auto const transform = [] (const auto & value) {
        return value * 2;
    };

    ATA::transform_if(testArrayIn.begin(), testArrayIn.end(), testArrayOut.begin(), transform, predicate);

    CHECK(testArrayOut == std::array<int, 5>{ 2, 6 });

    auto const mapPredicate = [] (const auto & value) {
        return value.second % 2 != 0;
    };

    auto const mapTransform = [] (const auto & value) {
        return std::make_pair(value.first, value.second * 2);
    };

    ATA::transform_if(testMapIn.begin(), testMapIn.end(), std::inserter(testMapOut, testMapOut.end()),
                      mapTransform,
                      mapPredicate);

    CHECK(testMapOut == std::map<int, int>{ { 1, 2 }, { 3, 6 } });
}

TEST_CASE("Test transform from map to vector, if values are odd") {
    auto testMapIn = std::map<int, int>{ { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 } };
    auto testVectorOut = std::vector<int>{ };

    auto const mapPredicate = [] (const auto & value) {
        return value.second % 2 != 0;
    };

    auto const mapToVectorTransform = [] (const auto & value) {
        return value.second * 2;
    };

    ATA::transform_if(testMapIn.begin(), testMapIn.end(), std::back_inserter(testVectorOut),
            mapToVectorTransform,
            mapPredicate);

    CHECK(testVectorOut == std::vector<int>{ 2, 6 });
}