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
    SQL(){

    }
    SQL(string s);
//RUN
    void run();
    void run_command(string cmd);

private:
    void RPNhandler(string title, vector<string> rpnVec);

    vector<string> _table_names;        //stores table names
    Map<string, Table> _table_map;      //redo on initialization      
};

void SQL::run(){
    cout << "--------------" << endl;
    cout << "MANUAL SQL RUNNING" << endl;
    cout << "--------------" << endl;
    string cmd;
    getline(cin, cmd);
    cout << "COMMAND: " << cmd << endl;
    while(cmd!="exit"){
        run_command(cmd);
        getline(cin, cmd);
        cout << "COMMAND: " << cmd << endl;
    }
    cout << "--------------" << endl;
    cout << "MANUAL SQL STOPPING" << endl;
    cout << "--------------" << endl;
}

void SQL::run_command(string cmd){
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
        cout << "Created table: " << title << " successfully" << endl;
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
        if(p.getCmdVec()[1]=="*"){
            string title = p.getCmdVec()[3];
            if(p.getCmdVec().size()==4){
                _table_map[title].select_all();
            }
            else{  //has where
                vector<string> rpnVec = p.convertToRpn(p.getCmdVec());
                cout << "RPN VEC: " << rpnVec << endl;
                RPNhandler(title, rpnVec);
            }
        }
        else{
            vector<string> simp = p.convertSimple(p.getCmdVec()); //basic select
            string title = simp.back();
            simp.pop_back();
            _table_map[title].select(simp);
        }        
    }
}

void SQL::RPNhandler(string title, vector<string> rpnVec){
    if(rpnVec.size()==3){
        Table temp = _table_map[title].select_where(rpnVec);
        temp.select_all();
    }
    else{
        Table temp("select_where", _table_map[title].get_fieldvec());
        stack<vector<long> >s;
        vector<string> working_str;    //is postfix
        for(int i = 0; i < rpnVec.size(); i++){
            if(rpnVec[i]=="and"){
                vector<long> res;
                vector<long> t1 = s.top();
                sort(t1.begin(), t1.end());
                s.pop();
                vector<long> t2 = s.top();
                sort(t2.begin(), t2.end());
                s.pop();
                cout << "AND t1: " << t1 << endl;
                cout << "AND t2: " << t1 << endl;
                set_intersection(t1.begin(), t1.end(), t2.begin(), t2.end(), t1.begin());
                cout << "AND res: " << t1 << endl;
                s.push(t1);
            }
            if(rpnVec[i]=="or"){
                vector<long> res;
                vector<long> t3 = s.top();
                sort(t3.begin(), t3.end());
                s.pop();
                vector<long> t4 = s.top();
                sort(t4.begin(), t4.end());
                s.pop();
                cout << "OR t3: " << t3 << endl;
                cout << "OR t4: " << t4 << endl;
                set_union(t3.begin(), t3.end(), t4.begin(), t4.end(), t3.begin());
                cout << "OR res: " << t4 << endl;
                s.push(t3);
            }
            else{
                working_str.push_back(rpnVec[i]);
                if(working_str.size()==3){
                    cout << "Working str: " << working_str << endl;
                    cout << "Pushing to stack: " << _table_map[title].select_where_recnos(working_str);
                    s.push(_table_map[title].select_where_recnos(working_str));
                    working_str.clear();
                }
            }
        }
        vector<long> ret = s.top();
        for(auto i:ret){
            vector<string> tem = _table_map[title].get_rec(i);
            //temp.insert(tem);
            cout << i << " ";
        }
        //temp.select_all();
    }
}

#endif // SQL_H