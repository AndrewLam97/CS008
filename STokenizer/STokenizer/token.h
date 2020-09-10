/*
 * Author: Andrew Lam
 * Project: String Tokenizer
 * Purpose: Token Class
 * Notes: 
 */

#ifndef TOKEN
#define TOKEN
#include "iostream"
using namespace std;

class Token
{
public:
    Token();
    Token(string str, int type);
    friend ostream& operator <<(ostream& outs, const Token& t){
        outs << t._typeStr << "     |" << t._tokenStr << "|";
        return outs;
    }
    int type();
    string token_str(); //returns _token
    string type_string(); //converts _type to _typeStr
private:
    string _token;
    int _type;
    string _typeStr;
    string _tokenStr;
};

Token::Token(string str, int type){
    this->_token = str;
    this->_type = type;
    this->_tokenStr = token_str();
    this->_typeStr = type_string();
}
string Token::token_str(){
    return _token;
}
string Token::type_string(){
    switch (_type){
        case -1:
            return string("UNKNOWN");
        case 0:
            return string("PUNCTUATION");
        case 1:
            return string("ALPHA");
        case 2:
            return string("NUMBER");
        case 3:
            return string("SPACE");
    }
}



#endif // TOKEN