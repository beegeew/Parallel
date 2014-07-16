/*
Beverly Wertz
CS4379 - Project 3 
Calculating gravitational force on celestial bodies in a solar system

The idea that I wanted to implement is To split the computational area
into equal parts using the knowledge that it is a right triangle. This
triangle can be further split into smaller sub triangles as long as the 
number of processes is a perfect square which is a power of two. Without
this property, this implementation would not work. 

The difficulty I had in getting this implemented was being able to determine
the start and end points for each triangular area. It was simple to calculate
without overlap on paper but I struggled to find an efficient algorithm that 
could achieve the desired row and column communicators. (I was always able
to figure out at least one of the communicators but the other one didn't
seem to follow a pattern that could be defined by an algorithm).

To this end, I decided to go with an approach that would run the calculation
on any (((i-1)*(i-2))/2)%size == rank which sould evenly distribute the 
computations among all processes.

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
	int rank, size, i, j;
	
	//Initialize the start and endtime variables
	double startTime, endTime;
	
	//Initialize the MPI comm and retrieve the rank and size of this process
	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);
	
	//Set our N value to 2*P
	const int N = 2*size;
	
	//Allocate space for the planetary mass and force arrays
	double *mass, *force, *localForce;
	mass = malloc(N*sizeof(double));
	force = malloc(N*sizeof(double));
	localForce = malloc(N*sizeof(double));
	
	if (rank == 0)
	{	for ( i = 0; i < N; i++) {
			mass[i] = 2654 + i*(i+5);
	}}
	
	for (i = 0; i < N; i++){
		force[i] = 0.0;
		localForce[i] = 0.0;
	}
	
	//Get the start time
	if (rank == 0) startTime = MPI_Wtime();	
	
	//logP send to all other processes
	MPI_Bcast(mass,N, MPI_DOUBLE, 0, comm);
	MPI_Barrier(comm);
	
	//setup variables to run the computations
	int compute = 0;
	double diff, tmp;
	
	//Calculate the gravitational force between each planetary pair
	for (i = 1; i < N; i++) {
		for (j = 0; j < i; j++) {
			if (i < 2 && j%size == rank)
				compute = 1;
			else if (i < 3 && j%size == rank)
				compute = 1;
			else if ((((i-1)*(i-2))/2+j)%size == rank)
				compute = 1;
			
			if (compute) {
				diff = mass[i]-mass[j];
				tmp = -C/(diff*diff);
				localForce[i]+=tmp;
				localForce[j]-=tmp;
				compute = 0;
			}
	}}
	
	//Wait for all calculations to be completed
	MPI_Barrier(comm);
	
	//Gather all the calculations together
	MPI_Reduce(localForce,force, N, MPI_DOUBLE,MPI_SUM,0,comm);

	//Get the end time and print result
	if (rank == 0) {
		endTime = MPI_Wtime();
		printf("Elapsed time is %f\n",endTime-startTime);
	}	

	//free memory
	free(mass);
	free(force);
	free(localForce);
	
	//Close out all processes
	MPI_Finalize();
	return 0;
}

