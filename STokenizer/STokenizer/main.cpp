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
    cout << endl;
    char buf[20] = "adfasdfsadfsa";
    STokenizer stk(buf);
    stk.printTable();
    
    
    system("pause"); //View Terminal Output
    return 0;
    
}