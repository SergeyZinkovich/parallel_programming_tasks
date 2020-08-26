#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		
		vector<int> vec_sizes = {100000, 1000000, 10000000, 100000000};
		for (int i: vec_sizes){
    		int vector_size = i;

    		vector<int>vec(vector_size, 1);

    		if (rank == 0) {
        		int leftSize = vec.size() / 2;
        		int rightSize = vec.size() - leftSize;

        		double start_time = MPI_Wtime();

        		MPI_Send(vec.data(), leftSize, MPI_INT, 2*rank + 1, 0, MPI_COMM_WORLD);
        		MPI_Send(vec.data() + leftSize, rightSize, MPI_INT, 2*rank + 2, 0, MPI_COMM_WORLD);

        		int leftSum, rightSum;
        		MPI_Recv(&leftSum, 1, MPI_INT, 2*rank + 1,  MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        		MPI_Recv(&rightSum, 1, MPI_INT, 2*rank + 2, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
						cout << "array size: " << vec.size() << endl;
        		cout << "time: " << MPI_Wtime() - start_time << endl;
        		cout << leftSum + rightSum << endl;
    		}
    		else {
        		MPI_Status status;
        		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
						int count;
        		MPI_Get_count(&status, MPI_INT, &count);
        		int* arr = new int[count];

        		MPI_Recv(arr, count, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        		int leftSize = count / 2;
        		int rightSize = count - leftSize;

        		int leftSum = 0, rightSum = 0;

        		if (2*rank + 1 < size) {
            		MPI_Send(arr, leftSize, MPI_INT, 2*rank + 1, 0, MPI_COMM_WORLD);
            		MPI_Recv(&leftSum, 1, MPI_INT, 2*rank + 1,  MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        		}
        		else {
            		for (int i = 0; i < leftSize; i++) {
                		leftSum += arr[i];
            		}
        		}

        		if (2*rank + 2< size) {
            		MPI_Send(arr + leftSize, rightSize, MPI_INT, 2*rank + 2, 0, MPI_COMM_WORLD);
            		MPI_Recv(&rightSum, 1, MPI_INT, 2*rank + 2, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        		}
        		else {
            		for (int i = leftSize; i < count; i++) {
                		rightSum += arr[i];
            		}
        		}

        		int sum = leftSum + rightSum;

       		 MPI_Send(&sum, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);

        		delete[] arr;
    		}
		}

    MPI_Finalize();

    return EXIT_SUCCESS;
}