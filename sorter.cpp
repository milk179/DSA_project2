//
// Created by andre on 3/24/2026.
//

#include "sorter.h"

sorter::sorter(std::vector<int> dataset_) : dataset(dataset_) {}

std::vector<int> sorter::quicksort() {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> datasetCopy = dataset;

    quicksortReal(datasetCopy, 0, static_cast<int>(datasetCopy.size()) - 1);

    auto end = std::chrono::high_resolution_clock::now();

    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    return datasetCopy;
}

std::vector<int> sorter::mergesort() {

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> result;
    if (!dataset.empty()) {
        result = mergesortReal(dataset, 0, static_cast<int>(dataset.size()) - 1);
    }

    auto end = std::chrono::high_resolution_clock::now();

    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    return result;
}

std::chrono::microseconds sorter::getMicros() { return microseconds; }

void sorter::quicksortReal(std::vector<int>& dataset, int left, int right) {

    if (left >= right) return;

    int pivot = left + (right - left) / 2;
    std::swap(dataset[pivot], dataset[right]);
    pivot = right;

    int i = left, j = right - 1;

    while (i <= j) {
        while (j >= left && !(dataset[j] <= dataset[pivot])) j--;
        while (i <= right && !(dataset[i] > dataset[pivot])) i++;

        if (i > j) break;

        std::swap(dataset[i], dataset[j]);
        i++;
        j--;
    }

    quicksortReal(dataset, left, j);
    quicksortReal(dataset, i, right);
}

std::vector<int> sorter::mergesortReal(const std::vector<int>& dataset, int left, int right) {

    if (left == right) return { dataset[left] };

    int middle = left + (right - left) / 2;

    std::vector<int> leftset = mergesortReal(dataset, left, middle);
    std::vector<int> rightset = mergesortReal(dataset, middle + 1, right);

    return merge(leftset, rightset);
}

std::vector<int> sorter::merge(std::vector<int> leftset, std::vector<int> rightset) {

    if (leftset.empty()) return rightset;
    else if (rightset.empty()) return leftset;

    std::vector<int> result;
    result.reserve(leftset.size() + rightset.size());

    int i = 0, j = 0;

    while (i < leftset.size() && j < rightset.size()) {

        if (leftset[i] > rightset[j]) {
            result.push_back(rightset[j]);
            j++;
        }
        else {
            result.push_back(leftset[i]);
            i++;
        }
    }

    while (i < leftset.size()) result.push_back(leftset[i++]);
    while (j < rightset.size()) result.push_back(rightset[j++]);

    return result;
}
