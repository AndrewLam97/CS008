/*
 * Author: Andrew Lam
 * Project: Heap
 * Purpose: Interactive Testing Interface
 * Notes: Heap Test File, prints heap on exit
 */
#include "heap.h"
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

//Helper Functions
int random_num()
{ //returns random number 1-100
    return (rand() % 100) + 1;
}

int main()
{
    srand(time(NULL));
    MaxHeap<int, int> h;

    char input;
    int key;

    std::cout << "[R]andom  [I]nsert  [P]op   [C]lear    e[X]it: ";
    std::cin >> input;
    while (input != 'x')
    {
        switch (input)
        {
        case 'r':
        {
            int random = random_num();
            std::cout << endl
                      << "-- Inserting " << random << endl;
            h.insert(random, random);
        }
        break;

        case 'i':
        {
            std::cout << "?";
            std::cin >> key;
            std::cout << endl
                      << "-- Inserting " << key << endl;
            h.insert(key, key);
        }
        break;

        case 'c':
        {
            h.~MaxHeap();
        }
        break;

        case 'p':
        {
            std::cout << "Popping: " << h.getMax() << endl << endl;
            h.popMax();
        }
        break;
        case 'x':
        {
        }
        break;

        default:
            break;
        }
        cout << "[R]andom  [I]nsert  [P]op   [C]lear    e[X]it: ";
        cin >> input;
    }

    cout << endl << "Printing heap: " << endl;
    h.print_heap();

    cout << endl << "Printing heap in descending order: " << endl;
    while(!h.isEmpty()){
        cout << h.getMax() << " ";
        h.popMax();
    }

    system("PAUSE");
    return 0;
}