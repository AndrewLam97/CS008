#include <iostream>
#include "binary_search_tree.h"
using namespace std;

//Driver Function
void test_bst(){
    

    char input;
    cout << "[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it: ";
    cin >> input;

    while(input != 'x'){
        cout << "[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it: ";
        cin >> input;

        switch(input){
            case 'r': //
                break;
            case 'i':
                break;
            case 'c':
                break;
            case 's':
                break;
            case 'e':
                break;
            case 'x':
                break;
        }
    }
    
}

int main(){
    system("PAUSE");
    return 0;
}