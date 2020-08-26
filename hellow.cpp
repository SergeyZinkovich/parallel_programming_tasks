
#include <stdio.h>
#include<iostream>
int main(int argc, char *argv[])
{
setlocale(LC_ALL, "Russian");
printf("Последовательная область 1\n");
#pragma omp parallel
{
printf("Параллельная область\n");
}
printf("Последовательная область 2\n");
}