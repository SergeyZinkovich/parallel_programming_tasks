#include <cstdlib>
#include "mpi.h"
#include <iostream>
#include<bits/stdc++.h> 

using namespace std;

int main(int argc, char* argv[]){
MPI_Init(&argc, &argv);
double time_start, time_finish;
int gen,rank, n, i, message;
int a[10];
int mul = 1;
int neg = 0;
MPI_Status status;
MPI_Comm_size(MPI_COMM_WORLD, &n);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
time_start = MPI_Wtime();
if (rank == 0)
{
	for (i=1; i<n; i++){
		MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE,
		MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		if(message % 2 == 1){
			mul *= message;
		}
		if(message < 0){
			if(neg == 0){
				neg = message;
			}
			else if(message > neg){
				neg = message;
			}
		}
	}
	cout << mul - neg << endl;
}
else{
	srand( time(NULL));
  gen = rand() - INT_MAX/2; 
	MPI_Send(&gen,1,MPI_INT,0,0,MPI_COMM_WORLD);
}
time_finish = MPI_Wtime();
MPI_Finalize();
cout << "Time " << time_finish - time_start << endl;
return 0;
}