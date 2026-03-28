// comparator.h | Jonathan Tang | 3/26/26

#include "comparator.h"
#include "dataloader.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

ComparisonResult Comparator::run(const std::vector<int>& dataset, const std::string& label) {
    // Save the dataset details once, then run mergesort and quicksort.
    ComparisonResult result;
    result.datasetLabel  = label;
    result.datasetSize   = dataset.size();

    // Measure mergesort and record whether the returned data is sorted correctly.
    {
        sorter s(dataset);
        std::vector<int> msResult = s.mergesort();
        result.mergesortMicros  = s.getMicros().count();
        result.mergesortCorrect = DataLoader::isSorted(msResult);
    }

    // Measure quicksort and validate its output.
    {
        sorter s(dataset);
        std::vector<int> qsResult = s.quicksort();
        result.quicksortMicros  = s.getMicros().count();
        result.quicksortCorrect = DataLoader::isSorted(qsResult);
    }

    return result;
}

void Comparator::printResult(const ComparisonResult& result) {
    // Print the timing and correctness details for one dataset comparison.
    std::cout << "\n";
    std::cout << "======================================================\n";
    std::cout << "  Dataset : " << result.datasetLabel << "\n";
    std::cout << "  Size    : " << result.datasetSize << " elements\n";
    std::cout << "------------------------------------------------------\n";

    std::cout << "  Quicksort  | Time: " << std::setw(10) << result.quicksortMicros
              << " us | Correct: " << (result.quicksortCorrect ? "YES" : "NO ") << "\n";

    std::cout << "  Mergesort  | Time: " << std::setw(10) << result.mergesortMicros
              << " us | Correct: " << (result.mergesortCorrect ? "YES" : "NO ") << "\n";

    std::cout << "------------------------------------------------------\n";

    // Pick the winner by correctness first, then by runtime when both are valid.
    if (result.quicksortCorrect && result.mergesortCorrect) {
        if (result.quicksortMicros < result.mergesortMicros) {
            double ratio = static_cast<double>(result.mergesortMicros) / result.quicksortMicros;
            std::cout << "  Winner: Quicksort  (" << std::fixed << std::setprecision(2)
                      << ratio << "x faster)\n";
        } else if (result.mergesortMicros < result.quicksortMicros) {
            double ratio = static_cast<double>(result.quicksortMicros) / result.mergesortMicros;
            std::cout << "  Winner: Mergesort  (" << std::fixed << std::setprecision(2)
                      << ratio << "x faster)\n";
        } else {
            std::cout << "  Winner: Tie\n";
        }
    } else if (!result.quicksortCorrect && result.mergesortCorrect) {
        std::cout << "  Note: Quicksort produced an incorrect result.\n";
        std::cout << "  Winner: Mergesort (correctness)\n";
    } else if (result.quicksortCorrect && !result.mergesortCorrect) {
        std::cout << "  Note: Mergesort produced an incorrect result.\n";
        std::cout << "  Winner: Quicksort (correctness)\n";
    } else {
        std::cout << "  Both algorithms produced incorrect results.\n";
    }

    std::cout << "======================================================\n";
}

void Comparator::printTable(const std::vector<ComparisonResult>& results) {
    if (results.empty()) return;

    // Print a full table so every dataset can be compared side by side.
    std::cout << "\n";
    std::cout << "                         FULL COMPARISON TABLE\n";
    std::cout << std::left
              << std::setw(32) << "Dataset"
              << std::setw(14) << "Size"
              << std::setw(18) << "Quicksort (us)"
              << std::setw(18) << "Mergesort (us)"
              << "Winner\n";

    // Build a winner label for each row before writing the output.
    for (const auto& r : results) {
        std::string winner = "Tie";
        if (r.quicksortCorrect && r.mergesortCorrect) {
            if (r.quicksortMicros < r.mergesortMicros) winner = "Quicksort";
            else if (r.mergesortMicros < r.quicksortMicros) winner = "Mergesort";
        } else if (!r.quicksortCorrect && r.mergesortCorrect) {
            winner = "Mergesort*";
        } else if (r.quicksortCorrect && !r.mergesortCorrect) {
            winner = "Quicksort*";
        } else {
            winner = "N/A";
        }

        std::string label = r.datasetLabel;
        if (label.size() > 30) label = label.substr(0, 27) + "...";

        std::cout << std::left
                  << std::setw(32) << label
                  << std::setw(14) << r.datasetSize
                  << std::setw(18) << r.quicksortMicros
                  << std::setw(18) << r.mergesortMicros
                  << winner << "\n";
    }

    std::cout << "  * Correctness issue detected for that algorithm.\n";
}
