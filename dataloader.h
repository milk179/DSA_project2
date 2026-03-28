// dataloader.h | Jonathan Tang | 3/26/26

#pragma once
#include <vector>
#include <string>

enum class DatasetType {
    RANDOM,
    NEARLY_SORTED,
    REVERSE_SORTED,
    FROM_CSV
};

class DataLoader {
public:

    // Generate a random dataset.
    static std::vector<int> generateRandom(int size, int maxVal = 1000000);

    // Generate a nearly-sorted dataset.
    static std::vector<int> generateNearlySorted(int size, double swapFraction = 0.05);

    // Generate a reverse-sorted dataset.
    static std::vector<int> generateReverseSorted(int size);

    // Load integers from a CSV file.
    static std::vector<int> loadFromCSV(const std::string& filepath, int maxRows = 200000);

    // Print a summary of the first few and last few elements.
    static void printSummary(const std::vector<int>& data, int previewCount = 5);

    // Verify that a vector is sorted in non-descending order.
    static bool isSorted(const std::vector<int>& data);
};
