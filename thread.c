#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#define NUM_THREADS	5

struct aug{
  int* arr;
  int left;
  int mid;
  int right;
  int* temp;
};


void mergeAdd(struct aug* arg)
{
	int i = arg->left;
	int j = arg->mid + 1;
	int k = arg->left; //临时下标
	while (i <= arg->mid && j <= arg->right)
	{
		if (arg->arr[i] < arg->arr[j])
		{
			arg->temp[k++] = arg->arr[i++];
		}
		else
		{
			arg->temp[k++] = arg->arr[j++];
		}
	}
	while (i <= arg->mid)
	{
		arg->temp[k++] = arg->arr[i++];
	}
	while (j <= arg->right)
	{
		arg->temp[k++] = arg->arr[j++];
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

void mergeSort_thread_create(pthread_t threads[],int i, int arr[], int left, int right, int *temp)
{

	if (left < right)
	{	
		int mid = left + (right - left) / 2;
		mergeSort_serial(arr, left, mid, temp);
		mergeSort_serial(arr, mid + 1, right, temp);
		mergeAdd(arr, left, mid, right, temp);
	}
}

int main(int argc, char *argv[])
{
  int NUM_THREADS  = atoi(argv[1]);
  pthread_t threads[NUM_THREADS];

  int len;
	scanf("%d", &len);
	int arr[len]; // = {0};
	for (int i = 0; i < len; i++)
		scanf("%d", &arr[i]);

	int *temp = (int *)malloc(sizeof(int) * len);

  // struct msg arg[NUM_THREADS];
  // char* word = "Hello World! It's me, thread #";
  int t=0;
  for(int t=0;t<NUM_THREADS;t++){
    // printf("In main: creating thread %d\n", t);
    // arg[t] = (struct msg){t, word};
    pthread_create(&threads[t], NULL, &PrintHello, &arr[t]);
  }
  for(int t=0;t<NUM_THREADS;t++)
    pthread_join(threads[t], NULL);
  printf("\nall threads finish.\n");
  /* Last thing that main() should do */
  pthread_exit(NULL);
}