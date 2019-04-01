 MergeSort_openMP
A multi-threads MergeSort implemented by openMP in C.
# CS302 Operating System Bonus Task 1:
Merge Sort in Multithreading
TANG Bo, ZHANG Shiqi, ZENG Xinxun, SHEN Yun
21 March 2019
## Merge Sort Algorithm
Merge Sort is a Divide and Conquer algorithm. It divides input array in two halves, calls itself
for the two halves and then merges the two sorted halves. The merge(arr, l, m, r) is key process
that assumes that arr[l..m] and arr[m+1..r] are sorted and merges the two sorted sub-arrays
into one. The basic process of merge sort can be summarized as follows1:  
  > **Algorithm 1 MergeSort(arr[], l, r)**  
  > if r > l then  
  >>    m ← (l + r)/2  
  >>    MergeSort(arr, l, m)  
  >>    MergeSort(arr, m+1, r)  
  >>    merge(arr, l, m, r) 
  >
  > end if  
## Task Requirement
### Implement a multithreading version merge sort in C language, which can deploy
divide and merge subroutines to different threads. There is no limitation about the thread
libraries. You can use pthread, thread pool, openMP and etc.
### Finish an analysis report, which includes implementation ideas, findings and analysis.
In the report, you should
* use tables or figures to illustrate your experiment results.
* compare the performance difference between single thread and multiple threads.
* analyze the relationship between the number of threads and overall performance.
* analyze the margin gain2 while every new thread adding into the program.
## Submission and Grades  

    OS_Bonus1_StudentID.zip
    |---- OS_Bonus1_StudentID.pdf
    |---- OS_Bonus1_StudentID.c
    
* Submission format: Illustrated above. Note that no report template is provided.
* Deadline: 12:00 at noon, 3 April 2019.
* Grades: At most 50 bonus points for Lab 4.
