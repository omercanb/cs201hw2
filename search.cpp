//
// Created by Ömer Can Baykara on 14.11.2024.
//
#include <random>
#include "search.h"

#include <iostream>
#include <ostream>

int linearSearch(const std::vector<int>& vec, int value) {
    for (int i = 0; i < vec.size(); i++)
      if (vec[i] == value)
        return i;
    return -1;
}

int linearSearchRecursive(const std::vector<int>& vec, int value, int i) {
    if (i == vec.size()) {
        return -1;
    }
    if (vec[i] == value) {
        return i;
    }
    return linearSearchRecursive(vec, value, i + 1);
}
int binarySearch(const std::vector<int>& vec, int value) {
    int l = 0, r = vec.size() - 1;
    while (l <= r) {
        const int m = l + (r - l) / 2;
        const int curr = vec[m];

        if (value == curr) {
            return m;
        }
        if (value < curr) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return -1;
}
int jumpSearch(const std::vector<int>& vec, int value) {
    // int block_size = static_cast<int>(std::sqrt(vec.size()));
    int block_size = vec.size();
    int i = 0;
    for (; i < vec.size(); i += block_size) {
        if (vec[i] == value) {
            return i;
        }
        if (vec[i] > value) {
            break;
        }
    }
    i-= block_size;
    for (int j = i; j < vec.size() && j < i + block_size; j += 1) {
        if (vec[j] == value) {
            return j;
        }
    }
    return -1;
}


int randomSearch(const std::vector<int>& vec, int value, std::mt19937& rng) {
    std::vector<int> indices(vec.size());
    for (int i = 0; i < indices.size(); i++) {
        indices[i] = i;
    }
    std::ranges::shuffle(indices, rng);
    for (const int idx : indices) {
        if (vec[idx] == value) {
            return idx;
        }
    }
    return -1;
};