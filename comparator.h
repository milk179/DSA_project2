// comparator.h | Jonathan Tang | 3/26/26
#pragma once

#include "sorter.h"
#include <string>
#include <vector>


struct ComparisonResult {
    std::string datasetLabel;       
    long long quicksortMicros;      // Time for quicksort in microseconds
    long long mergesortMicros;      // Time for mergesort in microseconds
    bool quicksortCorrect;          // Whether output is actually sorted
    bool mergesortCorrect;
    size_t datasetSize;
};

class Comparator {
public:
    // Run both algorithms on the given dataset and return a ComparisonResult.
    static ComparisonResult run(const std::vector<int>& dataset, const std::string& label);

    // Print a formatted comparison result.
    static void printResult(const ComparisonResult& result);

    // Print a summary table for multiple results.
    static void printTable(const std::vector<ComparisonResult>& results);
};

