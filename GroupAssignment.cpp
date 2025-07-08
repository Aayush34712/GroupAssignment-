#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

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
    
    // Binary search between left and right
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data[mid] == key) return mid;
        else if (data[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Merge Sort
void merge(vector<int>& data, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (data[i] <= data[j]) temp[k++] = data[i++];
        else temp[k++] = data[j++];
    }

    while (i <= mid) temp[k++] = data[i++];
    while (j <= right) temp[k++] = data[j++];

    for (int p = 0; p < k; ++p) {
        data[left + p] = temp[p];
    }
}

void mergeSort(vector<int>& data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);
        merge(data, left, mid, right);
    }
}

// Quick Sort
int partition(vector<int>& data, int low, int high) {
    int pivot = data[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (data[j] < pivot) {
            swap(data[++i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return i + 1;
}

void quickSort(vector<int>& data, int low, int high) {
    if (low < high) {
        int pi = partition(data, low, high);
        quickSort(data, low, pi - 1);
        quickSort(data, pi + 1, high);
    }
}

// Main function
int main() {
    int N;
    cout << "Enter the number of random integers (N): ";
    cin >> N;

    // Generate N random integers (1-100000 by default)
    vector<int> data;
    generateRandomNumbers(data, N);
    cout << "Generated " << N << " random numbers between 1 and 100000\n";

    // Sort the array for searching algorithms
    vector<int> sortedData = data;
    sort(sortedData.begin(), sortedData.end());

    // Ask user for a number to search
    int key;
    cout << "\nEnter a number to search (1-100000): ";
    cin >> key;

    // Validate search range
    if (key < 1 || key > 100000) {
        cout << "Warning: Search value is outside the random number range (1-100000).\n";
        cout << "This will likely result in 'Not found'.\n";
    }

    // Test searching algorithms
    cout << "\n=== Searching Algorithms ===\n";
    
    // Binary Search with multiple iterations for better timing
    const int search_iterations = 10000;
    auto start = high_resolution_clock::now();
    int index = -1;
    for (int i = 0; i < search_iterations; ++i) {
        index = binarySearch(sortedData, key);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start) / search_iterations;
    
    cout << "Binary Search: ";
    if (index != -1) {
        cout << "Found at index " << index;
    } else {
        cout << "Not found";
    }
    cout << " | Time: " << duration.count() << " nanoseconds\n";

    // Exponential Search with multiple iterations
    start = high_resolution_clock::now();
    for (int i = 0; i < search_iterations; ++i) {
        index = exponentialSearch(sortedData, key);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start) / search_iterations;
    
    cout << "Exponential Search: ";
    if (index != -1) {
        cout << "Found at index " << index;
    } else {
        cout << "Not found";
    }
    cout << " | Time: " << duration.count() << " nanoseconds\n";

    // Test sorting algorithms
    cout << "\n=== Sorting Algorithms ===\n";
    
    // Merge Sort
    vector<int> mergeData = data;
    start = high_resolution_clock::now();
    mergeSort(mergeData, 0, mergeData.size() - 1);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Merge Sort completed | Time: " << duration.count() << " milliseconds\n";

    // Quick Sort
    vector<int> quickData = data;
    start = high_resolution_clock::now();
    quickSort(quickData, 0, quickData.size() - 1);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Quick Sort completed | Time: " << duration.count() << " milliseconds\n";

    return 0;
}