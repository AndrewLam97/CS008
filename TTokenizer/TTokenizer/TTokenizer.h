/*
 * Author: Andrew Lam
 * Project: Tree Tokenizer
 * Purpose: Lab 2
 * Notes: TTokenizer Header File
 */
#include "../../BST/AVL/avl_tree.h"
#include "../../BST/AVL/avl_array.h"
#include "../../!includes/heap/heap.h"
#include "../../FTokenizer/FTokenizer/FTokenizer.h"
#include <map>
#include <iostream>
using namespace std;

class TTokenizer{
public:
    TTokenizer(char *fname);
    void tree_tokenize();
    void make_heap();
    void print_top();
private:
    avl_array<string, int, std::uint16_t, 2048, true> a;
    MaxHeap<int, string> h;
    map<string, int> m;
    map<string, int>::iterator it;
};

TTokenizer::TTokenizer(char *fname){
    //FTokenizer setftk(fname);
}

void TTokenizer::tree_tokenize(){
    FTokenizer ftk("C:/Users/Andrew/Documents/School/PCC/CS008/FTokenizer/FTokenizer/solitude.txt");
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

void TTokenizer::make_heap(){
    for(it = m.begin(); it != m.end(); it++){
        h.insert(it->second, it->first);
    }
}

void TTokenizer::print_top(){
    for(int i = 1; i <= 100; i++){
        cout << i << ": " << h.getMax() << " : " << h.getMaxKey() << endl;
        h.popMax();
    }
    
}