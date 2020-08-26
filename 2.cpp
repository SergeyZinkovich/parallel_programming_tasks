#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	int a[50];
	int i, sum1, sum2;
	for (int j = 0; j < 50; j++){
		a[j] = 1;
	}

	#pragma omp parallel shared(a, sum1) private(i) reduction (+: sum2)
	{
		#pragma omp for
    for (i = 0; i < 50; i++){
			sum1 += a[i];
			sum2++;
		}
	}
	printf("Обычная сумма %d\n", sum1);
	printf("С reduction %d\n", sum2);

	sum1 = 0;
	#pragma omp parallel shared(a, sum1) private(i) reduction (+: sum2)
	{
		#pragma omp for
    for (i = 0; i < 50; i++){
			#pragma omp atomic
			sum1 += a[i];
		}
	}
printf("Сумма с atomic %d\n", sum1);

	sum1 = 0;
	#pragma omp parallel shared(a, sum1) private(i) reduction (+: sum2)
	{
		#pragma omp for
    for (i = 0; i < 50; i++){
			#pragma omp critical
			sum1 += a[i];
		}
	}
printf("Сумма с critical %d\n", sum1);


}