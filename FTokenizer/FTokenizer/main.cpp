/*
 * Author: Andrew Lam
 * Project: FTokenizer
 * Purpose: Returns a token via extraction operator from an input file
 * Notes: main source file
 */
#include "FTokenizer.h"
#include <cstring>
#include <iostream>
using namespace std;

//test fnc
void test_f_tokenize_simple(){
    Token t;
    FTokenizer ftk("C:/Users/Andrew/Documents/School/PCC/CS008/FTokenizer/FTokenizer/solitude.txt");
    ftk>>t;
    int token_count = 0;
    while (ftk.more()){
        if (t.type_string()=="ALPHA" ){
            token_count++;
            cout<<setw(10)<<token_count
                <<setw(3)<<left<<":"<<setw(25)<<left<<t.token_str()
                <<t.type_string()<<endl;
        }
        ftk>>t;
    }
    cout<<"Tokens Found: "<<token_count<<endl;
    cout<<"=========="<<endl;
    system("pause");
}

int main(){
    //FTokenizer ftk("C:/Users/Andrew/Documents/School/PCC/CS008/FTokenizer/FTokenizer/test.txt");
    FTokenizer ftk("C:/Users/Andrew/Documents/School/PCC/CS008/FTokenizer/FTokenizer/solitude.txt");
    Token t;
    ftk>>t;
    int token_count = 0;
    while (ftk.more()){
        if (t.type_string()=="ALPHA" ){
            token_count++;
            //cout<<setw(10)<<token_count
            //    <<setw(3)<<left<<":"<<setw(25)<<left<<t.token_str()
            //    <<t.type_string()<<endl;
        }
        ftk>>t;
        //cout<<"Tokens Found: "<<token_count<<endl;
    }
    cout<<"Tokens Found: "<<token_count<<endl;
    cout<<"=========="<<endl;
    system("pause");

    return 0;
}