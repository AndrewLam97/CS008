#include "priority_queue.h"
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

//Helper Functions
int Random(int min, int max)
{ //returns random number x-y
    return rand() % (max+1-min) + min;
}

int main(){
    srand(time(NULL));
    PQueue<int> pq;
    for (int i = 0; i<100; i++){
        pq.insert(Random(1,1000), Random(1,10));
    }

    cout << "Printing Priority Queue in descending priority..." << endl;
    pq.print_tree();

    system("PAUSE");
    return 0;
}