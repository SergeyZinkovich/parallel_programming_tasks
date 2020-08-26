#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> sizes = {50, 100, 200, 800};

    for (const auto s : sizes) {
    		auto message = new char[s*1024*1024];

    		int N = 10;
    		double time = 0;

    		for (auto i = 0; i < N; i++) {
        		if (rank == 0) {
            		double start_time = MPI_Wtime();
            		MPI_Send(message, s*1024*1024, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
            		MPI_Recv(message, s*1024*1024, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            		time += (MPI_Wtime() - start_time);
        		}
        		else if (rank == 1) {
            		MPI_Recv(message, s*1024*1024, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            		MPI_Send(message, s*1024*1024, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        		}
    		}

    		if (rank == 0) {
        		cout << "time: " << time/N << endl;
        		cout << "length in Mb: " << s << endl;
						cout << "bandwidth: " <<  (s/ time) *2 * N << endl;
    		}

    		delete[] message;

    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}