// main.cpp
// Authors: Samuel Arango 
//          Andre Morgan  
//			Jonathan Tang
// Date: 3/27/2026


#include "comparator.h"
#include "dataloader.h"
#include "sorter.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>
// Reset the input stream after invalid reads.
static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Keep prompting until the user enters an integer inside the range.
static int readInt(const std::string& prompt, int minVal, int maxVal) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val && val >= minVal && val <= maxVal) {
            clearInput();
            return val;
        }
        clearInput();
        std::cout << "  Invalid input. Please enter a number between "
                  << minVal << " and " << maxVal << ".\n";
    }
}

// Print the main menu.
static void printMainMenu() {
    std::cout << "\n";
    std::cout << "      DSA Project 2: Sort Comparator         \n";
    std::cout << "      Team ASJ:  Merge vs. Quick Sort       \n";
    std::cout << "  [1] Load Data                               \n";
    std::cout << "  [2] Sort Data & Compare                     \n";
    std::cout << "  [3] Run All Conditions (Full Benchmark)     \n";
    std::cout << "  [4] Quit                                    \n";
    std::cout << "  Choice: ";
}

// Collect the user's dataset choice, and print a short preview.
static std::vector<int> loadDataMenu() {
    std::cout << "\n Load Data \n";
    std::cout << "  [1] Random data\n";
    std::cout << "  [2] Nearly sorted data\n";
    std::cout << "  [3] Reverse sorted data\n";
    std::cout << "  [4] Load from CSV file\n";
    int choice = readInt("  Choice: ", 1, 4);

    std::vector<int> dataset;

    if (choice == 1) {
        int size = readInt("  Enter dataset size (100 - 1000000): ", 100, 1000000);
        std::cout << "  Generating random dataset...\n";
        dataset = DataLoader::generateRandom(size);
        std::cout << "  Done.\n";
        DataLoader::printSummary(dataset);

    } else if (choice == 2) {
        int size = readInt("  Enter dataset size (100 - 1000000): ", 100, 1000000);
        std::cout << "  Generating nearly-sorted dataset (5% swapped)...\n";
        dataset = DataLoader::generateNearlySorted(size, 0.05);
        std::cout << "  Done.\n";
        DataLoader::printSummary(dataset);

    } else if (choice == 3) {
        int size = readInt("  Enter dataset size (100 - 1000000): ", 100, 1000000);
        std::cout << "  Generating reverse-sorted dataset...\n";
        dataset = DataLoader::generateReverseSorted(size);
        std::cout << "  Done.\n";
        DataLoader::printSummary(dataset);

    } else {
        clearInput();
        std::cout << "  Enter CSV file path: ";
        std::string filepath;
        std::getline(std::cin, filepath);

        int maxRows = readInt("  Max rows to load (100 - 1000000): ", 100, 1000000);
        dataset = DataLoader::loadFromCSV(filepath, maxRows);

        if (dataset.empty()) {
            std::cout << "  No data loaded. Returning to menu.\n";
        } else {
            DataLoader::printSummary(dataset);
        }
    }

    return dataset;
}

// Run both sorts on the current dataset and print the summary.
static ComparisonResult sortAndCompare(const std::vector<int>& dataset, const std::string& label) {
    if (dataset.empty()) {
        std::cout << "  No dataset loaded. Please load data first.\n";
        return {};
    }

    std::cout << "\n  Running Quicksort and Mergesort on " << dataset.size() << " elements...\n";
    ComparisonResult result = Comparator::run(dataset, label);
    Comparator::printResult(result);
    return result;
}

// Run the benchmark across random, nearly sorted, and reverse-sorted inputs.
static void fullBenchmark() {
    const int BENCHMARK_SIZE = 100000;

    std::cout << "\n  Running full benchmark (" << BENCHMARK_SIZE << " elements each)...\n";
    std::cout << "  This tests: Random, Nearly Sorted, and Reverse Sorted.\n\n";

    std::vector<ComparisonResult> allResults;

    std::cout << "  [1/3] Generating random dataset...\n";
    auto r1 = DataLoader::generateRandom(BENCHMARK_SIZE);
    allResults.push_back(Comparator::run(r1, "Random (" + std::to_string(BENCHMARK_SIZE) + ")"));

    std::cout << "  [2/3] Generating nearly-sorted dataset...\n";
    auto r2 = DataLoader::generateNearlySorted(BENCHMARK_SIZE);
    allResults.push_back(Comparator::run(r2, "Nearly Sorted (" + std::to_string(BENCHMARK_SIZE) + ")"));

    std::cout << "  [3/3] Generating reverse-sorted dataset...\n";
    auto r3 = DataLoader::generateReverseSorted(BENCHMARK_SIZE);
    allResults.push_back(Comparator::run(r3, "Reverse Sorted (" + std::to_string(BENCHMARK_SIZE) + ")"));

    for (const auto& res : allResults) {
        Comparator::printResult(res);
    }
    Comparator::printTable(allResults);
}

// Drive the menu loop and dispatch the user's menu choices.
int main() {
    std::vector<int> currentDataset;
    std::string      currentLabel = "Dataset";
    std::vector<ComparisonResult> sessionResults;

    bool running = true;
    while (running) {
        printMainMenu();

        int choice;
        if (!(std::cin >> choice)) {
            clearInput();
            continue;
        }
        clearInput();

        if (choice == 1) {
            currentDataset = loadDataMenu();
            currentLabel = "Loaded Dataset (" + std::to_string(currentDataset.size()) + " elements)";
        } else if (choice == 2) {
            if (currentDataset.empty()) {
                std::cout << "\n  No dataset loaded. Please choose option 1 first.\n";
            } else {
                ComparisonResult res = sortAndCompare(currentDataset, currentLabel);
                if (res.datasetSize > 0) {
                    sessionResults.push_back(res);
                }
            }
        } else if (choice == 3) {
            fullBenchmark();
        } else if (choice == 4) {
            std::cout << "\n  Goodbye!\n";
            running = false;
        } else {
            std::cout << "\n  Invalid choice. Please enter 1-4.\n";
        }
    }

    return 0;
}
