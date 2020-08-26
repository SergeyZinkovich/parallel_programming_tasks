#include "mpi.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void create_file() {
    ofstream myfile;
    myfile.open ("file.txt");
    for (int i = 0; i < 1000; i++) {
        myfile << i << " ";
    }
    myfile.close();
}

char buf[100];

int main(int argc, char **argv)
{
    int size;
    create_file();
    int rank;
    MPI_Init(&argc, &argv);
    MPI_File fh;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_File_open(MPI_COMM_WORLD, "file.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
		MPI_File_set_view(fh, rank*100, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
		MPI_File_read_all(fh, buf, 100, MPI_CHAR, MPI_STATUS_IGNORE);    printf("process %d, buf=%s\n", rank, buf);
    MPI_File_close(&fh);

    remove("file.txt");
    MPI_Finalize();
}