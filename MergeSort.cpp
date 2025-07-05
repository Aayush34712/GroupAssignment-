#include <iostream>
#include <vector>

using namespace std;

// Function to combine two sorted parts of the array
void combine(vector<int>& nums, int left, int mid, int right) {
    int size1 = mid - left + 1;
    int size2 = right - mid;

    // Create temporary arrays
    vector<int> first(size1), second(size2);

    // Copy data into temp arrays
    for (int i = 0; i < size1; i++)
        first[i] = nums[left + i];
    for (int j = 0; j < size2; j++)
        second[j] = nums[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge both arrays back into nums
    while (i < size1 && j < size2) {
        if (first[i] <= second[j]) {
            nums[k] = first[i];
            i++;
        } else {
            nums[k] = second[j];
            j++;
        }
        k++;
    }

    // Add leftover elements from first array
    while (i < size1) {
        nums[k] = first[i];
        i++;
        k++;
    }

    // Add leftover elements from second array
    while (j < size2) {
        nums[k] = second[j];
        j++;
        k++;
    }
}

// Merge sort function
void mergeSort(vector<int>& nums, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort left part
        mergeSort(nums, left, mid);
        // Sort right part
        mergeSort(nums, mid + 1, right);
        // Merge both parts
        combine(nums, left, mid, right);
    }
}

// Function to print elements of the array
void printList(const vector<int>& nums) {
    for (int val : nums) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    vector<int> data = {12, 11, 13, 5, 6, 7};
    int n = data.size();

    cout << "Before sorting: ";
    printList(data);

    mergeSort(data, 0, n - 1);

    cout << "After sorting (Merge Sort): ";
    printList(data);

    return 0;
}
