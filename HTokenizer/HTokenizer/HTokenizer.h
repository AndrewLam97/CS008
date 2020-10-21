/*
 * Author: Andrew Lam
 * Project: Hash Table Tokenizer
 * Purpose: Lab 3
 * Notes: HTokenizer Header File
 */
#include "../../!includes/heap/heap.h"
#include "../../FTokenizer/FTokenizer/FTokenizer.h"
#include "../../!includes/hash_table/chained_hash_table.h"
#include <string>
#include <iomanip>
#include <map>
#include <iostream>
using namespace std;

class HTokenizer{
public:
    HTokenizer(char *fname);
    void hash_tokenize();
    void make_heap();
    void print_top_bottom();
private:
    MaxHeap<int, string> h;
    map<string, int> m;
    map<string, int>::iterator it;
};

HTokenizer::HTokenizer(char *fname){
    //FTokenizer setftk(fname);
}

void HTokenizer::hash_tokenize(){
    FTokenizer ftk("C:/Users/Andrew/Documents/School/PCC/CS008/HTokenizer/HTokenizer/solitude.txt");
    Token t;
    ftk>>t;
    while(ftk.more()){
        if (t.type_string()=="ALPHA"){
            it = m.find(t.token_str());
            if(it != m.end()){
                m[t.token_str()] = m[t.token_str()]+1;
            }
            else{
                m.insert(pair<string, int> (t.token_str(), 1));
            }
        }
        ftk>>t;
    }
}

void HTokenizer::make_heap(){
    for(it = m.begin(); it != m.end(); it++){
        h.insert(it->second, it->first);
    }
}

void HTokenizer::print_top_bottom(){
    cout << "TOP 100 TOKENS" << endl <<
            setw(3) << setfill(' ') << "#" << ":" <<
            setw(15) << setfill(' ') << "TOKEN" << "  :  " <<
            setw(5) << setfill(' ') << "FREQ" << endl;
    cout << "-----------------------------" << endl;
    for(int i = 1; i <= 100; i++){
        cout << setw(3) << setfill('0') << i << ":" <<
                setw(15) << setfill(' ') << h.getMax() << "  :  " << 
                setw(5) << setfill('0') << h.getMaxKey() << endl;
        h.popMax();
    }

    cout << endl << endl << "BOTTOM 100 TOKENS" << endl <<
                setw(3) << setfill(' ') << "#" << ":" <<
                setw(15) << setfill(' ') << "TOKEN" << "  :  " <<
                setw(5) << setfill(' ') << "FREQ" << endl;
    cout << "-----------------------------" << endl;

    //cout << "SIZE: " << h.getSize() << endl;
    int i = 1;
    while(!h.isEmpty()){ 
        if(h.getSize() <= 100){
            cout << setw(3) << setfill('0') << i++ << ":" <<
                setw(15) << setfill(' ') << h.getMax() << "  :  " << 
                setw(5) << setfill('0') << h.getMaxKey() << endl;
        }
        h.popMax();
    }
}