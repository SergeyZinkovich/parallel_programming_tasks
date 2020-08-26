#include <mpi.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, n, i, message;
		char m_in, m_out;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 3)
    {
        std::cout << "Hello from process " << rank << "\n";
        for (i=1; i<n; i++){
            MPI_Recv(&m_out, 1, MPI_CHAR, MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            std::cout << "Hello from process " << m_out << std::endl;
        }
    }
    else{ 
			m_in = rank + '0';
			MPI_Send(&m_in,1,MPI_CHAR,3,0,MPI_COMM_WORLD);
    }
		MPI_Finalize();

    return EXIT_SUCCESS;
}