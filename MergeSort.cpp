#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;
using namespace std::chrono;

// Utility functions
void generateRandomNumbers(vector<int>& data, int N, int min_val = 1, int max_val = 100000) {
    data.resize(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min_val, max_val);

    for (int i = 0; i < N; ++i) {
        data[i] = dist(gen);
    }
}

// Binary Search
int binarySearch(const vector<int>& data, int key) {
    int left = 0, right = data.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data[mid] == key) return mid;
        else if (data[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Exponential Search
int exponentialSearch(const vector<int>& data, int key) {
    if (data.empty()) return -1;
    if (data[0] == key) return 0;

    int i = 1;
    while (i < data.size() && data[i] <= key) i *= 2;

    int left = i / 2;
    int right = min(i, static_cast<int>(data.size()) - 1);
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data[mid] == key) return mid;
        else if (data[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Main function with verification
int main() {
    int N;
    cout << "Enter the number of random integers (N): ";
    cin >> N;

    // Generate and display range information
    const int min_val = 1, max_val = 100000;
    vector<int> data;
    generateRandomNumbers(data, N, min_val, max_val);
    cout << "Generated " << N << " random numbers between " << min_val << " and " << max_val << "\n";

    // Display actual range of generated numbers (C++11 compatible)
    auto minmax = minmax_element(data.begin(), data.end());
    int min_actual = *minmax.first;
    int max_actual = *minmax.second;
    cout << "Actual range in data: " << min_actual << " to " << max_actual << "\n";

    // Create a verified sorted copy
    vector<int> sortedData = data;
    sort(sortedData.begin(), sortedData.end());
    assert(is_sorted(sortedData.begin(), sortedData.end()));

    // Ask for search key with range suggestions
    int key;
    cout << "\nEnter a number to search (" << min_actual << "-" << max_actual << "): ";
    cin >> key;

    // Verify if key exists in unsorted data (for debugging)
    bool key_exists = find(data.begin(), data.end(), key) != data.end();
    cout << "Debug: Key " << key << (key_exists ? " EXISTS" : " DOES NOT EXIST") << " in original data\n";

    // Test searching algorithms
    cout << "\n=== Searching Algorithms ===\n";
    
    // Binary Search with verification
    auto start = high_resolution_clock::now();
    int index = binarySearch(sortedData, key);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    
    cout << "Binary Search: ";
    if (index != -1) {
        cout << "Found at index " << index << " (value: " << sortedData[index] << ")";
        assert(sortedData[index] == key);
    } else {
        cout << "Not found";
        assert(!key_exists);
    }
    cout << " | Time: " << duration.count() << " ns\n";

    // Exponential Search with verification
    start = high_resolution_clock::now();
    index = exponentialSearch(sortedData, key);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    
    cout << "Exponential Search: ";
    if (index != -1) {
        cout << "Found at index " << index << " (value: " << sortedData[index] << ")";
        assert(sortedData[index] == key);
    } else {
        cout << "Not found";
        assert(!key_exists);
    }
    cout << " | Time: " << duration.count() << " ns\n";

    // [Keep your existing sorting algorithms output here...]

    return 0;
}