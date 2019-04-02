#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int fib_ser(int n)
{
  if (n < 2)
    return n;
  else
    return fib_ser(n-1) + fib_ser(n-2);
}

int fib(int n)
{
  int i, j;

  if (n <= 20)
    return fib_ser(n);
  else
  {
    #pragma omp paralle num_threads(2)
    {
    #pragma omp task shared(i)
    i = fib(n-1);
    #pragma omp task shared(j)
    j = fib(n-2);
    #pragma omp taskwait
    return i+j;
    }
  }
}

int main(int argc, char *argv[]){
    int len  = atoi(argv[1]);
    //printf("DONE\n");
    int s = fib(len);
    printf("%d DONE\n",s);
    return 0;
}