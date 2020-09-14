/*
 * Author: Andrew Lam
 * Project: String Tokenizer
 * Purpose: 
 * Notes: main source file
 */

#include <iostream>
#include "s_tokenizer.h"
using namespace std;

int main()
{
    cout << "DEBUG TEST" << endl;
    char buf[] = "it was the night of october 17th. pi was still 3.14.";
    STokenizer stk(buf);
    Token t;
    stk>>t;
    while(stk.more()){
        cout << t << endl;
        t = Token();
        stk>>t;
    }
    //cout << t;
    

    //stk.printTable();
    
    
    system("pause"); //View Terminal Output
    return 0;
    
}