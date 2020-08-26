#include <stdio.h>
#include <omp.h>
#include <vector>
int main(int argc, char *argv[])
{

	#ifdef _OPENMP
	printf("OpenMP is supported!\n");
	#endif

	int num, i = 0;
	int a[8];

	omp_set_num_threads(2);
	#pragma omp parallel shared(a, i) private(num) num_threads(8) 
	{
		num = omp_get_thread_num();
		if (num == 0){
			printf("Всего нитей: %d\n", omp_get_num_threads());
		}
	
			#pragma omp critical
			{
				printf("Нить номер %d\n", num);
				a[i] = num;
				i++;
			}
	}
	
	for (int j = 7; j >= 0; --j)
		printf("%d\n", a[j]);
}