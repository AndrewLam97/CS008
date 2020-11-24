#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#include "../binary_file/binary_file.h"
#include "../binary_file/Record.h"

class Table{
public:
//CTOR
    Table();
    Table(string title, const vector<string>& vecFields);
//MODIFY
    void insert(const vector<string>& insert_me);
//ACCESS
    void select_all();

    friend ostream& operator<<(ostream& outs, Table& t);

private:
    string _title;
    vector<vector<string>> _table;
};

template <typename T> 
ostream& operator<<(ostream& outs, const vector<T>& vec) { 
    outs << "[ "; 
    for (int i = 0; i < vec.size(); ++i) { 
        outs << vec[i] << " "; 
    } 
    outs << "]" << endl; 
    return outs; 
} 

ostream& operator << (ostream& outs, Table& t){
    cout << "TABLE: " << t._title << endl;
    t.select_all();
}

Table::Table(string title, const vector<string>& vecFields){
    _title = title; 
    _table.push_back(vecFields);
}

void Table::insert(const vector<string>& insert_me){
    _table.push_back(insert_me);
}

void Table::select_all(){
    for(int i = 0; i < _table.size(); i++){
        for(int j = 0; j < _table[0].size(); j++){
            cout << _table[i][j] << " ";
        }
        cout << endl;
    }
}

#endif // TABLE_H