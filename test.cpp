//
// Created by Samuel Arango on 3/28/26.
//
#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <vector>
#include "sorter.h"
#include "dataloader.h"
#include "comparator.h"

bool sorted(const std::vector<int>& vec) {
    return std::is_sorted(vec.begin(), vec.end());
}

TEST_CASE("Sorting Algorithm Accuracy", "[sorter]") {
    SECTION("Quicksort Random vector") {
        std::vector<int> data = {5, 2, 9, 1, 5, 6};

        sorter mySorter(data);

        std::vector<int> result = mySorter.quicksort();

        CHECK(sorted(result));
    }

    SECTION("Mergesort Random vector") {
        std::vector<int> data = {5, 2, 9, 1, 5, 6};
        sorter mySorter(data);
        std::vector<int> result = mySorter.mergesort();

        CHECK(sorted(result));
    }
}

TEST_CASE("Comparator Result Validation", "[comparator]") {
    auto data = DataLoader::generateRandom(100);

    SECTION("Comparator does valid timing/size") {
        ComparisonResult result = Comparator::run(data, "Test Run");

        CHECK(result.datasetSize == 100);
        CHECK(result.datasetLabel == "Test Run");
        CHECK(result.quicksortMicros >= 0);
        CHECK(result.mergesortMicros >= 0);
    }
}