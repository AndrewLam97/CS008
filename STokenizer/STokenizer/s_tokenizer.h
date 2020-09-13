/*
 * Author: Andrew Lam
 * Project: String Tokenizer
 * Purpose: String Tokenizer Class
 * Notes: 
 */

#ifndef S_TOKENIZER_H
#define S_TOKENIZER_H

#include "token.h"
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAX_COLUMNS = 150;
const int MAX_ROWS = 40;
//const int MAX_COLUMNS = 10; TEST
//const int MAX_ROWS = 5; TEST
const int MAX_BUFFER = 2000;

class STokenizer
{
public:
    STokenizer();
    STokenizer(char str[]);
    bool done();            //true: there are no more tokens
    bool more();            //true: there are more tokens
    //

    //---------------
    //extract one token (very similar to the way cin >> works)
    friend STokenizer& operator >> (STokenizer& s, Token& t);

    //set a new string as the input string
    void set_string(char str[]);

    void test();
    void printTable();
private:
    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)
    void make_table(int _table[][MAX_COLUMNS]);

    //extract the longest string that match
    //     one of the acceptable token types
    //return true until
    bool get_token(int start_state, string& token);
    //---------------------------------
    char _buffer[MAX_BUFFER];       //input string
    int _pos;                       //current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];
};
int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer(char str[]){
    make_table(_table);
    set_string(str);
}

void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            _table[i][j] = -1;
        }
    }
}
void STokenizer::set_string(char str[]){
    strcpy(_buffer, str);
}

bool STokenizer::get_token(int start_state, string& token){

}

//--------------------------------------------------------------------------
void STokenizer::test(){
    cout << _table[0][0] << endl;
}

void STokenizer::printTable(){
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            cout << "" << _table[i][j] << " ";
        }
        cout << endl;
    }
}



#endif // S_TOKENIZER_H