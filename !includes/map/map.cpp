#include "map.h"
#include <string>
#include <iostream>

int main(){
    Map<int, string> m;

    Pair<int, string> tempPair{1, "asdlkfjsadlfkja"};
    m.insert(tempPair.key, tempPair.value);

    Pair<int, string> tempPair2{2, "kasjdfk"};
    m.insert(tempPair2.key, tempPair2.value);

    Pair<int, string> tempPair3{3, "12313131"};
    m.insert(tempPair3.key, tempPair3.value);

    Pair<int, string> tempPair4{4, "9999999"};
    m.insert(tempPair4.key, tempPair4.value);

    cout << m[2] << endl;

    system("PAUSE");
    return 0;
}
