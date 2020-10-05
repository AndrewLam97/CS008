/*
 * Author: Andrew Lam
 * Project: AVL Tree
 * Purpose: AVL Tree Interactive Program
 * Notes: CLI
 */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "avl_tree.h"
using namespace std;

//Helper Functions
int random_num(){ //returns random number 1-100
    return (rand() % 100)+1;
}

//Driver Function
void test_avl(){
    srand(time(NULL));
    AVL<int> a;

    char input;
    int insert_input;
    int search_input;
    int erase_input;

    std::cout << "[R]andom  [I]nsert  [C]lear  [S]earch  [E]rase      e[X]it: ";
    std::cin >> input;

    while(input != 'x'){
        switch(input){
            case 'r':
            {
                int random = random_num();
                std::cout << endl << "-- Inserting " << random << endl;
                a.insert(random);
            } 
            break;
        
            case 'i':
            {
                std::cout << "?";
                std::cin >> insert_input;
                a.insert(insert_input);
            }
            break;

            case 'c':
            {
                a.~AVL();
            }
            break;
            
            case 's':
            {
                std::cout << "?";
                std::cin >> search_input;
                if(a.search(search_input)){
                    std::cout << endl << "Found: " << search_input << endl;
                }
                else std::cout << endl << "Did not find: " << search_input << endl;
            }
            break;

            case 'e':
            {
                std::cout << "?";
                std::cin >> erase_input;
                a.erase(erase_input);
            }
            break;
            case 'x':
            {

            }
            break;
            default:
            break;
        }
        tree_print(a.getRoot());
        std::cout << "[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it: ";
        std::cin >> input;
    }
}

int main(){
    test_avl();

    system("PAUSE");
    return 0;
}