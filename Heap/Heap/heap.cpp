#include "heap.h"
#include <string>
#include <iostream>
using namespace std;

int main(){
    // MaxHeap<int, string> h;
    // h.insert(10,"a");
    // h.insert(15,"b");
    // h.insert(17,"c");
    // h.insert(8,"d");
    // h.insert(10,"e");
    // h.insert(14,"f");
    // h.insert(25,"g");
    MaxHeap<int, int> h;
    h.insert(10,10);
    h.insert(15,15);
    h.insert(17,17);
    h.insert(8,8);
    h.insert(13,13);
    h.insert(14,14);
    h.insert(25,25);

    while(!h.isEmpty()){
        cout << h.getMax() << endl;
        h.popMax();
    }

    system("PAUSE");
    return 0;
}