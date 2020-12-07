#include "multimap.h"
#include <string>
#include <iostream>
using namespace std;

int main(){
    MMap<string, string> mm;

    vector<string> vec1 = {"1234", "123", "12", "1"};
    vector<string> vec2 = {"asdf"};
    vector<string> vec3 = {"1279213471023", "99999999999"};

    MPair<string, string> mpair1{"One", vec1};
    MPair<string, string> mpair2{"Two", vec2};
    MPair<string, string> mpair3{"Three", vec3};

    cout << "Inserting" << "\"Zero\", \"0000\" " << endl;
    mm.insert("Zero", "0000");

    cout << "Inserting: " << "\"One\", \"1234\", \"123\", \"12\", \"1\"" << endl;
    mm.insert(mpair1);
    cout << "Inserting: " << "\"Two\", \"asdf\""<< endl;
    mm.insert(mpair2);
    cout << "Inserting: " << "\"Three\", \"1279213471023\", \"99999999999\"" << endl;
    mm.insert(mpair3);

    cout << "Size: " << mm.size() << endl;
    cout << endl << "Printing table..." << endl; 

    cout << mm["Zero"];
    cout << mm["One"];
    cout << mm["Two"];
    cout << mm["Three"];

    cout << "Erasing key \"Three\"..."<< endl;
    mm.erase("Three");
    cout << "Size: " << mm.size() << endl;

    // j

    system("PAUSE");
    return 0;
}