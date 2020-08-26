#include <mpi.h>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    int size, rank, prev, next;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    prev = rank - 1;
    next = rank + 1;

    if(rank == 0)
        prev = size - 1;
    if(rank == size - 1)
        next = 0;

    MPI_Request reqs[4];
    MPI_Status stats[4];

    float rbuf[2];
    float sbuf[2];


    MPI_Recv_init(&rbuf[0], 1, MPI_FLOAT, prev, 5, MPI_COMM_WORLD, &reqs[0]);
    MPI_Recv_init(&rbuf[1], 1, MPI_FLOAT, next, 6, MPI_COMM_WORLD, &reqs[1]);

    MPI_Send_init(&sbuf[0], 1, MPI_FLOAT, prev, 6, MPI_COMM_WORLD, &reqs[2]);
    MPI_Send_init(&sbuf[1], 1, MPI_FLOAT, next, 5, MPI_COMM_WORLD, &reqs[3]);

    sbuf[0] = rank;
    sbuf[1] = 10 * rank;

    cout << "process: " << rank << endl;
    cout << "sending to prev: " << sbuf[0] << endl;
    cout << "sending to next: " << sbuf[1] << endl;

    MPI_Startall(4, reqs);
    MPI_Waitall(4, reqs, stats);

    cout << "process: " << rank << endl;
    cout << "received from prev " << rbuf[0] << endl;
    cout << "received from next " << rbuf[1] << endl;

    MPI_Request_free(&reqs[0]);
    MPI_Request_free(&reqs[1]);
    MPI_Request_free(&reqs[2]);
    MPI_Request_free(&reqs[3]);

    MPI_Finalize();

    return EXIT_SUCCESS;
}