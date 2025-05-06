#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void generateArray(vector<int>& arr, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000;
    }
}
// =====================================
void printArray(vector<int>& arr) {
    for (auto i : arr) {
        cout << i << " ";
    }
    cout << "\n";
}
// =====================================
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
// =====================================
void sequentialQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low ,high);
        sequentialQuickSort(arr, low, pi - 1);
        sequentialQuickSort(arr, pi + 1, high);
    }
}
// =====================================
void parallelQuickSort(vector<int>& arr, int low, int high, int depth = 0) {
    if (low < high) {
        int pi = partition(arr, low, high);

        if (depth <= 3) {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallelQuickSort(arr, low, pi - 1, depth + 1);

                #pragma omp section
                parallelQuickSort(arr, pi + 1, high, depth + 1);
            }
        }
        else {
            // switch to sequential to avoid excessive thread overhead
            sequentialQuickSort(arr, low, pi - 1);
            sequentialQuickSort(arr, pi + 1, high);
        }
    }
}
// =====================================
void copyArray(const vector<int>& source, vector<int>& dest) {
    for (int i = 0; i < source.size(); i++) {
        dest[i] = source[i];
    }
}
// =====================================
int main() {
    int size;
    cout << "Enter size of array: ";
    cin >> size;

    vector<int> originalArr(size), seqArr(size), parArr(size);

    generateArray(originalArr, size);
    copyArray(originalArr, seqArr);
    copyArray(originalArr, parArr);

    cout << "Original Array:\n";
    // printArray(originalArr);

    auto startTime = high_resolution_clock::now();
    sequentialQuickSort(seqArr, 0, size - 1);
    auto endTime = high_resolution_clock::now();

    auto seqTime = duration_cast<seconds>(endTime - startTime);
    cout << "Sequential Quick Sort Time: " << seqTime.count() << " ms\n";

     startTime = high_resolution_clock::now();
    parallelQuickSort(seqArr, 0, size - 1); // depth is a default argument, so no need to pass here
     endTime = high_resolution_clock::now();

    auto parTime = duration_cast<seconds>(endTime - startTime);
    cout << "Parallel Quick Sort Time: " << parTime.count() << " ms\n";

    return 0;
}