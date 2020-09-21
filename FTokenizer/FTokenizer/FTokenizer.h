#ifndef F_TOKENIZER_H
#define F_TOKENIZER_H
#include <fstream>
#include <string>
#include "../../STokenizer/STokenizer/s_tokenizer.h"

const int MAX_BLOCK = 2000;
bool debug = true;

class FTokenizer
{
public:
    //const int MAX_BLOCK = MAX_BUFFER;
    FTokenizer(char *fname);
    Token next_token();
    bool more();     //returns the current value of _more
    int pos();       //returns the value of _pos
    int block_pos(); //returns the value of _blockPos
    friend FTokenizer &operator >> (FTokenizer &f, Token &t)
    {
        t = f.next_token();
    }

    void test();

private:
    bool get_new_block(); //gets the new block from the file
    std::ifstream _f;     //file being tokenized
    STokenizer _stk;      //The STokenizer object to tokenize current block
    char block_buf[MAX_BLOCK+1];
    int _pos;      //Current position in the file
    int _blockPos; //Current position in the current block
    bool _more;    //false if last token of the last block
                   //  has been processed and now we are at
                   //  the end of the last block.
};

FTokenizer::FTokenizer(char *fname)
{
    cout << "Reading: " << fname << endl;
    _f.open(fname);
    if(!_f){
        cout << "Unable to open file...";
    }
    //_pos = 0;
    //_blockPos = 0;
    get_new_block();
}

Token FTokenizer::next_token()
{
    // if(_blockPos > MAX_BLOCK && more()){
    //     get_new_block();
    //     _blockPos = 0;
    // }
    if(!_stk.more()){
        get_new_block();
    }
    Token t;
    _stk >> t; //_stk already has buffer
    //_blockPos += t.token_str().size();
    //if(debug) cout << "Current _blockPos: " << _blockPos << endl;
    return t;
}

bool FTokenizer::get_new_block()
{
    if(debug)cout << "Getting new block" << endl;
    if(!_f.eof()){
        _f.read(block_buf, MAX_BUFFER);
        block_buf[_f.gcount()] = '\0';
    }
    if(debug)cout << "CURRENT_BUFFER: " << block_buf << endl;
    _stk = STokenizer(block_buf);
    //_stk.set_string(block_buf);
}

bool FTokenizer::more()
{
    _more = !_f.eof();
    return _more;
}

#endif // F_TOKENIZER_H