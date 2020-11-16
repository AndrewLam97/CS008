/*
 * Author: Andrew Lam
 * Project: BPlusTree
 * Purpose: Main Test File
 * Notes: Header File.
 */
#include "b_plus_tree.h"
#include <iostream>
#include <random>
#include <time.h>
#include <cassert>
using namespace std;

int random_num() { //returns random number 1-100
    return (rand() % 100) + 1;
}


int main(){
    BPlusTree<int> bpt(3);
    cout << "Beginning Auto Test:" << endl;
    cout << "Inserting even numbers from 0-1000..." << endl;
    for(int i=0;i<=1000;i+=2){
        bpt.insert(i);
    }

    int i = 0;
    while(i<1000 && bpt.contains(i)){
        i+=2;
        if(bpt.contains(i) == false){
            cout << "Error finding element" << endl;
            break;
        }
    }
    if(i == 1000){ cout << endl << "All elements verified..." << endl; }

    i = 1;
    while(i<1000 && !bpt.contains(i)){
        i+=2;
        if(bpt.contains(i) == true){
            cout << "Found non-inserted element" << endl;
            break;
        }
    }
    if(i == 1001) { cout << endl << "No extra elements inserted" << endl; }

    cout << endl << endl << "Beginning Manual Test: " << endl;

    srand(time(NULL));
    BPlusTree<int> bpt1(3);

    char input;
    int key;

    std::cout << "[R]andom  [I]nsert  R[e]move  [P]rint  e[X]it: ";
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
            bpt1.insert(random);
        }
        break;

        case 'i':
        {
            std::cout << "?";
            std::cin >> key;
            std::cout << endl
                      << "-- Inserting " << key << endl;
            bpt1.insert(key);
        }
        break;

        case 'e':
        {
            std::cout << "?";
            std::cin >> key;
            std::cout << endl
                      << "-- Removing " << key << endl;
            bpt1.remove(key);
        }
        break;

        case 'p':
        {
            std::cout << "Printing tree in ascending order: " << endl;
            bpt1.traverse();
            cout << endl;
        }
        break;
        case 'x':
        {
        }
        break;

        default:
            break;
        }
        std::cout << "[R]andom  [I]nsert  R[e]move  [P]rint  e[X]it: ";
        cin >> input;
    }

    cout << endl << "Exiting and Printing BPlusTree in ascending order: " << endl;
    bpt1.traverse();
    cout << endl;
    

    system("PAUSE");
    return 0;
}