#include "bplustree.h"
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

int random_num() { //returns random number 1-1000
    return (rand() % 1000) + 1;
}

int main(){
    // srand(time(NULL));

    // BPTree bpt;
    // vector<int> added;

    // cout << "Beginning Auto Test:" << endl;
    // cout << "Inserting 100 random numbers" << endl;
    // for(int i=0;i<10000;i++){
    //     int r = random_num();
    //     bpt.insert(r);
    //     added.push_back(r);
    // }

    // for(int i = 0; i < 10000;i++){
    //     if(bpt.contains(added[i]) == false){
    //         cout << "Error finding element" << added[i] << endl;
    //         bpt.display(bpt.getRoot());
    //         break;
    //     }
    //     else{
    //         cout << "Found element" << added[i] << endl;
    //         bpt.remove(added[i]);
    //     } 

    // }
    // cout << endl;
    // //bpt.display(bpt.getRoot());
    // cout << endl << "End..." << endl;


    cout << endl << endl << "Beginning Manual Test: " << endl;

    srand(time(NULL));
    BPTree<int> bpt1;

    char input;
    int key;

    std::cout << "[R]andom  [I]nsert  [S]earch R[e]move  [P]rint  e[X]it: ";
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

        case 's':
        {
            std:: cout << "?";
            std::cin >> key;
            std::cout << endl
                      << bpt1.contains(key) << endl;
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
            bpt1.display(bpt1.getRoot());
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
        std::cout << "[R]andom  [I]nsert  [S]earch R[e]move  [P]rint  e[X]it: ";
        cin >> input;
    }

    cout << endl << "Exiting and Printing BPlusTree in ascending order: " << endl;
    bpt1.display(bpt1.getRoot());
    cout << endl;


    system("PAUSE");
    return 0;
}