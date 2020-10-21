/*
 * Author: Andrew Lam
 * Project: Hash Table Tokenizer
 * Purpose: Lab 3
 * Notes: Main File
 */
#include "HTokenizer.h"
using namespace std;

int main(){
    HTokenizer htk("C:/Users/Andrew/Documents/School/PCC/CS008/HTokenizer/HTokenizer/solitude.txt");
    htk.hash_tokenize();
    htk.make_heap();
    htk.print_top_bottom();
    system("PAUSE");
}