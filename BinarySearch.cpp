#include <iostream>
#include <vector>
#include <algorithm> // to sort  array

using namespace std;

// This function searches for a number using binary search
int searchElement(const vector<int>& data, int key) {
    int start = 0;
    int end = data.size() - 1;

    while (start <= end) {
        int middle = start + (end - start) / 2;

        if (data[middle] == key) {
            return middle; // found the number
        } else if (data[middle] < key) {
            start = middle + 1; // go to the right side
        } else {
            end = middle - 1; // go to the left side
        }
    }

    return -1; // number not found
}

int main() {
    vector<int> numbers = {10, 4, 2, 40, 3, 60, 70, 50};
    int element;

    // sort the array first
    sort(numbers.begin(), numbers.end());

    cout << "Sorted array: ";
    for (int val : numbers) {
        cout << val << " ";
    }
    cout << endl;

    // ask the user for a number
    cout << "Enter number to search: ";
    cin >> element;

    // call the function to search the number
    int index = searchElement(numbers, element);

    // show the result
    if (index == -1) {
        cout << "Number not found." << endl;
    } else {
        cout << "Number found at index " << index << "." << endl;
    }

    return 0;
}
