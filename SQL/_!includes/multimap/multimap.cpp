#include "multimap.h"
#include <string>
#include <iostream>
using namespace std;

int main(){
    MMap<string, long> mm;

    //vector<string> vec1 = {"1234", "123", "12", "1"};
    //vector<string> vec2 = {"asdf"};
    //vector<string> vec3 = {"1279213471023", "99999999999"};

    MPair<string, long> mpair1{"One", 1};
    MPair<string, long> mpair2{"Two", 2};
    MPair<string, long> mpair3{"Three", 3};
    MPair<string, long> mpair4{"Three", 4};

    //cout << "Inserting: " << "\"One\", \"1234\", \"123\", \"12\", \"1\"" << endl;
    mm.insert(mpair1);
    //cout << "Inserting: " << "\"Two\", \"asdf\""<< endl;
    mm.insert(mpair2);
    //cout << "Inserting: " << "\"Three\", \"1279213471023\", \"99999999999\"" << endl;
    mm.insert(mpair3);

    cout << "Size: " << mm.size() << endl;
    cout << endl << "Printing table..." << endl; 

    //cout << mm["Zero"];
    cout << mm["One"];
    cout << mm["Two"];
    cout << mm["Three"];
    mm.insert(mpair4);
    cout << mm["Three"];

    cout << "Erasing key \"Two\"..."<< endl;
    mm.erase("Two");
    cout << "Size: " << mm.size() << endl;



    system("PAUSE");
    return 0;
}