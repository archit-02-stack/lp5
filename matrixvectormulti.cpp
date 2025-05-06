#include <iostream>
#include <omp.h>  
#include <chrono>
#define MAX_SIZE 500
using namespace std;

int main() 
{
    int N;
    cout << "Enter the size of the matrix (N x N): ";
    cin >> N;

    if (N > MAX_SIZE) 
    {
        cout << "Matrix size is too large! Please enter a value <= " << MAX_SIZE << endl;
        return -1;
    }

    int A[MAX_SIZE][MAX_SIZE], x[MAX_SIZE], y[MAX_SIZE];
    
    cout << "Enter the elements of the matrix A (row by row):\n";
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            cin >> A[i][j];
        }
    }

    cout << "Enter the elements of the vector x:\n";
    for (int i = 0; i < N; i++) 
    {
        cin >> x[i];
        y[i] = 0;  
    }

    // Matrix-vector multiplication
    auto start = chrono::high_resolution_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            y[i] += A[i][j] * x[j];
        }
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "Resultant vector y:\n";
    for (int i = 0; i < N; i++) 
    {
        cout << y[i] << " ";
    }
    cout << endl;

    cout << "Matrix-vector multiplication took " << duration.count() << " milliseconds.\n";
	return 0;
}

