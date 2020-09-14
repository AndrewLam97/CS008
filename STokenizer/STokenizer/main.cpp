/*
 * Author: Andrew Lam
 * Project: STokenizer
 * Purpose: Returns a token via extraction operator from an input buffer according to
 *          rules set in an internal FSM.
 * Notes: main source file
 */

#include <iostream>
#include "s_tokenizer.h"
using namespace std;

int main()
{
    char buf[] = "it was the night of october 17th. pi was still 3.14.";
    STokenizer stk(buf);
    Token t;
    stk>>t;
    cout << t << endl;
    while(stk.more()){
        t = Token();
        stk>>t;
        cout << t << endl;
    }
    system("pause"); //View Terminal Output
    return 0;
    
}