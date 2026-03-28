// dataloader.cpp | Jonathan Tang | 3/26/26

#include "dataloader.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
std::vector<int> DataLoader::generateRandom(int size, int maxVal) {
    // Fill a vector with random values.
    std::vector<int> data;
    data.reserve(size);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, maxVal);

    for (int i = 0; i < size; ++i) {
        data.push_back(dist(rng));
    }
    return data;
}

std::vector<int> DataLoader::generateNearlySorted(int size, double swapFraction) {
    // Build a sorted dataset first, then scramble.
    std::vector<int> data;
    data.reserve(size);

    for (int i = 0; i < size; ++i) {
        data.push_back(i);
    }

    std::mt19937 rng(std::random_device{}());
    int swapCount = static_cast<int>(size * swapFraction);
    std::uniform_int_distribution<int> dist(0, size - 1);

    for (int i = 0; i < swapCount; ++i) {
        int a = dist(rng);
        int b = dist(rng);
        std::swap(data[a], data[b]);
    }

    return data;
}

std::vector<int> DataLoader::generateReverseSorted(int size) {
    // Generate data in descending order.
    std::vector<int> data;
    data.reserve(size);
    for (int i = size; i > 0; --i) {
        data.push_back(i);
    }
    return data;
}

std::vector<int> DataLoader::loadFromCSV(const std::string& filepath, int maxRows) {
    // Read comma-separated values from the file, keep numeric tokens, and stop once the row limit is reached.
    std::vector<int> data;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "[DataLoader] Error: Could not open file: " << filepath << "\n";
        return data;
    }

    std::string line;
    int rowCount = 0;

    while (std::getline(file, line) && rowCount < maxRows) {
        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ',')) {
            // Trim each token before attempting integer conversion.
            size_t start = token.find_first_not_of(" \t\r\n");
            size_t end   = token.find_last_not_of(" \t\r\n");
            if (start == std::string::npos) continue;
            token = token.substr(start, end - start + 1);

            try {
                int val = std::stoi(token);
                data.push_back(val);
                ++rowCount;
                if (rowCount >= maxRows) break;
            } catch (...) {
            }
        }
    }

    file.close();

    if (data.empty()) {
        std::cerr << "[DataLoader] Warning: No numeric data found in " << filepath << "\n";
    } else {
        std::cout << "[DataLoader] Loaded " << data.size() << " values from " << filepath << "\n";
    }

    return data;
}

void DataLoader::printSummary(const std::vector<int>& data, int previewCount) {
    // Show the dataset size.
    if (data.empty()) {
        std::cout << "  [Empty dataset]\n";
        return;
    }

    std::cout << "  Size: " << data.size() << " elements\n";
    std::cout << "  First " << previewCount << ": ";
    for (int i = 0; i < previewCount && i < (int)data.size(); ++i) {
        std::cout << data[i];
        if (i < previewCount - 1 && i < (int)data.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";

    std::cout << "  Last  " << previewCount << ": ";
    int startIdx = std::max(0, (int)data.size() - previewCount);
    for (int i = startIdx; i < (int)data.size(); ++i) {
        std::cout << data[i];
        if (i < (int)data.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}

bool DataLoader::isSorted(const std::vector<int>& data) {
    // Verify that the values never decrease.
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i] < data[i - 1]) return false;
    }
    return true;
}
