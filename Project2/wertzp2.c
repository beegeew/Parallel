/*
Beverly G Wertz     - Project 2
CS4379 - Parallel Programming Spring 2012

Custom Barrier Function
It has p-1 total send and rcvs, but time of send and receives is in log p. 

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

//Set debug on(1) and off(2) to remove output display
int DEBUG = 1;

int myBarrier(MPI_Comm comm)
{
	int rank, size, numComm = 1;
	char sender ='f';
	MPI_Status myStatus;
	
	//get rank and size
	MPI_Comm_rank (comm, &rank); 
	MPI_Comm_size (comm, &size);
	
	//If it's a single process, there's nothing here to do so we exit
	if (size == 1) 
		return 0;
	
	//If the current rank is zero, then this is the first sender.
	if (rank == 0)
		sender = 't';
	
	while (numComm < size) {
		//When a sender has been flagged it will communicate to the process
		//which is 2^(step-1) away from the current rank process. 
		//eg. Rank 0 sends to rank 1 on step 1. 
		//than, rank 0 sends to rank 2, and rank 1 sends to rank 3 on step 2
		if (sender == 't') {
			MPI_Send(&sender,1,MPI_CHAR,rank+numComm,39,comm);
			if (DEBUG)
				printf("Process %d is sending to %d\n",rank,rank+numComm);
		//If we haven't been flagged as a sender, we will be receiving. 
		} else if ( rank < 2*numComm) {
			MPI_Recv(&sender,1,MPI_CHAR,MPI_ANY_SOURCE,39,comm,&myStatus);
			if (DEBUG)
				printf("Process %d is receiving from %d\n",rank,rank-numComm);
		}
		numComm*=2;
	}

	return 1;	
}

int main(int argc, char **argv)
{

	int rank,size,i,j,max = 0,startPos=0,currProcessOut = 1;;
	
	//Initializing our MPI and getting the rank and size 
	MPI_Init (&argc, &argv); 
	MPI_Comm_rank (MPI_COMM_WORLD, &rank); 
	MPI_Comm_size (MPI_COMM_WORLD, &size);
	
	myBarrier(MPI_COMM_WORLD);

	//Close out all processes
	MPI_Finalize();
	return 0;
}
