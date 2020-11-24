#include "map.h"
#include <string>
#include <iostream>

int main(){
    Map<string, string> m;

    cout << "Inserting: " << "\"One\", \"potato\"" << endl;
    Pair<string, string> tempPair{"One", "potato"};
    m.insert(tempPair.key, tempPair.value);
    cout << "Inserting: " << "\"Two\", \"apple\"" << endl;
    Pair<string, string> tempPair2{"Two", "apple"};
    m.insert(tempPair2.key, tempPair2.value);
    cout << "Inserting: " << "\"Three\", \"banana\"" << endl;
    Pair<string, string> tempPair3{"Three", "banana"};
    m.insert(tempPair3.key, tempPair3.value);
    cout << "Inserting: " << "\"Four\", \"orange\"" << endl;
    Pair<string, string> tempPair4{"Four", "orange"};
    m.insert(tempPair4.key, tempPair4.value);

    cout << "Map Size: " << m.size() << endl;
    
    cout << "Removing key 1..." << endl;
    m.erase("One");

    cout << "Map Size: " << m.size() << endl;

    cout << "Printing 2" << endl;
    cout << m["Two"] << endl;


    system("PAUSE");
    return 0;
}
