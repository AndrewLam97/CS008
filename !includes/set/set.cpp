#include "set.h"
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

// int main()
// {
//     srand(time(NULL));
//     Set<int> s(3);

//     char input;
//     int key;

//     std::cout << "[R]andom  [I]nsert  R[e]move  [P]rint  e[X]it: ";
//     std::cin >> input;
//     while (input != 'x')
//     {
//         switch (input)
//         {
//         case 'r':
//         {
//             int random = random_num();
//             std::cout << endl
//                       << "-- Inserting " << random << endl;
//             s.insert(random);
//         }
//         break;

//         case 'i':
//         {
//             std::cout << "?";
//             std::cin >> key;
//             std::cout << endl
//                       << "-- Inserting " << key << endl;
//             s.insert(key);
//         }
//         break;

//         case 'e':
//         {
//             std::cout << "?";
//             std::cin >> key;
//             std::cout << endl
//                       << "-- Removing " << key << endl;
//             s.remove(key);
//         }
//         break;

//         case 'p':
//         {
//             std::cout << "Printing tree in ascending order: " << endl;
//             s.traverse();
//             cout << endl;
//         }
//         break;
//         case 'x':
//         {
//         }
//         break;

//         default:
//             break;
//         }
//         std::cout << "[R]andom  [I]nsert  R[e]move  [P]rint  e[X]it: ";
//         cin >> input;
//     }

//     cout << endl << "Exiting and Printing BTree in ascending order: " << endl;
//     s.traverse();
//     cout << endl;
//     system("PAUSE");
//     return 0;
// }

int main(){
    Set<int> s1(3);
    Set<int> s2(3);

    cout << "Inserting 3 into s1" << endl;
    s1.insert(3);
    cout << "Inserting 123 into s1" << endl;
    s1.insert(123);
    cout << "Inserting 99 into s1" << endl;
    s1.insert(99);
    cout << "Inserting 123 into s1" << endl;
    s1.insert(123);
    cout << "Inserting 50 into s1" << endl;
    s1.insert(50);
    cout << "Inserting 9 into s1" << endl;
    s1.insert(9);
    cout << "Removing 99 from s1" << endl;
    s1.remove(99);

    cout << "Inserting 123 into s2" << endl;
    s2.insert(123);
    cout << "Inserting 7 into s2" << endl;
    s2.insert(7);
    cout << "Inserting 60 into s2" << endl;
    s2.insert(60);
    cout << "Inserting 1 into s2" << endl;
    s2.insert(1);
    cout << "Inserting 14 into s2" << endl;
    s2.insert(14);
    cout << "Removing 60 from s2" << endl;
    s2.remove(60);

    cout << endl << "Printing s1:" << endl;
    s1.traverse();
    cout << endl << "Printing s2:" << endl;
    s2.traverse();

    cout << endl << "Performing Union..." << endl;
    s1.set_union(s2);

    cout << endl << "Printing union:" << endl;
    s1.traverse();

    cout << "Printing intersection:" << endl;
    s1.set_intersect(s2);

    cout << endl;


    system("PAUSE");
    return 0;
}




