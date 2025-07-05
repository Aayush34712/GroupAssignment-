#include <iostream>
#include <vector>
#include <algorithm> // for using swap

using namespace std;

// This function arranges elements around a pivot
int divide(vector<int>& nums, int start, int end) {
    int pivot = nums[end];  // picking the last value as pivot
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (nums[j] < pivot) {
            i++;
            swap(nums[i], nums[j]); // putting smaller elements on the left
        }
    }

    swap(nums[i + 1], nums[end]); // putting pivot in correct place
    return i + 1; // return pivot index
}

// Quick Sort function
void quickSort(vector<int>& nums, int start, int end) {
    if (start < end) {
        int partIndex = divide(nums, start, end); // get partition position

        quickSort(nums, start, partIndex - 1); // sort left side
        quickSort(nums, partIndex + 1, end);   // sort right side
    }
}

// This prints all elements of the array
void printList(const vector<int>& nums) {
    for (int val : nums) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    vector<int> data = {10, 7, 8, 9, 1, 5};
    int size = data.size();

    cout << "Before sorting: ";
    printList(data);

    quickSort(data, 0, size - 1);

    cout << "After sorting (Quick Sort): ";
    printList(data);

    return 0;
}
