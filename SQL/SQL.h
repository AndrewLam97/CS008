/*
 * Author: Andrew Lam
 * Project: SQL Class
 * Purpose: SQL Class
 * Notes: Header file.
 */
#ifndef SQL_H
#define SQL_H
#include <iostream>
#include <string>
#include <vector>
#include "_!includes/table/table.h"
#include "_!includes/map/map.h"
#include "_!includes/multimap/multimap.h"
#include "_!includes/binary_file/binary_file.h"
#include "_!includes/binary_file/Record.h"
#include "_!includes/parser/parser.h"
using namespace std;




class SQL{
public:
//CTORS
    //SQL();
//RUN
    void run();
    void run_command();

private:
    vector<string> _table_names;        //stores table names
    Map<string, Table> _table_map;      //redo on initialization      
};

void SQL::run(){
    cout << "--------------" << endl;
    cout << "SQL RUNNING" << endl;
    cout << "--------------" << endl;
    while(true){
        run_command();
    }
    cout << "--------------" << endl;
    cout << "SQL STOPPING" << endl;
    cout << "--------------" << endl;
}

void SQL::run_command(){
    string cmd;
    getline(cin, cmd);
    cout << "COMMAND: " << cmd << endl;
    Parser p(cmd);
    if(p.getCmdVec()[0]=="make" && p.getCmdVec()[1]=="table"){
        string title = p.getCmdVec()[2];
        vector<string>fields;
        //cout << "CMDVEC SIZE: " << p.getCmdVec().size() << endl;
        for(int i=4;i<p.getCmdVec().size();i++){
            fields.push_back(p.getCmdVec()[i]);
        }
        Table temp(title, fields);
        _table_map.insert(title, temp);
        cout << "Created table" << title << " successfully" << endl;
    }
    if(p.getCmdVec()[0]=="insert" && p.getCmdVec()[1]=="into"){
        string title = p.getCmdVec()[2];
        vector<string>fields;
        //cout << "CMDVEC SIZE: " << p.getCmdVec().size() << endl;
        for(int i=4;i<p.getCmdVec().size();i++){
            fields.push_back(p.getCmdVec()[i]);
        }
        _table_map[title].insert(fields);
        cout << "Inserted into: " << title << " successfully" << endl;
        _table_map[title].select_all();
    }
    if(p.getCmdVec()[0]=="select"){
        //cout << "COMMANDVEC: " << p.getCmdVec();
        cout << p.convertToRpn(p.getCmdVec());
    }
}

#endif // SQL_H