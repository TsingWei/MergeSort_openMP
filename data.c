#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int* generator(int n){
    int *temp = (int*)malloc(sizeof(int)*n);
    // int arr[n];
    for(int i=0;i<n;i++)
        temp[i]=rand()%(10*n);
    return temp;
}

int main(int argc, char *argv[]){
    
    int len  = atoi(argv[1]);
    
    int *arr = generator(len);
    printf("%d\n",len);
	for (int i = 0; i < len; i++){
        
		printf("%d ",arr[i]);
	}
    printf("\n");
}
