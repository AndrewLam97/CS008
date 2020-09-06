/*
 * Author: Andrew Lam
 * Project: String Tokenizer
 * Purpose: Token Class
 * Notes: 
 */

#ifndef TOKEN
#define TOKEN

class Token
{
public:
    Token();
    Token(string str, int type);
    friend ostream& operator <<(ostream& outs, const Token& t);
    int type();
    string type_string();
    string token_str();
private:
    string _token;
    int _type;
};

#endif // TOKEN