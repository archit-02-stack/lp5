#include <iostream>
#include <omp.h>
#include <climits>
#include<chrono>
using namespace std;
using namespace std::chrono;

int main() 
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int* arr = new int[n];

    cout << "Enter elements:" << endl;
    for (int i = 0; i < n; i++)
	{
        cin >> arr[i];
    }
    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    long long sum = 0;  

    auto start = high_resolution_clock::now();

    #pragma omp parallel for reduction(min:minVal) reduction(max:maxVal) reduction(+:sum)
    for (int i = 0; i < n; i++) 
	{
        if (arr[i] < minVal)
            minVal = arr[i];
        if (arr[i] > maxVal)
            maxVal = arr[i];
        sum += arr[i];
    }

    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;

    double average = (double)sum / n;

    cout << "Minimum value: " << minVal << endl;
    cout << "Maximum value: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;
    cout << "Time taken for computation: " << duration.count() << " seconds" << endl;

    delete[] arr;
    return 0;
}
