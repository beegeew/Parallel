/*
Beverly Wertz
CS4379 - Project 3 
Calculating gravitational force on celestial bodies in a solar system

The idea behind my implementation is To split the computational area
into equal parts using the knowledge that it is a right triangle. This
triangle can be further split into smaller sub triangles as long as the 
number of processes is a perfect square which is a power of two. Without
this property, this implementation would not work. 

The process counts in consideration will be 1, 4, 16. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

#define C 1.23456

int main(int argc, char **argv)
{
	//Setup variables to capture the rank, size, iterate through the triangle
	//startrow and start column of each process and the row communicator
	//Also setup a char value to track the orientation of the triangle
	int rank, size, i, j, startrow, startcol, rowComm, rootP;
	//orientation tracks the vertical side of the triangle - r for if 
	//the vertical side is on the right and l if the vertical side is on
	//the left.
	char orient = 'r';
	
	//Initialize the start and endtime variables
	double startTime, endTime;
	
	//Initialize the MPI comm and retrieve the rank and size of this process
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//Set our N value to 2*P
	const int N = 2*size;
	//Get the sqrt of the # of processes casted as an int
	rootP = (int) sqrt(size);
	
	//Allocate space for the planetary mass and force arrays
	double *mass, *force;
	if (rank == 0) {
		mass = malloc(N*sizeof(double));
		force = malloc(N*sizeof(double));
	} else {
		mass = malloc((N/rootP)*sizeof(double));
		force = malloc((N/rootP)*sizeof(double));
	}
	
	for ( i = 0; i < N; i++) {
		mass[i] = 2654 + i*(i+5);
		printf("%f\n",mass[i]);
	}
	
	//Get the start time
	if (rank == 0) startTime = MPI_Wtime();	

	//Get the end time and print result
	if (rank == 0) {
		endTime = MPI_Wtime();
		printf("Elapsed time is %f\n",endTime-startTime);
	}	
	
	//Close out all processes
	MPI_Finalize();
	return 0;
}

