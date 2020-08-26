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

    int vector_size = 20000000;

    std::vector<int>vector1(vector_size, 1);
    std::vector<int>vector2(vector_size, 1);


    double start_time;
    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    int chunk_size = vector_size / size;
		int start_index = rank * chunk_size;
    int local_sum = 0;

    for (int i = start_index; i < start_index + chunk_size; i++) {
    		local_sum += vector1[i] * vector2[i];
      	if(i == vector_size - 1){
						break;
				}
		}

		
    int result = 0;
    MPI_Reduce(&local_sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        cout << result << endl;

    if (rank == 0) {
        cout << "Time: " << MPI_Wtime() - start_time << endl;
    }

    MPI_Finalize();
}