#include <iostream>
#include <chrono>
#include <omp.h>  
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

    int A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], C[MAX_SIZE][MAX_SIZE] = {0};

    cout << "Enter the elements of the matrix A (row by row):\n";
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            cin >> A[i][j];
        }
    }

    cout << "Enter the elements of the matrix B (row by row):\n";
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            cin >> B[i][j];
        }
    }
    
    // Parallel Matrix-matrix multiplication
    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            for (int k = 0; k < N; k++) 
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    // Output
    cout << "Resultant Matrix C = (A * B):\n";
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matrix multiplication took " << duration.count() << " milliseconds.\n";
	return 0;
}

