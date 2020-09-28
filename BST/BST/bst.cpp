#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "binary_search_tree.h"
using namespace std;

//Helper Functions
int random_num(){ //returns random number 1-100
    return (rand() % 100)+1;
}

//Driver Function
void test_bst(){
    srand(time(NULL));
    BST<int> b;

    char input;
    int insert_input;
    int search_input;
    int erase_input;

    std::cout << "[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it: ";
    std::cin >> input;

    while(input != 'x'){
        switch(input){
            case 'r':
            {
                int random = random_num();
                std::cout << endl << "-- Inserting " << random << endl;
                b.insert(random);
            } 
            break;
        
            case 'i':
            {
                std::cout << "?";
                std::cin >> insert_input;
                b.insert(insert_input);
            }
            break;

            case 'c':
            {
                b.~BST();
            }
            break;
            
            case 's':
            {
                std::cout << "?";
                std::cin >> search_input;
                if(b.search(search_input)){
                    std::cout << endl << "Found: " << search_input << endl;
                }
                else std::cout << endl << "Did not find: " << search_input << endl;
            }
            break;

            case 'e':
            {
                std::cout << "?";
                std::cin >> erase_input;
                b.erase(erase_input);
            }
            break;
            case 'x':
            {

            }
            break;
            default:
            break;
        }
        tree_print(b.getRoot());
        std::cout << "[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it: ";
        std::cin >> input;
    }
}

int main(){
    test_bst();

    system("PAUSE");
    return 0;
}