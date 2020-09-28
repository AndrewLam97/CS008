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
    cout << "[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it: ";
    cin >> input;

    while(input != 'x'){
        switch(input){
            case 'r':
            {
                int random = random_num();
                cout << endl << "-- Inserting " << random << endl;
                b.insert(random);
            } 
            break;
        
            case 'i':
            {

            }
            break;

            case 'c':
            {

            }
            break;
            
            case 's':
            {

            }
            break;

            case 'e':
            {

            }
            break;
            case 'x':
            {

            }
            break;
        }
        tree_print(b.getRoot());
        cout << "[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it: ";
        cin >> input;
    }
    
}

int main(){
    test_bst();

    system("PAUSE");
    return 0;
}