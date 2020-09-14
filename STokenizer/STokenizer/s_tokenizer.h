/*
 * Author: Andrew Lam
 * Project: String Tokenizer
 * Purpose: String Tokenizer Class
 * Notes: Returns a token via extraction operator from an input buffer according to
 *        rules set in an internal FSM.
 */

#ifndef S_TOKENIZER_H
#define S_TOKENIZER_H

#include "token.h"
//#include "matrix_functions/matrix_functions.h"
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAX_COLUMNS = 150;
const int MAX_ROWS = 50;
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
    friend STokenizer& operator >> (STokenizer& s, Token& t){
        string temp_substr;
        int start_state = 0;
        s.get_token(start_state, temp_substr);
        Token temp(temp_substr,_table[0][int(temp_substr[0])]); //create token with token substring and type
        t = temp;
    }

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
    _pos = 0;
}

void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            _table[i][j] = -1;
        }
    }
    //SUCCESS STATES
    _table[0][0] = 0;
    for(int i = 10; i<50; i+=10){
        _table[i][0] = 1;
    }
    _table[31][0] = 1; //decimal numbers
    //STATE 0
    //---PUNCTUATION---
    _table[0][int('.')] = 10;
    _table[0][int(',')] = 10;
    _table[0][int('?')] = 10;
    _table[0][int('!')] = 10;
    //---ALPHAS---
    for(int i = int('A'); i <= int('Z'); i++){
        _table[0][i] = 20;
    }
    for(int i = int('a'); i <= int('z'); i++){
        _table[0][i] = 20;
    }
    //---NUMBERS---
    for(int i = int('0'); i <= int('9'); i++){
        _table[0][i] = 30;
    }
    //---SPACE---
    _table[0][int(' ')] = 40;
    _table[0][9] = 40;  //tab
    _table[0][13] = 40; //return

    //STATE 10 - PUNCTUATION

    //STATE 20 - ALPHA
    for(int i = int('A'); i <= int('Z'); i++){
        _table[20][i] = 20;
    }
    for(int i = int('a'); i <= int('z'); i++){
        _table[20][i] = 20;
    }
    
    //STATE 30/31 - NUMBERS
    for(int i = int('0'); i <= int('9'); i++){
        _table[30][i] = 30;
    }
    _table[30][int('.')] = 31; //decimal point
    for(int i = int('0'); i <= int('9'); i++){ //decimal numbers
        _table[31][i] = 31;
    }

    //STATE 40 - SPACES
    _table[40][int(' ')] = 40;
    _table[40][9] = 40;  //tab
    _table[40][13] = 40; //return

}
void STokenizer::set_string(char str[]){
    strcpy(_buffer, str);
}

bool STokenizer::get_token(int start_state, string& token){
    int pos_start = _pos; //store starting pos
    int pos_last_success = -1;
    int current_state = start_state; //pass starting state for FTokenizer
    while(_buffer[_pos]!= '\0' && current_state != -1){
        current_state = _table[current_state][int(_buffer[_pos])];
        if(_table[current_state][0] == 1){
            pos_last_success = _pos;
            _pos++;
        }
    }
    for(int i = pos_start; i<=pos_last_success; i++){
        token.push_back(_buffer[i]);
    }
    return !done();
}

bool STokenizer::done(){ //return true if reached end of _buffer
    if(_pos == strlen(_buffer)){
        return true;
    }
    else return false;
}

bool STokenizer::more(){ //return true if more tokens
    if(_pos != strlen(_buffer)){
        return true;
    }
    else return false;
}

//TEST FUNCTIONS ---------------------------------------------------------
void STokenizer::test(){
    string temp;
    int start_state = 0;
    get_token(start_state, temp);
    cout << temp << endl;
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