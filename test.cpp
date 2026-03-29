//Samuel

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <vector>

#include "comparator.h"
#include "dataloader.h"
#include "sorter.h"

static void checkBothSorts(const std::vector<int>& input) {
    auto expected = input;
    std::sort(expected.begin(), expected.end());

    sorter quicksorter(input);
    sorter mergesorter(input);

    CHECK(quicksorter.quicksort() == expected);
    CHECK(mergesorter.mergesort() == expected);
}

TEST_CASE("Sorters handle edge cases", "[sorter]") {
    SECTION("empty input") {
        checkBothSorts({});
    }

    SECTION("single value") {
        checkBothSorts({42});
    }

    SECTION("two values") {
        checkBothSorts({2, 1});
    }

    SECTION("already sorted") {
        checkBothSorts({1, 2, 3, 4, 5, 6});
    }

    SECTION("reverse sorted") {
        checkBothSorts({6, 5, 4, 3, 2, 1});
    }

    SECTION("all equal") {
        checkBothSorts({7, 7, 7, 7, 7});
    }

    SECTION("duplicates") {
        checkBothSorts({5, 2, 9, 1, 5, 6, 2, 9});
    }

    SECTION("mixed negative and positive values") {
        checkBothSorts({9, -1, 5, 0, -1, 9, 3});
    }
}

TEST_CASE("Comparator reports metadata and correctness", "[comparator]") {
    std::vector<int> data = {5, 2, 9, 1, 5, 6};

    ComparisonResult result = Comparator::run(data, "Test Run");

    CHECK(result.datasetSize == data.size());
    CHECK(result.datasetLabel == "Test Run");
    CHECK(result.quicksortMicros >= 0);
    CHECK(result.mergesortMicros >= 0);
    CHECK(result.quicksortCorrect);
    CHECK(result.mergesortCorrect);
}

TEST_CASE("DataLoader helpers behave as expected", "[dataloader]") {
    SECTION("generate random returns requested size") {
        auto data = DataLoader::generateRandom(100, 50);
        CHECK(data.size() == 100);
    }

    SECTION("generate nearly sorted returns requested size") {
        auto data = DataLoader::generateNearlySorted(100, 0.10);
        CHECK(data.size() == 100);
    }

    SECTION("generate reverse sorted returns descending values") {
        auto data = DataLoader::generateReverseSorted(5);
        CHECK(data == std::vector<int>{5, 4, 3, 2, 1});
    }

    SECTION("isSorted accepts ordered data and rejects unordered data") {
        CHECK(DataLoader::isSorted({}));
        CHECK(DataLoader::isSorted({1, 1, 2, 3}));
        CHECK_FALSE(DataLoader::isSorted({3, 1, 2}));
    }
}
