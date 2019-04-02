#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc, char *argv[]) 
{
	int a[80000],b[80000],c[80000];
	for(int i=0;i<80000;++i)
	{
		a[i] = i;
		b[i] = i/2;
	}
	double start = omp_get_wtime();

	#pragma omp parallel for num_threads(2)
	for (int i = 0; i < 80000; ++i)
	{
		a[i] = a[i] + b[i];
		c[i] = a[i]-i+b[i];
		c[i] += a[i]-i+b[i];
		c[i] += a[i]/2-i+b[i];
		// printf("i=%d, c[i]=%d\n", i, c[i]);
	}
	double finish = omp_get_wtime();
	printf("from omp: %lf\n", finish - start);
}
