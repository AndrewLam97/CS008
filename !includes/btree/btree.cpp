#include "btree.h"
#include "../map/pair.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

//Helper Functions
int random_num()
{ //returns random number 1-100
    return (rand() % 100) + 1;
}

int main()
{
    srand(time(NULL));
    BTree<int> bt(3);

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
            bt.insert(random);
        }
        break;

        case 'i':
        {
            std::cout << "?";
            std::cin >> key;
            std::cout << endl
                      << "-- Inserting " << key << endl;
            bt.insert(key);
        }
        break;

        case 'e':
        {
            std::cout << "?";
            std::cin >> key;
            std::cout << endl
                      << "-- Removing " << key << endl;
            bt.remove(key);
        }
        break;

        case 'p':
        {
            std::cout << "Printing tree in ascending order: " << endl;
            bt.traverse();
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

    cout << endl << "Exiting and Printing BTree in ascending order: " << endl;
    bt.traverse();
    cout << endl;
    system("PAUSE");
    return 0;
}






    // BTree<Pair<int, int> > bt(3); // A B-Tree with minium degree 3

    // Pair<int, int> tempPair{1, 11};
    // bt.insert(tempPair);

    // Pair<int, int> tempPair2{2, 22};
    // bt.insert(tempPair2);


    // bt.traverse();

 
    // BTree<int> bt(3);
    // bt.insert(5); 
    // cout << "Inserting 5" << endl;
    // bt.insert(11); 
    // cout << "Inserting 11" << endl;
    // bt.insert(99); 
    // cout << "Inserting 99" << endl;
    // bt.insert(75); 
    // cout << "Inserting 75" << endl;
    // bt.insert(32); 
    // cout << "Inserting 32" << endl;
    // bt.insert(30); 
    // cout << "Inserting 30" << endl;
    // bt.insert(68); 
    // cout << "Inserting 68" << endl;
    // bt.insert(17); 
    // cout << "Inserting 17" << endl;
  
    // cout << "Traversing tree... " << endl; 
    // bt.traverse(); 

    // int r = 32;
    // cout << "Removing: " << r << endl;
    // bt.remove(r);

    // int r1 = 123;
    // cout << "Removing: " << r1 << endl;
    // bt.remove(r1);

    // int r2 = 99;
    // cout << "Removing: " << r2 << endl;
    // bt.remove(r2);

    // int r3 = 5;
    // cout << "Removing: " << r3 << endl;
    // bt.remove(r3);

    // cout << "Traversing tree... " << endl; 
    // bt.traverse();

    
    //bt.print();
  
    //cout << bt.get(1);

    // int k = 68; 
    // cout << endl << "Searching for: " << k << endl;
    // (bt.find(k) != NULL)? cout << k << " found" << endl : cout << k << " not found" << endl;

    // int k = 68; 
    // cout << endl << "Getting: " << k << endl;
    // cout << bt.get(k) << endl;  
  
    // k = 123; 
    // cout << "Searching for: " << k << endl;
    // (bt.find(k) != NULL)? cout << k << " found" << endl : cout << k << " not found" << endl;