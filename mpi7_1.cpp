#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N = 1000000;
    char message;
    double time = 0;

    for (auto i = 0; i < N; i++) {
        if (rank == 0) {
            double start_time = MPI_Wtime();
            MPI_Send(&message, 0, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&message, 0, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            time += (MPI_Wtime() - start_time);
        }
        else if (rank == 1) {
            MPI_Recv(&message, 0, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&message, 0, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == 0) {
        cout << "latency: " << time/(2* N) << endl;
    }


    MPI_Finalize();
    return EXIT_SUCCESS;
}