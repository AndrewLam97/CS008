/*
 * Author: Andrew Lam
 * Project: Sort Functions
 * Purpose: Timing Sort Functions
 * Notes: main file
 */
#include "../timer/timer.h"
#include "../averager/averager.h"
#include "sort_functions.h"
#include <chrono>
#include <random>
#include <array>
#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

const bool debug = false;

float time_sort_routine(int arr[], unsigned int  size,
                        void (*f)(int *, int, int)){
    timer t;
    t.start();
    f(arr, 0, size-1);
    t.stop();
    return t.duration();
}

int main(){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    Averager quickavg;
    Averager mergeavg;
    Averager heapavg;

    //initialize arr
    const unsigned int size = 50000;
    int arr[size];
    for(int i = 0; i < size; i++){
        arr[i] = i;
    }

    for(int i = 0; i < 500; i++){
        shuffle(begin(arr), end(arr), default_random_engine(seed));
        quickavg.add(time_sort_routine(arr, size, quickSort));
    }

    for(int i = 0; i < 500; i++){
        shuffle(begin(arr), end(arr), default_random_engine(seed));
        mergeavg.add(time_sort_routine(arr, size, mergeSort));
    }

    for(int i = 0; i < 500; i++){
        shuffle(begin(arr), end(arr), default_random_engine(seed));
        heapavg.add(time_sort_routine(arr, size, heapSort));
    }

    cout << "SORT TIME AVERAGES - 500 ITERATIONS:" << endl;
    cout << "QuickSort(50,000): " << quickavg.getAverage() << endl;
    cout << "MergeSort(50,000): " << mergeavg.getAverage() << endl;
    cout << "HeapSort(50,000):  " << heapavg.getAverage() << endl;



    system("PAUSE");

    return 0;
}