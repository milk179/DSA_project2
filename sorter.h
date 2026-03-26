//
// Created by andre on 3/24/2026.
//

#include <vector>
#pragma once

class sorter {

public:

	sorter(std::vector<int> dataset_);

	std::vector<int> quicksort();

	std::vector<int> mergesort();

	void quicksortReal(std::vector<int>& dataset, int left, int right);

	std::vector<int> mergesortReal(const std::vector<int>& dataset, int left, int right);

	std::vector<int> merge(std::vector<int> leftset, std::vector<int> rightset);

private:

	std::vector<int> dataset;

};