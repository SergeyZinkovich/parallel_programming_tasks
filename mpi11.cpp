#include "mpi.h"
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    int size, rank;
    MPI_Init(&argc, &argv);

    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // инициализация матрицы каждым процессом
    int N = 500;
		vector<vector<int>> matrixA(N, vector<int>(N, 1));
		vector<vector<int>> matrixB(N, vector<int>(N, 1));
		vector<vector<int>> result(N, vector<int>(N, 0));

    MPI_Barrier(MPI_COMM_WORLD); //барьерная синхронизация процессов
    // начало замера времени для каждого процесса
    double start_time = MPI_Wtime();
    // перемножение матриц
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    // конец замера времени
    double time = MPI_Wtime() - start_time;
    // вывод время выполнения перемножения матриц на каждом процессе
    cout << "process: " << rank << ", time: " << time << endl;

    MPI_Finalize();

    return EXIT_SUCCESS;
}