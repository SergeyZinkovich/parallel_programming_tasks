#include <cstdio>
#include <omp.h>
#include <vector>
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
    int vector_size = atoi(argv[1]); 
    int threads_num = atoi(argv[2]);
		int max = 0;
    std::vector<int> vector(vector_size);
		srand( time(NULL));
    for (int i = 0; i < vector_size; i++){
    	vector[i] = rand();
		}
    double start = omp_get_wtime();
    #pragma omp parallel for reduction(max: max) num_threads(threads_num)
    for (int i = 0; i < vector_size; i++) {
			if ( vector[i] > max){ 
        max = vector[i];
			}
    }
    double end = omp_get_wtime();
    printf("Max = %d\n", max);
    printf("Время выполнения: %f\n", end-start);

}