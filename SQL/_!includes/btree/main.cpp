#include <iostream>
#include <random>
#include <time.h>
#include <cassert>
#include "btree.h"
using namespace std;


void test_BTree_auto(int tree_size=5000, int how_many=500, bool report=false);
bool test_BTree_auto(int how_many, bool report=true);

int Random(int lo, int hi)
{
    int r = rand()%(hi-lo+1)+lo;

    return r;
}


int main(int argc, char *argv[])
{
    cout <<endl<<endl<<endl<< "===============================" << endl<<endl<<endl<<endl;

    //------------------------------------------
    srand(time(0));
    //------------------------------------------



//    test_BTree_insert_random();
//    test_BTree_remove();
//    test_BTree_interactive();
//    test_BTree_big_three();
    test_BTree_auto(1000,100,false);

//    test_map();
//    test_map_interactive();

//    test_multimap();
//    test_multimap_interactive();
//    test_multimap_auto();

//    test_iterator();
    cout <<endl<<endl<<endl<< "===============================" << endl;
    return 0;
}
void test_iterator(){
    const bool debug = false;
    BTree<int> bt;
    for (int i= 0; i<125; i++)
        bt.insert(Random(0,100));   cout<<bt<<endl;


    cout<<"------------------------------------------------------------"<<endl;
    for(BTree<int>::Iterator it = bt.begin();
                                    it!= bt.end(); ++it){
        if (debug) it.print_Iterator();
        cout<<"["<<*it<<"] ";
        if (debug) cout<<endl;
    }
    cout<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"test ++ operator: "<<endl;
    BTree<int>::Iterator it = bt.begin();
    cout<<"{"<<*(it++)<<"}"<<endl;
    cout<<"{"<<*it<<"}"<<endl;
    for (int i = 60; i<75; i++){
        it = bt.find(i);
        if (!it.is_null())
            cout<<*it<<" was found."<<endl;
        else
            cout<<i<<" was not found"<<endl;
        }
    cout<<"===================================================================="<<endl;

}

void test_BTree_auto(int tree_size, int how_many, bool report){
    bool verified = true;
    for (int i = 0; i< how_many; i++){
        if (report){
            cout<<"*********************************************************"<<endl;
            cout<<" T E S T:    "<<i<<endl;
            cout<<"*********************************************************"<<endl;
        }
        if (!test_BTree_auto(tree_size, report)){
            cout<<"T E S T :   ["<<i<<"]    F A I L E D ! ! !"<<endl;
            verified = false;
            return;
        }

    }
    cout<<"**************************************************************************"<<endl;
    cout<<"**************************************************************************"<<endl;
    cout<<"             E N D     T E S T: "<<how_many<<" tests of "<<tree_size<<" items: ";
    cout<<(verified?"VERIFIED": "VERIFICATION FAILED")<<endl;
    cout<<"**************************************************************************"<<endl;
    cout<<"**************************************************************************"<<endl;

}

bool test_BTree_auto(int how_many, bool report){
    const int MAX = 10000;
    assert(how_many < MAX);
    BTree<int> bt;
    int a[MAX];
    int original[MAX];
    int deleted_list[MAX];

    int original_size;
    int size;
    int deleted_size = 0;

    //fill a[ ]
    for (int i= 0; i< how_many; i++){
        a[i] = i;
    }
    //shuffle a[ ]: Put this in a function!
    for (int i = 0; i< how_many; i++){
        int from = Random(0, how_many-1);
        int to = Random(0, how_many -1);
        int temp = a[to];
        a[to] = a[from];
        a [from] = temp;
    }
    //copy  a[ ] -> original[ ]:
    copy_array(original, a, how_many);
    size = how_many;
    original_size = how_many;
    for (int i=0; i<size; i++){
        bt.insert(a[i]);

    }
    if (report){
        cout<<"========================================================"<<endl;
        cout<<"  "<<endl;
        cout<<"========================================================"<<endl;
        cout<<bt<<endl<<endl;
    }
    for (int i= 0; i<how_many; i++){
        int r = Random(0, how_many - i - 1);
        if (report){
            cout<<"========================================================"<<endl;
            cout<<bt<<endl;
            cout<<". . . . . . . . . . . . . . . . . . . . . . . . . . . . "<<endl;
            cout<<"deleted: "; print_array(deleted_list, deleted_size);
            cout<<"   from: "; print_array(original, original_size);
            cout<<endl;
            cout<<"  REMOVING ["<<a[r]<<"]"<<endl;
            cout<<"========================================================"<<endl;
        }
        bt.remove(a[r]);


        delete_item(a, r, size, deleted_list[deleted_size++]);
        if (!bt.is_valid()){
            cout<<setw(6)<<i<<" I N V A L I D   T R E E"<<endl;
            cout<<"Original Array: "; print_array(original, original_size);
            cout<<"Deleted Items : "; print_array(deleted_list, deleted_size);
            cout<<endl<<endl<<bt<<endl<<endl;
            return false;
        }

    }
    if (report) cout<<" V A L I D    T R E E"<<endl;

    return true;
}