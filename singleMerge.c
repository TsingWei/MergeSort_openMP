#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
//#include <time.h>
//#include <sys/time.h>
#define CHUNK_TH 100 
// int CHUNK = 1;
void mergeAdd(int arr[], int left, int mid, int right, int *temp)
{
	int i = left;
	int j = mid + 1;
	int k = left; //临时下标
	while (i <= mid && j <= right)
	{
		if (arr[i] < arr[j])
		{
			temp[k++] = arr[i++];
		}
		else
		{
			temp[k++] = arr[j++];
		}
	}
	while (i <= mid)
	{
		temp[k++] = arr[i++];
	}
	while (j <= right)
	{
		temp[k++] = arr[j++];
	}

	memcpy(arr + left, temp + left, sizeof(int) * (right - left + 1));
}

void mergeSort_serial(int arr[], int left, int right, int *temp)
{

	if (left < right)
	{	
		int mid = left + (right - left) / 2;
		mergeSort_serial(arr, left, mid, temp);
		mergeSort_serial(arr, mid + 1, right, temp);
		mergeAdd(arr, left, mid, right, temp);
	}
}



int main()
{
	//omp_set_num_threads(2);
	int len;
	scanf("%d", &len);
	int arr[len]; // = {0};
	for (int i = 0; i < len; i++)
		scanf("%d", &arr[i]);

	int *temp = (int *)malloc(sizeof(int) * len);

	// long start, end;
	// struct timeval timecheck;
	// gettimeofday(&timecheck, NULL);
	// start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;

	struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);

	mergeSort_serial(arr, 0, len - 1, temp);
	free(temp);
	// gettimeofday(&timecheck, NULL);
	// end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
	// printf("%ld milliseconds elapsed\n", (end - start));
	// for (int i = 0; i < len; i++){
	// 	printf("%d ", arr[i]);
	// }
	// printf("\n");
	// system("echo \"end\"");
	clock_gettime(CLOCK_REALTIME, &finish);
    printf("from omp: %lf\n", (finish.tv_sec + 1.e-9 * finish.tv_nsec) -
                          (start.tv_sec + 1.e-9 * start.tv_nsec));

	return 0;
}