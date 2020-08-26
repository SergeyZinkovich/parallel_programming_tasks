#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;

void vecSum(int rank, int commSize, const vector<int>& vec) {
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    vector<int> vec_sizes = {100000, 1000000, 10000000, 100000000, 100000000, 100000000};

		for (int h: vec_sizes){
    		vector<int> vec(h, 1);
				int count;
    		if (rank == size - 1) {
        		count = vec.size() - (size - 1) * (vec.size() / size);
    		}
    		else {
        		count = vec.size() / size;
    		}

    		int sum = 0;

    		for (int i = 0; i < count; i++) {
        		sum += vec[ rank * (vec.size() / size) + i];
    		}

				double start = MPI_Wtime();

    		int result = 0;

    		MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    		if (rank == 0) {
						cout << "array size: " << vec.size() << endl;
        		cout << "time: " << MPI_Wtime() - start << endl;
        		cout << result << endl;
    		}
		}

    MPI_Finalize();

    return EXIT_SUCCESS;
}