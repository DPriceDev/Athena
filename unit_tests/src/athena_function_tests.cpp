//
// Created by David Price on 27/05/2020.
//
#include "catch.hpp"

#include <array>
#include <map>
#include <vector>

#include "athena_functions.h"

TEST_CASE("Test All vector values are transformed if predicate is true") {
    auto testVectorIn = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto testVectorOut = std::vector<int>();

    auto const predicate = [](const auto &value) {
        return value == value;
    };

    auto const transform = [](const auto &value) {
        return value * 2;
    };

    ATA::transform_if(testVectorIn.begin(), testVectorIn.end(), std::back_inserter(testVectorOut),
                      transform, predicate);

    CHECK(testVectorOut == std::vector<int>{0, 2, 4, 6, 8, 10, 12, 14, 16, 18});
}

TEST_CASE("Test All vector values are transformed if predicate is false") {
    auto testVectorIn = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto testVectorOut = std::vector<int>();

    auto const predicate = [](const auto &value) {
        return value != value;
    };

    auto const transform = [](const auto &value) {
        return value * 2;
    };

    ATA::transform_if(testVectorIn.begin(), testVectorIn.end(), std::back_inserter(testVectorOut),
                      transform,
                      predicate);

    CHECK(testVectorOut.empty());
}

TEST_CASE("Test only odd vector values are transformed") {
    auto testVectorIn = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto testVectorOut = std::vector<int>();

    auto const predicate = [](const auto &value) {
        return value % 2 != 0;
    };

    auto const transform = [](const auto &value) {
        return value * 2;
    };

    ATA::transform_if(testVectorIn.begin(), testVectorIn.end(), std::back_inserter(testVectorOut),
                      transform,
                      predicate);

    CHECK(testVectorOut == std::vector<int>{2, 6, 10, 14, 18});
}

TEST_CASE("Test transform if works for arrays and maps if values are odd") {
    auto testArrayIn = std::array<int, 5>{0, 1, 2, 3, 4};
    auto testArrayOut = std::array<int, 5>{};

    auto testMapIn = std::map<int, int>{{0, 0},
                                        {1, 1},
                                        {2, 2},
                                        {3, 3}};
    auto testMapOut = std::map<int, int>{};

    auto const predicate = [](const auto &value) {
        return value % 2 != 0;
    };

    auto const transform = [](const auto &value) {
        return value * 2;
    };

    ATA::transform_if(testArrayIn.begin(), testArrayIn.end(), testArrayOut.begin(), transform, predicate);

    CHECK(testArrayOut == std::array<int, 5>{2, 6});

    auto const mapPredicate = [](const auto &value) {
        return value.second % 2 != 0;
    };

    auto const mapTransform = [](const auto &value) {
        return std::make_pair(value.first, value.second * 2);
    };

    ATA::transform_if(testMapIn.begin(), testMapIn.end(), std::inserter(testMapOut, testMapOut.end()),
                      mapTransform,
                      mapPredicate);

    CHECK(testMapOut == std::map<int, int>{{1, 2}, {3, 6}});
}

TEST_CASE("Test transform from map to vector, if values are odd") {
    auto testMapIn = std::map<int, int>{{0, 0},
                                        {1, 1},
                                        {2, 2},
                                        {3, 3}};
    auto testVectorOut = std::vector<int>{};

    auto const mapPredicate = [](const auto &value) {
        return value.second % 2 != 0;
    };

    auto const mapToVectorTransform = [](const auto &value) {
        return value.second * 2;
    };

    ATA::transform_if(testMapIn.begin(),
                      testMapIn.end(),
                      std::back_inserter(testVectorOut),
                      mapToVectorTransform,
                      mapPredicate);

    CHECK(testVectorOut == std::vector<int>{2, 6});
}


TEST_CASE("Test All vector values are Binary transformed if predicate is true") {
    auto testVectorIn = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto testVectorIn2 = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto testVectorOut = std::vector<int>();

    auto const predicate = [](const auto &value1, const auto &value2) {
        return value1 == value1 && value2 == value2;
    };

    auto const transform = [](const auto &value1, const auto &value2) {
        return (value1 * value2);
    };

    ATA::transform_if(testVectorIn.begin(), testVectorIn.end(), testVectorIn2.begin(),
                      std::back_inserter(testVectorOut),
                      transform,
                      predicate);

    CHECK(testVectorOut == std::vector<int>{0, 1, 4, 9, 16, 25, 36, 49, 64, 81});
}

TEST_CASE("Test All vector values are Binary transformed if predicate is false") {
    auto testVectorIn = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto testVectorIn2 = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto testVectorOut = std::vector<int>();

    auto const predicate = [](const auto &value1, const auto &value2) {
      return value1 != value1 && value2 != value2;
    };

    auto const transform = [](const auto &value1, const auto &value2) {
      return (value1 * value2);
    };

    ATA::transform_if(testVectorIn.begin(), testVectorIn.end(), testVectorIn2.begin(),
                      std::back_inserter(testVectorOut),
                      transform,
                      predicate);

    CHECK(testVectorOut.empty());
}

TEST_CASE("Test only odd vector values are Binary transformed") {
    auto testVectorIn = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto testVectorIn2 = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto testVectorOut = std::vector<int>();

    auto const predicate = [](const auto &value1, const auto &value2) {
      return value1 % 2 != 0 && value2 % 2 != 0;
    };

    auto const transform = [](const auto &value1, const auto &value2) {
      return (value1 * value2);
    };

    ATA::transform_if(testVectorIn.begin(), testVectorIn.end(), testVectorIn2.begin(),
                      std::back_inserter(testVectorOut),
                      transform,
                      predicate);

    CHECK(testVectorOut == std::vector<int>{1, 9, 25, 49, 81});
}

TEST_CASE("Test Binary transform if works for arrays and maps if values are odd") {
    auto testArrayIn = std::array<int, 5>{0, 1, 2, 3, 4};
    auto testArrayIn2 = std::array<int, 5>{0, 1, 2, 3, 4};
    auto testArrayOut = std::array<int, 5>{};

    auto testMapIn = std::map<int, int>{{0, 0},
                                        {1, 1},
                                        {2, 2},
                                        {3, 3}};
    auto testMapIn2 = std::map<int, int>{{0, 0},
                                        {1, 1},
                                        {2, 2},
                                        {3, 3}};
    auto testMapOut = std::map<int, int>{};

    auto const predicate = [](const auto &value1, const auto &value2) {
      return value1 % 2 != 0 && value2 % 2 != 0;
    };

    auto const transform = [](const auto &value1, const auto &value2) {
      return value1 * value2;
    };

    ATA::transform_if(testArrayIn.begin(), testArrayIn.end(), testArrayIn2.begin(),
                      testArrayOut.begin(),
                      transform,
                      predicate);

    CHECK(testArrayOut == std::array<int, 5>{1, 9});

    auto const mapPredicate = [](const auto &value1, const auto &value2) {
      return value1.second % 2 != 0 && value2.second % 2 != 0;
    };

    auto const mapTransform = [](const auto &value1, const auto &value2) {
      return std::make_pair(value1.first, value1.second * value2.second);
    };

    ATA::transform_if(testMapIn.begin(), testMapIn.end(), testMapIn2.begin(),
                      std::inserter(testMapOut, testMapOut.end()),
                      mapTransform,
                      mapPredicate);

    CHECK(testMapOut == std::map<int, int>{{1, 1}, {3, 9}});
}

TEST_CASE("Test Binary transform from map to vector, if values are odd") {
    auto testMapIn = std::map<int, int>{{0, 0},
                                        {1, 1},
                                        {2, 2},
                                        {3, 3}};
    auto testVectorIn = std::vector<int>{0, 1, 2, 3};
    auto testVectorOut = std::vector<int>{};

    auto const mapPredicate = [](const auto &value1, const auto &value2) {
      return value2 % 2 != 0 && value1.second % 2 != 0;
    };

    auto const mapToVectorTransform = [](const auto &value1, const auto &value2) {
      return value1.second * value2;
    };

    ATA::transform_if(testMapIn.begin(),
                      testMapIn.end(),
                      testVectorIn.begin(),
                      std::back_inserter(testVectorOut),
                      mapToVectorTransform,
                      mapPredicate);

    CHECK(testVectorOut == std::vector<int>{1, 9});
}