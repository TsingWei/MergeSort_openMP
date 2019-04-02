#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#define NUM_THREADS	5
int NUM_THREADS;
struct aug{
  int* arr;
  int left;
  int id;
  int right;
  int* temp;
};


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
	printf("Hi\n");
}

void mergeSort_serial(struct aug* arg)
{

	if (arg->left < arg->right)
	{	
		int mid = arg->left + (arg->right - arg->left) / 2;
		struct aug temp_arg1=(struct aug){arg->arr, arg->left, arg->id, mid, arg->temp };
		struct aug temp_arg2=(struct aug){arg->arr, mid, arg->id, arg->right, arg->temp };
	
		mergeSort_serial(&temp_arg1);
		mergeSort_serial(&temp_arg1);
		mergeAdd(arg->arr, arg->left, mid, arg->right, arg->temp);
	}
}

void mergeSort_thread_create(struct aug* arg)
{
	
	if (arg->id>=NUM_THREADS){
		
		//mergeSort_serial(arr, left, right, temp);
		pthread_t temp_thread;
		pthread_create(&temp_thread, NULL, &mergeSort_serial, &arg);
		pthread_join(temp_thread, NULL);
	}
	else if (arg->left < arg->right)
	{	
		int mid = arg->left + (arg->right - arg->left) / 2;
		struct aug temp_arg1=(struct aug){arg->arr, arg->left, arg->id*2, mid, arg->temp };
		struct aug temp_arg2=(struct aug){arg->arr, mid, arg->id*2, arg->right, arg->temp };
    pthread_t temp_thread1;
		pthread_t temp_thread2;
		printf("%dHere level is %d,left is %d, right is %d.\n",NUM_THREADS,arg->id,arg->left,arg->right);
    pthread_create(&temp_thread1, NULL, &mergeSort_thread_create, &temp_arg1);
		pthread_create(&temp_thread2, NULL, &mergeSort_thread_create, &temp_arg2);
		pthread_join(temp_thread1, NULL);
		pthread_join(temp_thread2, NULL);

		mergeAdd(arg->arr, arg->left, mid, arg->right, arg->temp);
	}
}

int main(int argc, char *argv[])
{
  NUM_THREADS  = atoi(argv[1]);
  pthread_t thread1;

  int len;
	scanf("%d", &len);
	int arr[len]; // = {0};
	for (int i = 0; i < len; i++)
		scanf("%d", &arr[i]);

	int *temp = (int *)malloc(sizeof(int) * len);

  // struct msg arg[NUM_THREADS];
  // char* word = "Hello World! It's me, thread #";
  int t=0;
  // for(int t=0;t<NUM_THREADS;t++){
    // printf("In main: creating thread %d\n", t);
    // arg[t] = (struct msg){t, word};
		struct aug arg=(struct aug){arr, 0, 1, len-1, temp };
    pthread_create(&thread1, NULL, &mergeSort_thread_create, &arg);
  
  // for(int t=0;t<NUM_THREADS;t++)
    pthread_join(thread1, NULL);
	for (int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
  printf("\nall threads finish.\n");
  /* Last thing that main() should do */
  pthread_exit(NULL);
}