//
// Created by Ömer Can Baykara on 14.11.2024.
//
#pragma once

#include <vector>

#ifndef SEARCH_H
#define SEARCH_H

int linearSearch(const std::vector<int>& vec, int value);
int linearSearchRecursive(const std::vector<int>& vec, int value, int i = 0);
int binarySearch(const std::vector<int>& vec, int value);
int jumpSearch(const std::vector<int>& vec, int value);
int randomSearch(const std::vector<int>& vec, int value, std::mt19937& rng);

#endif //SEARCH_H
