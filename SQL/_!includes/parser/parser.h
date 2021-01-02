/*
 * Author: Andrew Lam
 * Project: Parser Class
 * Purpose: Parser Class
 * Notes: Header File
 */
#ifndef PARSER_H
#define PARSER_H
#include <algorithm>
#include <queue>
#include <stack>
#include "../map/map.h"
#include "../multimap/multimap.h"
#include "../table/table.h"
#include "../STokenizer/s_tokenizer.h"
using namespace std;

const bool DEBUG =  true;

class Parser{
public:
    //CTOR
    Parser(string s){
        _cmd = s;
        //generateLookup();
        //generateAdjacency(_cmdAdjacency);
        generateCmdVec();
        //generateCmdMap();
    }

    //SETTERS
    void set_string(string s);

    //GETTERS
    MMap<string, vector<string> > getCmdMap();
    //returns tokenized input string
    vector<string> getCmdVec(){
        return _cmdVec;
    }

    //BIG FUNCTIONS
    //CONVERTS COMMAND VECTOR TO RPN VECTOR
    vector<string> convertToRpn(vector<string> cmdVec);
    vector<string> convertSimple(vector<string> cmdVec);

private:
    MMap<string, vector<string> >_cmdMap;
    void generateCmdMap();

    Map<string, int> _adjacencyLookup; //SQL COMMANDS
    void generateLookup();             

    static const int MAX_ROWS = 10;
    static const int MAX_COLS = 10;
    int _cmdAdjacency[MAX_ROWS][MAX_COLS];    
    void generateAdjacency(int _cmdAdjacency[][MAX_COLS]);

    string _cmd;
    vector<string> _cmdVec;
    queue<string> _cmdQueue;
    void generateCmdVec();
};

//CONVERTS CMDVEC TO RPNVEC
vector<string> Parser::convertSimple(vector<string> cmdVec){
    vector<string> ret;
    int i = 1;
    for(i;i<cmdVec.size()&&cmdVec[i]!="from";i++){
        ret.push_back(cmdVec[i]);
    }
    ret.push_back(cmdVec[i+1]);
    //cout << "Returning simp command: " << ret << endl;
    return ret;
}

//HELPER FUNCTIONS
bool is_operator(string s) {if(s=="="||s=="<"||s=="<="||s==">"||s==">=") return true;}
bool is_special(string s) {if(s=="and"||s=="or") return true;}
bool is_open_paren(string s){if(s=="(") return true;}
bool is_closed_paren(string s){if(s==")") return true;}

//returns cmdVec that's RPNd
vector<string> Parser::convertToRpn(vector<string> cmdVec){
    stack<string> s;
    stack<string> s1;
    queue<string> q;
    vector<string> ret;
    //ignore up till where keyword
    int i = 5;
    // while(i<cmdVec.size()){
    //     cout <<  "CURRENT TOKEN: " << cmdVec[i] << endl; 
    //     if(!is_operator(cmdVec[i]) && !is_open_paren(cmdVec[i]) && !is_closed_paren(cmdVec[i])){
    //         cout << "Pushback: " << cmdVec[i] << endl;
    //         ret.push_back(cmdVec[i]);
    //     }
    //     else if(is_operator(cmdVec[i]) || is_open_paren(cmdVec[i]) || is_closed_paren(cmdVec[i])){
    //         if(!is_open_paren(cmdVec[i])){
    //             while(!s.empty() && is_closed_paren(cmdVec[i]) && !is_open_paren(s.top())){
    //                 ret.push_back(s.top());
    //                 cout << "Pushback: " << cmdVec[i] << endl;
    //                 s.pop();
    //             }
    //             if(is_closed_paren(cmdVec[i])){
    //                 s.pop();
    //             }
    //         }
    //         if(!is_closed_paren(cmdVec[i])){
    //             s.push(cmdVec[i]);
    //             cout << "Pushing to stack: " << cmdVec[i] << endl;
    //         }
    //     }
        
    //     i++;
    // }
    // while(!s.empty()){
    //     ret.push_back(s.top());
    //     s.pop();
    // }

    while(i<cmdVec.size()){
        //cout <<  "CURRENT TOKEN: " << cmdVec[i] << endl;
        if(!is_operator(cmdVec[i]) && !is_special(cmdVec[i])){
            //cout << "ret add: " << cmdVec[i] << endl;
            ret.push_back(cmdVec[i]);
        }
        else if(is_operator(cmdVec[i])){
            if(s.size()>0){
                //cout << "ret add: " << s.top() << endl;
                ret.push_back(s.top());
                s.pop();
                s.push(cmdVec[i]);
            }
            s.push(cmdVec[i]);
        }
        else if(is_special(cmdVec[i])){
            if(s.size()>0){
                //cout << "ret add: " << s.top() << endl;
                ret.push_back(s.top());
                s.pop();
            }
            if(s1.size()==0){
                s1.push(cmdVec[i]);
            }
            else{
                //cout << "ret add: " << s1.top() << endl;
                ret.push_back(s1.top());
                s1.pop();
                s1.push(cmdVec[i]);
            }
        }
        i++;
    }
    while(!s.empty()){
        ret.push_back(s.top());
        s.pop();
    }
    while(!s1.empty()){
        ret.push_back(s1.top());
        s1.pop();
    }

    return ret;
}

//sets new parser string
void Parser::set_string(string s){
    _cmd = s;
    generateLookup();
    generateCmdVec();
    //generateCmdMap();
}

//enums basically
void Parser::generateLookup(){
    Map<string, int> temp;
    _adjacencyLookup = temp;
    _adjacencyLookup.insert("SELECT", 1);
    _adjacencyLookup.insert("INSERT", 2);
    _adjacencyLookup.insert("REMOVE", 3);
}

void Parser::generateAdjacency(int _cmdAdjacency[][MAX_COLS]){
    for(int i = 0; i < MAX_ROWS; i++){
        for(int j = 0; j < MAX_COLS; j++){
            _cmdAdjacency[i][j] = 0;
        }
    }
    //SUCCESS STATES
    _cmdAdjacency[0][0] = 0;
    for(int i=1;i<=3;i++){
        _cmdAdjacency[i][0] = 0;
    }
}

//generate command vector from member input string
void Parser::generateCmdVec(){
    //if(DEBUG) cout << "Generating cmd vec..." << endl;
    _cmdVec.clear();
    char cmdbuf[_cmd.length()+1];
    strcpy(cmdbuf, _cmd.c_str());
    STokenizer stk(cmdbuf);
    Token t;
    stk>>t;
    if(t.type_string()=="ALPHA" || t.type_string()=="NUMBER" || t.type_string()=="PUNCTUATION"){
        if(t.token_str() == "\""){
            string temp;
            t=Token();
            stk>>t;
            // while(t.token_str()!="\"" && stk.more() && (t.type_string() =="ALPHA" || t.type_string()=="NUMBER")){
            while(t.token_str()!="\"" && stk.more()){
                temp+=t.token_str();
                t=Token();
                stk>>t;
            }
            Token bigToken(temp, 20);
            //cout << "BIGTOKEN STR: " << bigToken.token_str() << endl;
            _cmdVec.push_back(bigToken.token_str());
        } //Checks for <= or >=
        if(t.token_str() == "<" || t.token_str() == ">"){
            string temp = t.token_str();
            Token t1;
            stk>>t1;
            if(t1.token_str() == "="){
                temp+=t1.token_str();
                t1 = Token(temp, 20);
                _cmdVec.push_back(t1.token_str());
            }
            else if (t1.token_str()==" "){
                _cmdVec.push_back(t.token_str());
            }
            else {
                _cmdVec.push_back(t.token_str());
                _cmdVec.push_back(t1.token_str());
            }
        }
        else if(t.token_str() != "," && t.token_str()!="\""){
            _cmdVec.push_back(t.token_str());
            //_cmdQueue.push(t.token_str());
            //if(DEBUG) cout << "Token: " << t.token_str() << " ";  
        }
    }
    while(stk.more()){
        t = Token();
        stk>>t; 
        if(t.token_str() == "\""){ //Checks for beginning quote
            string temp;
            t=Token();
            stk>>t;
            //while(t.token_str()!="\"" && stk.more() && (t.type_string() =="ALPHA" || t.type_string()=="NUMBER")){
            while(t.token_str()!="\"" && stk.more()){ //end quote
                temp+=t.token_str();
                t=Token();
                stk>>t;
            }
            Token bigToken(temp, 20);
            //cout << "BIGTOKEN STR: " << bigToken.token_str() << endl;
            _cmdVec.push_back(bigToken.token_str());
        } //Checks for <= or >=
        if(t.token_str() == "<" || t.token_str() == ">"){
            string temp = t.token_str();
            Token t1;
            stk>>t1;
            if(t1.token_str() == "="){
                temp+=t1.token_str();
                t1 = Token(temp, 20);
                _cmdVec.push_back(t1.token_str());
            }
            else if (t1.token_str()==" "){
                _cmdVec.push_back(t.token_str());
            }
            else {
                _cmdVec.push_back(t.token_str());
                _cmdVec.push_back(t1.token_str());
            }
        }
        else if(t.type_string()=="ALPHA" || t.type_string()=="NUMBER" || t.type_string()=="PUNCTUATION"){
            if(t.token_str() != "," && t.token_str()!="\"" && (t.token_str()!="<" || t.token_str()!=">")){
                _cmdVec.push_back(t.token_str());
                //_cmdQueue.push(t.token_str());
                //if(DEBUG) cout << "Token: " << t.token_str() << " ";  
            }
        }
        
        
    }
}

// //ONLY WORKS WITH CURRENT COMMAND CONFIG
// //UPDATE WITH WORKING ADJACENCY MATRIX AND POSTFIX
// void Parser::generateCmdMap(){
//     MMap<string, vector<string>> temp;
//     _cmdMap = temp;
//     if(DEBUG) cout << "Generating _cmdMap" << endl;
//     _cmdMap.insert("TABLE", _cmdVec[3]);         //table name
//     _cmdMap.insert("FIELDS", _cmdVec[1]);        //field to lookup
//     _cmdMap.insert("COMMAND", _cmdVec[0]);       //command to use
//     _cmdMap.insert("DESTINATION", _cmdVec[2]);   //from is implied?
// }

// MMap<string, vector<string> > Parser::getCmdMap(){
//     return _cmdMap;
// }

#endif // PARSER_H