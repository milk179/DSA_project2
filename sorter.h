//
// Created by andre on 3/24/2026.
//
#include <chrono>
#include <vector>
#pragma once

class sorter {

public:

	sorter(std::vector<int> dataset_); // Construct the object with the desired set of data

	std::vector<int> quicksort();

	std::vector<int> mergesort();

	std::chrono::microseconds getMicros(); // Gives you how long the last sorting operation took in microseconds

private:

	void quicksortReal(std::vector<int>& dataset, int left, int right);

	std::vector<int> mergesortReal(const std::vector<int>& dataset, int left, int right);

	std::vector<int> merge(std::vector<int> leftset, std::vector<int> rightset);

	std::vector<int> dataset;

	std::chrono::microseconds microseconds;

};