//Beverly Wertz
//CS4379 - Project 4
//Sequential code
//
//Runtime Results:  
//Time elapsed for cuda parallel code is: 503.266418 ms
//
//Time elapsed for sequential code is: 15.2684 seconds

#include <iostream>
#include <iomanip>
#include <cmath>
#include "hr_time.h"

using namespace std;

#define N 1024

int main(int argc, char* argv[])
{
	int **A, **B, **result;
	CStopWatch myTimer;

	//allocate space for the matrices
	A = (int**) malloc(N*sizeof(int*));
	B = (int**) malloc(N*sizeof(int*));
	result = (int**) malloc(N*sizeof(int*));

	for (int i = 0; i < N; i++) {
		A[i] = (int*) malloc(N*sizeof(int));
		B[i] = (int*) malloc(N*sizeof(int));
		result[i] = (int*) malloc(N*sizeof(int));
	}

	//put some starting data in the matrices
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			A[i][j] = i*j;
			B[i][j] = (N-i)*(N-j);
			result[i][j] = 0;
		}
	}

	//Uncomment the following code to view the values output by the matrix multiplication 
	//This is here mostly for verification of correctness

	/*//Print out the current arrays
	cout << "\nMatrix A contains the following values:\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << setw(4) << A[i][j];
		}
		cout << endl;
	}

	cout << "\n\nMatrix B contains the following values:\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << setw(4) << B[i][j];
		}
		cout << endl;
	}*/
	cout << "\nResources allocated. Starting Timer\n";
	myTimer.startTimer();

	//Perform the matrix multiplication
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				result[i][j] += A[i][k]*B[k][j];
	
	myTimer.stopTimer();
	/*cout << "\n\nResulting matrix contains the following values:\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << setw(6) << result[i][j];
		}
		cout << endl;
	}*/

	cout << "\nTime elapsed for sequential code is: " << myTimer.getElapsedTime() << " seconds\n";

	delete *A;
	delete *B;
	delete *result;

	cin.get();

	return 0;
}