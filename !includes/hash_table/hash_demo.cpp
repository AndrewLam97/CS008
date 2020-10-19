/*
 * Author: Andrew Lam
 * Project: Hash Table
 * Purpose: Double and Chained Hash Tables
 * Notes: Interactive application to test all functionality
 */
#include "double_hash_table.h"
#include "chained_hash_table.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

//Helper Functions
int random_num()
{ //returns random number 1-10000
    return (rand() % 10000) + 1;
}

// struct Record{
//     T item;
//     int key;
//     enum Usage info;
// };

void test_double_interactive();
void test_chained_interactive();

int main(){
    const bool INTERACTIVE_DOUBLE = true;
    const bool INTERACTIVE_CHAINED = false;
    const bool RANDOM_DOUBLE = false;
    const bool RANDOM_CHAINED = false;
    
    if (INTERACTIVE_DOUBLE){
        cout<<"--------------------------- INTERACTIVE DOUBLE ---------------------------"<<endl;
        test_double_interactive();
    }

    if (INTERACTIVE_CHAINED){
        cout<<"--------------------------- INTERACTIVE CHAINED ---------------------------"<<endl;
        test_chained_interactive();
    }

    if (RANDOM_CHAINED){
        //----------- RANDOM TEST ------------------------------
        //. . . . . .  Chained Hash Table . . . . . . . . . . .;
    }

    if (RANDOM_DOUBLE){
        //----------- RANDOM TEST ------------------------------
        //. . . . . .  Double Hash Table . . . . . . . . . . .;
    }

    cout<<endl<<endl<<endl<<"---------------------------------"<<endl;
}

void test_double_interactive(){
    srand(time(NULL));
    int CAPACITY = 17;

    Double_Hash_Table<int> dh(CAPACITY);

    char input;
    int value;
    int value2;

    std::cout << "[R]andom  [I]nsert  [F]ind   [D]elete  [S]ize  e[X]it: ";
    std::cin >> input;
    while (input != 'x')
    {
        switch (input)
        {
        case 'r':
        {
            int random = random_num();
            int random2 = random_num();
            std::cout << endl
                      << "-- Inserting " << random << ":" << random2 << endl;
            Record<int> temp = {random2, random, Used}; 
            dh.insert(temp);
        }
        break;

        case 'i':
        {
            std::cout << "Insert?";
            std::cin >> value;
            std::cin >> value2;
            std::cout << endl
                      << "-- Inserting " << value << ":" << value2 << endl;
            Record<int> temp = {value2, value, Used};
            dh.insert(temp);
        }
        break;

        case 'f':
        {
            std::cout << "Find?";
            std::cin >> value;
            int pos = dh.findIndex(value);
            if(pos > CAPACITY || pos < 0 || pos == NULL){
                cout << value << " NOT FOUND" << endl;
            }
            else{
                Record<int> temp = dh.search(pos);
                std::cout << temp.key << ":" << temp.item << endl;
            }
        }
        break;

        case 'd':
        {
            std::cout << "Delete?";
            std::cin >> value;
            if(dh.remove(value)){
                cout << endl << value << " REMOVED" << endl;
            }

        }
        break;

        case 's':
        {
            cout << endl << "Size: " << dh.getSize() << endl;
        }

        case 'x':
        {

        }
        break;

        default:
            break;
        }
        dh.printTable();
        cout << endl << endl << endl;

        std::cout << "[R]andom  [I]nsert  [F]ind   [D]elete  [S]ize  e[X]it: ";
        cin >> input;
    }
    system("PAUSE");
}

void test_chained_interactive(){
    srand(time(NULL));
    int CAPACITY = 17;

    Chained_Hash_Table<int> ch(CAPACITY);

    char input;
    int value;
    int value2;

    std::cout << "[R]andom  [I]nsert  [F]ind   [D]elete  e[X]it: ";
    std::cin >> input;
    while (input != 'x')
    {
        switch (input)
        {
        case 'r':
        {
            int random = random_num();
            int random2 = random_num();
            std::cout << endl
                      << "-- Inserting " << random << ":" << random2 << endl; 
            ch.insert(random, random2);
        }
        break;

        case 'i':
        {
            std::cout << "?";
            std::cin >> value;
            std::cin >> value2;
            std::cout << endl
                      << "-- Inserting " << value << ":" << value2 << endl;
            ch.insert(value, value2);
        }
        break;

        case 'f':
        {
            std::cout << "?";
            std::cin >> value;
            cout << value << ":" << ch.search(value) << endl;
        }
        break;

        case 'd':
        {
            std::cout << "?";
            std::cin >> value;
            if(ch.remove(value)){
                cout << endl << value << " REMOVED" << endl;
            }

        }
        break;
        case 'x':
        {
        }
        break;

        default:
            break;
        }
        ch.printTable();
        cout << endl << endl << endl;

        std::cout << "[R]andom  [I]nsert  [F]ind   [D]elete  e[X]it: ";
        cin >> input;
    }
    system("PAUSE");
}