#ifndef SORT_FUNCTIONS_H
#define SORT_FUNCTIONS_H
#include <iostream>
using namespace std;
//Contains quicksort, mergeSort, and heapsort
//-------------------------------------------------------
// UTILITIES

//Print array
void printArray(int arr[], int size){
    cout << "[ ";
    for (int i = 0; i < size; i++)  
        cout << arr[i] << " ";  
    cout << "]" << endl;  
} 


/*-------------------------------------------------------
 QUICK SORT

Uses element at last index as pivot point, partitions array
into lower and high sub-arrays until sub-array sizes are 1.

{48 21 10 15 57 29} -> Pivot = 10, swap pivot to end
       ^
{48 21 29 15 57 10} -> Move left bound right until it finds a value >= pivot
 ^L
{48 21 29 15 57 10} -> Move right bound left until it finds a value <= pivot
 ^R
Bounds cross so all elements to the left of left bound are less than pivot and vice versa
{10 21 29 15 57 48} -> Swap pivot to final location
 ^
{10 {21 29 15 57 48}} -> Pivot = 15, swap pivot to end
           ^
{10 {21 29 48 57} 15} -> Move left and right bounds, bounds cross at 21
     ^L       ^R
{10 15 29 48 57 21} -> Swap pivot to final location
    ^
{10 15 {29 48 57 21}} -> Pivot = 48, swap pivot to end
           ^
{10 15 {29 21 57} 48} -> Partition sub-array
        ^L    ^R
{10 15 {29 21 57} 48} -> Move left bound right until it finds a value >= pivot
              ^L
{10 15 {29 21 57} 48} -> Move right bound left until it finds a value <= pivot
           ^R
Bounds cross so swap pivot to final location
{10 15 29 21 48 57}
             ^
{10 15 {29 21} 48 {57}} -> Pivot = 29, swap pivot to end
        ^
{10 15 {21 29} 48 {57}} -> Partition sub-array
           ^
{10 15 {21 29} 48 {57}} -> Move bounds
        ^L ^R
Bounds cross so swap pivot to final location (already there)
{10 15 {21} 29 48 {57}} -> Sub-array contains a single element which means it's already sorted
        ^
{10 15 21 29 48 {57}} -> Sub-array contains a single element which means it's already sorted
                 ^        
{10 15 21 29 48 57} -> SORTED
*/

// Swap two elements  
void swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  
  
//Partitions array into sub-arrays around pivot
int partition (int arr[], int low, int high)  
{  
    int pivot = arr[high]; // pivot  
    int i = (low - 1); // smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
  
void quickSort(int arr[], int low, int high)  
{  
    if (low < high)  
    {  
        int partitionIndex = partition(arr, low, high);  
 
        quickSort(arr, low, partitionIndex - 1);  
        quickSort(arr, partitionIndex + 1, high);  
    }  
}   


/*-------------------------------------------------------
// MERGE SORT

{48 21 10 15 57 29} -> Split array into two sub-arrays
{48 21 10} {15 57 29} -> Split left array into two sub-arrays
{48 21} {10} -> Split array into two sub-arrays
{48} {21} -> Sub-arrays are of size 1, merge back together in sorted order
{21 48} {10} -> Right sub-array is of size 1, merge back together in sorted order
{10 21 48} -> Left sub-array sorted, moving to right hand side
{15 57 29} -> Split right sub-array
{15 57} {29} -> Split left sub-array
{15} {57} -> Sub-arrays are of size 1, merge back together in sorted order
{15 57} {29} -> Right sub-array is of size 1, merge back together in sorted order
{15 29 57} -> Finished sorting right hand side
{10 21 48} {15 29 57} -> Both sub-arrays sorted, merge both in sorted order
{10 15 21 29 48 57} -> SORTED
*/

// Merge and sort two halves
void Merge(int *a, int low, int high, int mid)
{
    int i, j, k, temp[high - low + 1];
    i = low;
    k = 0;
    j = mid + 1;

    // Merge the two sub-arrays into temp[].
    while (i <= mid && j <= high){
        if (a[i] < a[j]){
            temp[k] = a[i];
            k++;
            i++;
        }
        else{
            temp[k] = a[j];
            k++;
            j++;
        }
    }

    // Insert all the remaining values from i to mid into temp[].
    while (i <= mid){
        temp[k] = a[i];
        k++;
        i++;
    }

    // Insert all the remaining values from j to high into temp[].
    while (j <= high){
        temp[k] = a[j];
        k++;
        j++;
    }

    // Assign sorted data stored in temp[] to a[].
    for (i = low; i <= high; i++){
        a[i] = temp[i - low];
    }
}

// Split arr
void mergeSort(int *a, int low, int high){
    int mid;
    if (low < high){
        mid = (low + high) / 2;
        // create two sub-arrays
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);

        // Merge arrs
        Merge(a, low, high, mid);
    }
}

/*-------------------------------------------------------
// HEAP SORT
{1 12 9 5 6 10} is represented as
        1
    12      9
5   6       10
number of elements n = 6
index of first non-leaf i = 2 (n/2-1)
->heapify(arr,6,2) swaps index 2 with index 5
{1 12 10 5 6 9}
        1
    12      10<
5   6       9<
->heapify(arr,6,1) doesn't do anything as   12   is already a max heap
                                           5  6
->heapify(arr,6,0) heapify at root swaps index 0 with index 1
{12 1 10 5 6 9}
        12<
    1<      10
5   6       9
->heapify downwards
{12 1 10 5 6 9}
        12
    1<      10
5   6<      9
->swap index 1 and index 4 to satisfy max heap conditions
{12 6 10 5 1 9}
        12
    6<      10
5   1<      9
->Max Heap created from array
->Remove root element by swapping with last element, reduce size by 1
{9 6 10 5 1} [12]
        9<
    6      10<
5   1    
->Heapify
{10 6 9 5 1} [12]
       10<
    6      9<
5   1   
->Swap root to last and reduce size by 1
{1 6 9 5} [10 12]
        1<
    6      9<
5      
->Heapify
{9 6 1 5} [10 12]
        9<
    6      1<
5
->Swap root to last and reduce size by 1
{5 6 1} [9 10 12]
    5<
6<      1
->Heapify
{6 5 1} [9 10 12]
    6<
5<       1
->Swap root to last and reduce size by 1
{1 5} [6 9 10 12]
    1<
5<
->Heapify
{5 1} [6 9 10 12]
    5<
1<
->Swap root to last and reduce size by 1
{1} [5 6 9 10 12]
->Size of array is 1, finished sorting
{1 5 6 9 10 12} -> SORTED
*/

// Create heap from subtree rooted with node i which is 
// an index in arr[]. n is size of heap 
void heapify(int arr[], int n, int i) 
{ 
    //Find largest among root
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left > root 
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
  
    // If right child > largest
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
  
    // Swap and continue to heapify if root is not largest
    if (largest != i) 
    { 
        swap(arr[i], arr[largest]); 
  
        // Recursively heapify sub-trees
        heapify(arr, n, largest); 
    } 
} 
   
void heapSort(int arr[], int low, int high) 
{ 
    // Build heap 
    for (int i = high / 2 - 1; i >= 0; i--) 
        heapify(arr, high, i); 
  
    // Extract items from heap
    for (int i=high-1; i>0; i--) 
    { 
        // Swap root to end
        swap(arr[0], arr[i]); 
  
        // Heapify on new sub arr
        heapify(arr, i, 0); 
    } 
} 
#endif // SORT_FUNCTIONS_H