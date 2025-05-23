#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to generate random array
void generateArray(vector<int>& arr, int size) {
	srand(time(0));
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 10000;    // generates 0 to 99,999
	}
}
// ======================================
// Function to print array
void printArray(vector<int>& arr) {
	for (auto i : arr) {
		cout << i << " ";
	}
	cout << "\n";
}
// ======================================
void merge(vector<int>& arr, int left, int mid, int right) {
	vector<int> temp(right - left + 1);
	int i = left, j = mid + 1, k = 0;

	// merge the subarrays 
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			temp[k++] = arr[i++];
		}
		else {
			temp[k++] = arr[j++];
		}
	}
	while (i <= mid) {
		temp[k++] = arr[i++];
	}
	while (j <= right) {
		temp[k++] = arr[j++];
	}
	
	// copy from the temp array to the original array
	for (int l = 0; l < temp.size(); l++) {
		arr[left + l] = temp[l];
	}
}
// ======================================
void mergeSortSequential(vector<int>& arr, int left, int right) {
	if (left >= right) return;
	int mid = (left + right) / 2;

	mergeSortSequential(arr, left, mid);
	mergeSortSequential(arr, mid + 1, right);

	merge(arr, left, mid, right);
}
// ======================================
void mergeSortParallel(vector<int>& arr, int left, int right, int depth = 0) {
	if (left >= right) return;

	int mid = (left + right) / 2;

	if (depth <= 3) {
		// parallelize up to a certain depth to avoid excessive thread creation
		#pragma omp parallel sections
		{
			#pragma omp section
			mergeSortParallel(arr, left, mid, depth + 1);

			#pragma omp section
			mergeSortParallel(arr, mid + 1, right, depth + 1);
		}
	}
	else {
		// Fallback to sequential to prevent overhead
		mergeSortSequential(arr, left, mid);
		mergeSortSequential(arr, mid + 1, right);
	}
	merge(arr, left, mid, right);
}
// ======================================
void copyArray(const vector<int>& source, vector<int>& dest) {
	for (int i = 0; i < source.size(); i++) {
		dest[i] = source[i];
	}
}
// ======================================
int main() {
	int size;
	cout << "Enter size of array: ";
	cin >> size;

	vector<int> original(size), seqArr(size), parArr(size);
	generateArray(original, size);

	copyArray(original, seqArr);
	copyArray(original, parArr);

	cout << "\nOriginal Array: ";
	printArray(original);

	// Sequential Sort Timing
	auto startTime = high_resolution_clock::now();
	mergeSortSequential(seqArr, 0, size - 1);
	auto endTime = high_resolution_clock::now();
	auto seqTime = duration_cast<seconds>(endTime - startTime);

	// Parallel Sort Timing
	startTime = high_resolution_clock::now();
	mergeSortParallel(parArr, 0, size - 1);
	endTime = high_resolution_clock::now();
	auto parTime = duration_cast<seconds>(endTime - startTime);

	cout << "\nSorted Array (Sequential):\n";
	printArray(seqArr);

	cout << "\nSorted Array (Parallel):\n";
	printArray(parArr);

	cout << "\n\nPerformance:\n";
	cout << "Sequential Time: " << seqTime.count() << " seconds\n";
	cout << "Parallel Time: " << parTime.count() << " seconds\n";

	return 0;	
}
// ======================================

/*
auto startTime = high_resolution_clock::now();
    sequentialQuickSort(seqArr, 0, size - 1);
    auto endTime = high_resolution_clock::now();

    auto seqTime = duration_cast<seconds>(endTime - startTime);
*/