#include <iostream>
#include <vector>
#include <algorithm> // for sort and min

using namespace std;

// This function uses binary search between given range
int binarySearch(const vector<int>& data, int start, int end, int key) {
    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (data[mid] == key)
            return mid;
        else if (data[mid] < key)
            start = mid + 1;
        else
            end = mid - 1;
    }
    return -1; // not found
}

// Exponential search to find position quickly
int exponentialSearch(const vector<int>& data, int key) {
    int size = data.size();

    // Check if key is at the first index
    if (data[0] == key)
        return 0;

    // Find range where the key might be
    int i = 1;
    while (i < size && data[i] <= key) {
        i *= 2;
    }

    // Use binary search in that range
    return binarySearch(data, i / 2, min(i, size - 1), key);
}

int main() {
    vector<int> numbers = {2, 3, 4, 10, 40, 50, 60, 70, 80, 100, 120};
    int value;

    // Ensure array is sorted before search
    sort(numbers.begin(), numbers.end());

    cout << "Sorted array: ";
    for (int x : numbers) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Enter number to search: ";
    cin >> value;

    int position = exponentialSearch(numbers, value);

    if (position == -1)
        cout << "Number not found in the list." << endl;
    else
        cout << "Number found at index " << position << "." << endl;

    return 0;
}
