#include <omp.h>
#include <algorithm>
#include <iostream>
using namespace std;

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void printArray(int arr[], int size) {
  for(int i = 0; i < size; i++) 
    cout << arr[i] << " ";
  cout << endl;
}

void oddEvenSortParallelFor(int arr[], int n) {
  for(int phase = 0; phase < n; phase++){
    if(phase % 2 == 0){
      #pragma omp parallel for
      for(int i = 1; i < n; i+=2){
        if(arr[i-1] > arr[i])
          swap(&arr[i-1], &arr[i]);  
      }
    }
    else {
      #pragma omp parallel for   
      for(int i = 1; i < n-1; i+=2){
        if(arr[i] > arr[i+1])
          swap(&arr[i], &arr[i+1]);
      }
    }
  }
}

void oddEvenSortParallel(int arr[], int n) {
  #pragma omp parallel
  {
    for(int phase = 0; phase < n; phase++){
      if(phase % 2 == 0){
        #pragma omp for
        for(int i = 1; i < n; i+=2){
          if(arr[i-1] > arr[i])
            swap(&arr[i-1], &arr[i]); 
        }
      }
      else {
        #pragma omp for
        for(int i = 1; i < n-1; i+=2){
          if(arr[i] > arr[i+1])
            swap(&arr[i], &arr[i+1]);
        }  
      }
    } 
  }
}

int main() {  
  int arr[] = {5, 3, 4, 1, 2};
  int n = sizeof(arr)/sizeof(arr[0]);

  oddEvenSortParallelFor(arr, n); 
  
  cout << "Odd Even Sort usando Parallel For:\n";
  printArray(arr, n);

  int arr2[] = {5, 3, 4, 1, 2};  
  
  oddEvenSortParallel(arr2, n);

  cout << "Odd Even Sort usando Parallel:\n";
  printArray(arr2, n);

  return 0;
}