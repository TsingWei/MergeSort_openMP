#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



void mergeAdd(int arr[], int left, int mid, int right, int *temp){//实现“治”
	int i = left;
	int j = mid + 1;
	int k = left;//临时下标
	while (i <= mid&&j <= right){
		if (arr[i] < arr[j]){
			temp[k++] = arr[i++];
		}
		else{
			temp[k++] = arr[j++];
		}
	}
	while (i <= mid){
		temp[k++] = arr[i++];
	}
	while (j <= right){
		temp[k++] = arr[j++];
	}
	//把temp中的内容拷给arr数组中
	//进行归并的时候，处理的区间是arr[left,right),对应的会把
	//这部分区间的数组填到tmp[left,right)区间上
	memcpy(arr + left, temp + left, sizeof(int)*(right - left+1));
}
void mergeSort(int arr[],int left,int right,int *temp){
	int mid = 0;
	
	if (left < right){
		#pragma omp parallel sections
		{
			mid = left + (right - left) / 2;
			#pragma omp section
			mergeSort(arr, left, mid, temp);
			#pragma omp section
			mergeSort(arr, mid + 1, right, temp);
		}
			mergeAdd(arr, left, mid, right, temp);
		
		
	}
	
}



int main(){
	int arr[] = { 8,4,5,7,1,3,6,2};
	int len = sizeof(arr)/sizeof(arr[0]);
	int *temp = (int*)malloc(sizeof(int)*len);
 
	mergeSort(arr, 0, len - 1, temp);
	free(temp);
   
	for (int i = 0; i < len; i++){
        
		printf("%d ", arr[i]);
	}
    printf("\n");
	system("echo \"end\"");
	return 0;
}