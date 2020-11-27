/*
 * Author: Andrew Lam
 * Project: Parser Class
 * Purpose: Parser Class
 * Notes: Header File
 */
#ifndef PARSER_H
#define PARSER_H
#include <queue>
#include "../map/map.h"
#include "../multimap/multimap.h"
#include "../table/table.h"
#include "../../STokenizer/STokenizer/s_tokenizer.h"
using namespace std;

const bool DEBUG =  false;

class Parser{
public:
    Parser(string s){
        _cmd = s;
        generateLookup();
        generateAdjacency(_cmdAdjacency);
        generateCmdVec();
        generateCmdMap();
    }

    void set_string(string s);
    MMap<string, string> getCmdMap();


private:
    MMap<string, string> _cmdMap;
    void generateCmdMap();

    Map<string, int> _adjacencyLookup; //SQL COMMANDS
    void generateLookup();             //3 for now: SELECT, INSERT, REMOVE

    static const int MAX_ROWS = 10;
    static const int MAX_COLS = 10;
    int _cmdAdjacency[MAX_ROWS][MAX_COLS];    
    void generateAdjacency(int _cmdAdjacency[][MAX_COLS]);

    string _cmd;
    vector<string> _cmdVec;
    queue<string> _cmdQueue;
    void generateCmdVec();
};

void Parser::set_string(string s){
    _cmd = s;
    generateLookup();
    generateCmdVec();
    generateCmdMap();
}

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

void Parser::generateCmdVec(){
    if(DEBUG) cout << "Generating cmd vec..." << endl;
    _cmdVec.clear();
    char cmdbuf[_cmd.length()+1];
    strcpy(cmdbuf, _cmd.c_str());
    STokenizer stk(cmdbuf);
    Token t;
    stk>>t;
    if(t.type_string()=="ALPHA"){
        _cmdVec.push_back(t.token_str());
        _cmdQueue.push(t.token_str());
        if(DEBUG) cout << "Token: " << t.token_str();        
    }
    while(stk.more()){
        t = Token();
        stk>>t;
        if(t.type_string()=="ALPHA"){
            _cmdVec.push_back(t.token_str());
            _cmdQueue.push(t.token_str());
            if(DEBUG) cout << "Token: " << t.token_str();
        }
        
    }
}

//ONLY WORKS WITH CURRENT COMMAND CONFIG
//UPDATE WITH WORKING ADJACENCY MATRIX AND POSTFIX
void Parser::generateCmdMap(){
    MMap<string, string> temp;
    _cmdMap = temp;
    if(DEBUG) cout << "Generating _cmdMap" << endl;
    _cmdMap.insert("TABLE", _cmdVec[3]);         //table name
    _cmdMap.insert("FIELDS", _cmdVec[1]);        //field to lookup
    _cmdMap.insert("COMMAND", _cmdVec[0]);       //command to use
    _cmdMap.insert("DESTINATION", _cmdVec[2]);   //from is implied?
}

MMap<string, string> Parser::getCmdMap(){
    return _cmdMap;
}

#endif // PARSER_H