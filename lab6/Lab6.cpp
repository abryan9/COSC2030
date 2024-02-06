//Written by Danny Radosevich
//Code for UWYO COSC 2030
//Lab6

#include <random>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <chrono>

using namespace std;

#define MAXSIZE 100000

//sorting
//function declarations
int partition(int arr[], int low, int high);
void quickSort(int quick[],int low, int high);
void merge(int arr[], int left, int mid, int right, int size);
void mergeSort(int merge[], int left, int right, int size);
void heapSort(int heap[], int size);
void heapify(int arr[],int size, int index);

int main()
{
  //for loop to get an illsorted array
  int heap[MAXSIZE];
  int merge[MAXSIZE];
  int quick[MAXSIZE];
  
  srand(unsigned(time(NULL)));
  
  for(int i = 0; i<MAXSIZE;i++)
  {
    //set all three arrays to the same thing
    int temp = rand()%(10*MAXSIZE);
    heap[i]  = temp;
    merge[i] = temp;
    quick[i] = temp;
  }
  
  //make sure the arrays are the same, so we can best test which is most efficient
  /*
  for(int i = 0; i<MAXSIZE;i++)
  {
    cout<<heap[i]<<"\t"<<merge[i]<<"\t"<<quick[i]<<endl;
  }*/
  
  //time heap sort
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  heapSort(heap,MAXSIZE);
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1);
  cout << "heapSort took " << time_span.count() << " seconds."<<endl;



  //time merge sort
  t1 = std::chrono::high_resolution_clock::now();
  mergeSort(merge,0, MAXSIZE -1, MAXSIZE);
  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1);
  cout << "mergeSort took " << time_span.count() << " seconds."<<endl;

  //time quick sorting
  t1 = std::chrono::high_resolution_clock::now();
  quickSort(quick, 0, MAXSIZE -1);
  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1);
  cout << "quickSort took " << time_span.count() << " seconds."<<endl;

  //print the new arrrays
  /*
  for(int i = 0; i<MAXSIZE;i++)
  {
    cout<<heap[i]<<"\t"<<merge[i]<<"\t"<<quick[i]<<endl;
  }*/
  return 0;
}

int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int lowIndex = (low-1);
  
  for(int i = low; i< high; i++)
  {
    if(arr[i]<=pivot)
    {
      lowIndex++;
      swap(arr[lowIndex], arr[i]);
    }
  }
  
  swap(arr[lowIndex+1],arr[high]);
  
  return (lowIndex+1);
}

void quickSort(int quick[],int low, int high)
{
  if(low<high)
  {
    int partIndex = partition(quick,low,high);

    //sort elements based on the partition
    quickSort(quick,low, partIndex-1);
    quickSort(quick,partIndex+1, high);
  }
}

void merge(int arr[], int left, int mid, int right, int size)
{
  int i, j, k = 0; //control variables for later
  int sizeOne = mid -left +1; //size of left arrays
  int sizeTwo = right - mid;//size of right array

  //arrays for each size
  //int *a = new int[variable_int];
  int *leftArray = new int[sizeOne];
  int *rightArray = new int[sizeTwo];

  //copy the data into the arrays
  for(i = 0; i<sizeOne; i++ )
  {
    leftArray[i] = arr[i+left];
  }
  
  for(j = 0; j<sizeTwo; j++)
  {
    rightArray[j] = arr[mid+1+j];
  }

  i = 0;
  j = 0;
  k = left;

  while(i<sizeOne && j<sizeTwo && k<size)
  {
    if(leftArray[i]<=rightArray[j])
    {
      arr[k] = leftArray[i];
      i++; //only increment when we use an element
    }
    else
    {
      arr[k] = rightArray[j];
      j++;//same as above
    }
    k++;
  }

  //now we need to clear the remainder in the arrays
  while(i<sizeOne && k <size)
  {
    arr[k] = leftArray[i];
    i++;
    k++;
  }
  
  while(j<sizeTwo && k <size)
  {
    arr[k] = rightArray[j];
    j++;
    k++;
  }
  
  delete[] leftArray;
  delete[] rightArray;
}

void mergeSort(int toMerge[], int left,int right, int size)
{
  if(left<right)
  {
    //find the mid point
    int mid = left+(right-left)/2;

    //recursivley call mergeSort
    mergeSort(toMerge, left, mid, size);
    mergeSort(toMerge, mid+1, right, size);
    //put the whole thing together
    merge(toMerge, left, mid, right, size);
  }
}

//Heap sort functions
void heapify(int arr[], int size, int index)
{
  int largestPos = index; //set the largest as the root
  int leftChildPos  = 2*index+1; //get the left child with offset
  int rightChildPos = 2*index+2; //get right child by offset

  cout << leftChildPos << " " << rightChildPos << " " << index << endl;

  //check if left child in bounds and larger than root
  if(leftChildPos<size && arr[leftChildPos]>arr[largestPos])
  {
    largestPos = leftChildPos; //we found a new largest
  }
  
  if(rightChildPos<size && arr[rightChildPos]>arr[largestPos])
  {
    largestPos = rightChildPos; //we found a new largest
  }
  
  //check if the largest is no longer root (we switched)
  if(largestPos != index)
  {

    // SWAP two elements in the array

    int tmp = arr[largestPos];
    arr[largestPos] = arr[index];
    arr[index] = tmp;
	
    // Recursively heapify the affected sub-tree
    heapify(arr, size, largestPos);
  }
}
void heapSort(int heap[], int size)
{
  //rearranges the array
  for(int i = size/2 - 1; i>=0; i--)
  {
    //call heapify
    heapify(heap,size,i);
  }

  
  for(int i = size-1; i>=0; i--)
  {
    // Move current root to end
    swap(heap[0], heap[i]);
    // call max heapify on the reduced heap
    heapify(heap, i, 0);
  }
}