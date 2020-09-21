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
    char buf[] = "GABRIEL GARCIA MARQUEZ. ONE HUNDRED YEARS OF SOLITUDE (both available in Bard editions). García Márquez currently lives with his wife and children in Barcelona.";
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