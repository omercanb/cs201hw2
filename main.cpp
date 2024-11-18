#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>

#include "search.h"

struct KeysForSearch {
    int near_start;
    int near_middle;
    int near_end;
    int not_in_collection;
};

std::vector<int> createRandomSortedArray(int size);
void printVector(const std::vector<int>& vec);
KeysForSearch chooseKeysForSearch(const std::vector<int> &vec);
void testSearch(std::vector<int>& vec, KeysForSearch keys);


int main() {
    // std::vector<int> vec = createRandomSortedArray(10);
    // testSearch(vec, chooseKeysForSearch(vec));
    const auto search = binarySearch;
    const std::string name = "binary";
    constexpr int num_of_runs = 10000; // Change according to how slow the search is

    std::random_device rd;
    std::mt19937 rng(rd()); // Used as an argument to random search

    std::ofstream outputFile("data.csv", std::ios::app);
    bool multiplyByFive = false;
    // This loop is not expected to finish, terminate it manually
    for (int size = 1; size <= 10'000'000'000; size = (multiplyByFive ? size * 5 : size * 2)) {
        multiplyByFive = !multiplyByFive;

        std::cout << size << std::endl;

        constexpr int types_of_keys = 4;

        std::array<long, types_of_keys> runtimes {};
        std::vector<int> vec = createRandomSortedArray(size);

        for (int i = 0; i < num_of_runs * types_of_keys; i++) {
            const KeysForSearch keys = chooseKeysForSearch(vec);
            std::array<int, types_of_keys> keys_array = {keys.near_start, keys.near_middle, keys.near_end, keys.not_in_collection};
            int key = keys_array[i % types_of_keys];
            auto start = std::chrono::high_resolution_clock::now();
            search(vec, key);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = end - start;
            runtimes[i % types_of_keys] += static_cast<long>(duration.count());
        }
        for (long& t : runtimes) {
            t /= num_of_runs;
        }

        outputFile << name << ",";
        outputFile << size << ",";
        for (int i = 0; i < runtimes.size(); i++) {
            outputFile << runtimes[i];
            if (i != runtimes.size() - 1) {
                outputFile << ",";
            }
        }
        outputFile << std::endl;

    }
    outputFile.close();
    return 0;
}

void testSearch(std::vector<int>& vec, KeysForSearch keys) {
    for (int n : {keys.near_start, keys.near_middle, keys.near_end, keys.not_in_collection}) {
        std::cout << jumpSearch(vec, n) << std::endl;
    }
}

KeysForSearch chooseKeysForSearch(const std::vector<int> &vec) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, static_cast<int>(vec.size())/10);
    KeysForSearch keys{};
    keys.near_start = vec[dist(gen)];
    keys.near_middle = vec[dist(gen) + static_cast<int>(vec.size()/2 - vec.size()/20)];
    keys.near_end = vec[vec.size() - dist(gen) - 1];
    if (vec.size() == 1) {
        keys.not_in_collection = -1;
    } else {
        std::uniform_int_distribution<> rangeOfVec(0, vec.back());
        bool found = false;
        do {
            int random = rangeOfVec(gen);
            if (binarySearch(vec, random) == -1) {
                keys.not_in_collection = random;
                found = true;
            }
        } while (!found);
    }
    return keys;
}

std::vector<int> createRandomSortedArray(int size) {
    // Create an array of size n with values in range [0, size*10]
    std::mt19937 gen(1337);
    std::uniform_int_distribution<> dist(0, 10);
    std::vector<int> arr(size);
    arr[0] = dist(gen);
    for (int i = 1; i < size; i++)
        arr[i] = arr[i-1] + dist(gen);
    return arr;
}

void printVector(const std::vector<int>& vec) {
    for (const int n : vec)
        std::cout << n << " ";
    std::cout << std::endl;
}
