/*
 * Author: Andrew Lam
 * Project: String Tokenizer
 * Purpose: Token Class
 * Notes: 
 */

#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <iomanip>
using namespace std;

class Token
{
public:
    Token();
    Token(string str, int type);
    friend ostream &operator<<(ostream &outs, const Token &t)
    {
        outs << setw(10) << t._typeStr << setw(10) <<"|" << t._tokenStr << "|";
        return outs;
    }
    int type();
    string token_str();   //returns _token
    string type_string(); //converts _type to _typeStr
private:
    string _token;
    int _type;
    string _typeStr;
    string _tokenStr;
};

Token::Token(){
    this->_token = "";
    this->_type = -1;
    this->_tokenStr = "NULL";
    this->_typeStr = "NULL";
}

Token::Token(string str, int type)
{
    this->_token = str;
    this->_type = type;
    this->_tokenStr = token_str();
    this->_typeStr = type_string();
}
string Token::token_str()
{
    return _token;
}
string Token::type_string()
{
    switch (_type)
    {
    case -1:
        return string("UNKNOWN");
    case 10:
        return string("PUNCTUATION");
    case 20:
        return string("ALPHA");
    case 30:
        return string("NUMBER");
    case 40:
        return string("SPACE");
    }
}

#endif // TOKEN_H