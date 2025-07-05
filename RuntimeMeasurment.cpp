#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

int main() {
    int N = 1000; // Change this value for different input sizes
    vector<int> arr(N);

    srand(time(0));
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % 10000;
    }

    auto start = high_resolution_clock::now();

    bubbleSort(arr);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Runtime for N = " << N << ": " << duration.count() << " ms" << endl;
}
