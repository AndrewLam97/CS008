/*
 * Author: Andrew Lam
 * Project: Tree Tokenizer
 * Purpose: Lab 2
 * Notes: Main File
 */
#include "TTokenizer.h"
using namespace std;

int main(){
    TTokenizer ttk("C:/Users/Andrew/Documents/School/PCC/CS008/FTokenizer/FTokenizer/solitude.txt");
    ttk.tree_tokenize();
    ttk.make_heap();
    ttk.print_top();
    system("PAUSE");
}