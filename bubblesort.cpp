#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>  
#include <omp.h>  
using namespace std;

int main() 
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int* arrSequential = new int[n];
    int* arrParallel = new int[n];
    
    cout << "Enter " << n << " elements for the array:\n";
    for (int i = 0; i < n; i++) 
	{
        cin >> arrSequential[i];
        arrParallel[i] = arrSequential[i];  
    }
    
    // Sequential Bubble Sort
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++) 
	{
        for (int j = 0; j < n - 1 - i; j++) {
            if (arrSequential[j] > arrSequential[j + 1]) 
			{
                swap(arrSequential[j], arrSequential[j + 1]);
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Sequential Bubble Sort Time: " << duration.count() << " seconds" << endl;

    cout << "Sorted Array (Sequential): ";
    for (int i = 0; i < n; i++) 
	{
        cout << arrSequential[i] << " ";
    }
    cout << endl;

    // Parallel Bubble Sort
    start = chrono::high_resolution_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < n - 1; i++) 
	{
        for (int j = 0; j < n - 1 - i; j++) 
		{
            if (arrParallel[j] > arrParallel[j + 1]) 
			{
                swap(arrParallel[j], arrParallel[j + 1]);
            }
        }
    }
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Parallel Bubble Sort Time: " << duration.count() << " seconds" << endl;

    cout << "Sorted Array (Parallel): ";
    for (int i = 0; i < n; i++) 
	{
        cout << arrParallel[i] << " ";
    }
    cout << endl;

    delete[] arrSequential;
    delete[] arrParallel;
	return 0;
}

