#include <cstdio>
#include <omp.h>
#include <vector>
#include <cstdlib>

int main(int argc, char *argv[])
{
    int vector_size = atoi(argv[1]);
		int threads_count = atoi(argv[2]);
		int sum = 0, local_sum = 0;
    std::vector<int> vector1(vector_size, 1), vector2(vector_size, 1);
    double start = omp_get_wtime();
    #pragma omp parallel private(local_sum) num_threads(threads_count) 
    {
        #pragma omp for
        for(int i = 0; i < vector_size; ++i)
        {
						local_sum += vector1[i] * vector2[i];
        }
				#pragma omp atomic
        sum += local_sum;

    }
    double end = omp_get_wtime();
    printf("Сумма: %d\n", sum);
    printf("Время выполнения: %f\n", end-start);

}