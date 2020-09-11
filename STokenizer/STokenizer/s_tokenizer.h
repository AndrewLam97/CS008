/*
 * Author: Andrew Lam
 * Project: String Tokenizer
 * Purpose: String Tokenizer Class
 * Notes: 
 */

#ifndef S_TOKENIZER_H
#define S_TOKENIZER_H

#include "token.h"
#include "matrix_functions/matrix_functions.h"
#include <string>
#include <iostream>
using namespace std;

const int MAX_COLUMNS = 150;
const int MAX_ROWS = 40;
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
void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    //init_table(_table);
}

bool STokenizer::get_token(int start_state, string& token){

}

void STokenizer::test(){

}

#endif // S_TOKENIZER_H