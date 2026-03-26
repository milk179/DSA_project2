//
// Created by andre on 3/24/2026.
//

#include "sorter.h"

sorter::sorter(std::vector<int> dataset_) : dataset(dataset_) {}

std::vector<int> sorter::quicksort() {
    quicksortReal(dataset, 0, dataset.size() - 1);
    return dataset;
}

std::vector<int> sorter::mergesort() { return mergesortReal(dataset, 0, dataset.size() - 1); }

void sorter::quicksortReal(std::vector<int>& dataset, int left, int right) {

    if (left >= right) return;

    int pivot = left + (right - left) / 2;
    std::swap(dataset[pivot], dataset[right]);
    pivot = right;

    int i = left, j = right - 1;

    while (i <= j) {

        if (dataset[j] <= dataset[pivot]) {

            if (dataset[i] > dataset[pivot]) std::swap(dataset[j], dataset[i]);
            i++;
            j--;
        }
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