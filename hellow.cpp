
#include <stdio.h>
#include<iostream>
int main(int argc, char *argv[])
{
setlocale(LC_ALL, "Russian");
printf("���������������� ������� 1\n");
#pragma omp parallel
{
printf("������������ �������\n");
}
printf("���������������� ������� 2\n");
}