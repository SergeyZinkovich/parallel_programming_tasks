#include <cstdio>
#include <omp.h>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    int vector_size = atoi(argv[1]);
    int threads_num = atoi(argv[2]);
    std::vector< vector<int> > matrix1(vector_size, vector<int>(vector_size, 2));
		std::vector< vector<int> > matrix2(vector_size, vector<int>(vector_size, 2));
		std::vector< vector<int> > matrix3(vector_size, vector<int>(vector_size));
    double start = omp_get_wtime();
    #pragma omp parallel shared(matrix3) num_threads(threads_num)
		{
			#pragma omp for
    	for (int j = 0; j < vector_size; j++){
				for (int i = 0; i < vector_size; i++) {
				
					for (int h = 0; h < vector_size; h++){
						matrix3[i][j] += matrix1[h][i] * matrix2[j][h];
					}
				}
    	}
		}
    double end = omp_get_wtime();
		double t1 = end-start;
    printf("Время выполнения c потоками = %f\n", t1);
		start = omp_get_wtime();
		for (int j = 0; j < vector_size; j++){
				
				for (int i = 0; i < vector_size; i++) {				
					for (int h = 0; h < vector_size; h++){
						matrix3[i][j] += matrix1[h][i] * matrix2[j][h];
					}
				}
    	}
		end = omp_get_wtime();
		double t2 = end-start;
    printf("Время выполнения в один поток = %f\n", t2);
		printf("Эффективность = %f\n", t2/t1*100);
		start = omp_get_wtime();
    #pragma omp parallel shared(matrix3) num_threads(threads_num)
		{
			#pragma omp for
		for (int h = 0; h < vector_size; h++){
    	for (int j = 0; j < vector_size; j++){
				for (int i = 0; i < vector_size; i++) {
				
						matrix3[i][j] += matrix1[h][i] * matrix2[j][h];
					}
				}
    	}
		}
    end = omp_get_wtime();
		t1 = end-start;
    printf("Время выполнения c потоками 2 = %f\n", t1);
		start = omp_get_wtime();
    #pragma omp parallel shared(matrix3) num_threads(threads_num)
		{
			#pragma omp for
    	for (int j = 0; j < vector_size; j++){
				for (int h = 0; h < vector_size; h++){
					for (int i = 0; i < vector_size; i++) {
				
						matrix3[i][j] += matrix1[h][i] * matrix2[j][h];
					}
				}
    	}
		}
    end = omp_get_wtime();
		t1 = end-start;
    printf("Время выполнения c потоками 3 = %f\n", t1);



}