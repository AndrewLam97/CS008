#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include "../binary_file/binary_file.h"
#include "../binary_file/Record.h"
using namespace std;

class Table{
public:
    typedef vector<vector<string>> tablebase;
//CTOR
    Table(){
        _title = "EMPTY";
        _size = 0;
    }


    Table(string title, const vector<string>& vecFields);
//MODIFY
    void insert(const vector<string>& insert_me);
//ACCESS
    Table select(vector<string>fields);
    Table select_where(vector<string>whereStr);
    vector<long> select_where_recnos(vector<string>whereStr);
    void select_all();
    void select_field(string field);

    friend ostream& operator<<(ostream& outs, Table& t);

    vector<string>get_fieldvec();

    int get_numberRecs(){
        _size = _table.size();
        return _size-1;
    }

    int fieldToFieldInt(string s);

private:
    string _title;
    int _size = _table.size();
    vector<string> _fieldnames;
    vector<multimap<string, long> >_indices;
    tablebase _table;
};

// template <typename T> 
// ostream& operator<<(ostream& outs, const vector<T>& vec) { 
//     outs << "[ "; 
//     for (int i = 0; i < vec.size(); ++i) { 
//         outs << vec[i] << " "; 
//     } 
//     outs << "]" << endl; 
//     return outs; 
// } 

ostream& operator << (ostream& outs, Table& t){
    cout << "TABLE: " << t._title << endl;
    t.select_all();
}

Table::Table(string title, const vector<string>& vecFields){
    _title = title;
    _size = 0;
    _fieldnames = vecFields;
    _table.push_back(vecFields);
    for(int i=0;i<vecFields.size();i++){
        multimap<string, long> temp;
        _indices.push_back(temp);
    }
}

void Table::insert(const vector<string>& insert_me){
    _table.push_back(insert_me);
    // fstream f;
    // //reset the file:
    // open_fileW(f, _title.c_str());
    // Record r(insert_me);      //filling the envelope
    // long recno = r.write(f);
    // cout<<"["<<insert_me <<"]"<< " was written into file as record: "<<recno<<endl;
    // f.close();

    for(int i=0;i<insert_me.size();i++){
        //cout << "Indices--emplacing: " << insert_me[i] << " : " << get_numberRecs() << endl;
        _indices[i].emplace(insert_me[i],get_numberRecs());
    }
    //cout << "Table size: " << get_numberRecs() << endl;
    //_size++;
}

void Table::select_all(){
    bool printTop = true;
    cout << "Table name: " << _title << ", Records: " << get_numberRecs() << endl;
    for(int i = 0; i < _table.size(); i++){
        if(i==0 && printTop){
            cout << right << setw(12) << "record";
            printTop = false;
        }
        else{cout << right << setw(12) << i-1;}
        for(int j = 0; j < _table[0].size(); j++){
            cout << right << setw(12) << _table[i][j] << " ";
        }
        if(i == 0){cout << endl << "---------------------------------------------------------";}
        cout << endl;
    }
}


//Single condition
void Table::select_field(string field){
    int fieldIndex = -1;
    vector<string>fieldvec;
    for(int i = 0; i < _table[0].size(); i++){
        if (field == _table[0][i]){
            fieldIndex = i;
        }
    }
    //cout << "Selecting Table with Field: " << field << endl;
    for(int i = 1; i < _table.size(); i++){
        cout << "Rec#" << i << "  :  " << _table[i][fieldIndex] << endl;
    }
}

//multiple conditions, create temp table with only desired fields
//
Table Table::select(vector<string> fields){
    Table temp ("basic_select",fields);
    vector<int> reqFieldsIndices;
    vector<string> insertVec;
    //generate required table field indices
    for(int i = 0; i<fields.size();i++){
        for(int j = 0; j < _table[0].size(); j++){
            if (fields[i] == _table[0][j]){
                reqFieldsIndices.push_back(j);
            }   
        }
    }
    //cout << "TEMP TABLE: "<< endl << temp << endl;

    for(int i=1;i<_table.size();i++){
        for(int j=0; j<reqFieldsIndices.size();j++){
            insertVec.push_back(_table[i][reqFieldsIndices[j]]);
            cout << "Adding " << _table[i][reqFieldsIndices[j]] << " to insertVec" << endl;
        }
        temp.insert(insertVec);
        insertVec.clear();
    }

    //temp.select_all();
    //cout << "TEMP TABLE: "<< endl << temp << endl;
    //cout << "Done printing table";
    return temp;
}

int Table::fieldToFieldInt(string s){
    for(int i=0;i<_fieldnames.size();i++){
        if(s == _fieldnames[i]) return i;
    }
    cout << "fieldToFieldInt: Invalid Field String provided" << endl;
    return -1;
}

//should be composed of 3 strings, field, key, cmd in postfix order
//returns recnos of matching entries
vector<long> Table::select_where_recnos(vector<string>whereStr){
    vector<long> vecIndices;
    string fieldStr = whereStr[0];
    int fieldIndex = fieldToFieldInt(fieldStr);
    string key = whereStr[1];
    string cmd = whereStr[2];

    if(cmd == "=="){
        auto ret = _indices[fieldIndex].equal_range(key);
        for(auto it=ret.first;it!=ret.second;++it){
            //cout << "vecIndices--PushBack: " << it->second << endl;
            vecIndices.push_back(it->second);
        }
    }

    if(cmd == ">"){
        auto ret = _indices[fieldIndex].upper_bound(key);
        for(auto it=ret;it!=_indices[fieldIndex].end();++it){
            //cout << "vecIndices--PushBack: " << it->second << endl;
            vecIndices.push_back(it->second);
        }
    }
    if(cmd == ">="){
        auto ret = _indices[fieldIndex].lower_bound(key);
        for(auto it=ret;it!=_indices[fieldIndex].end();++it){
            //cout << "vecIndices--PushBack: " << it->second << endl;
            vecIndices.push_back(it->second);
        }
    }
    if(cmd== "<"){
        auto ret = _indices[fieldIndex].lower_bound(key);
        for(auto it=_indices[fieldIndex].begin();it!=ret;++it){
            //cout << "vecIndices--PushBack: " << it->second << endl;
            vecIndices.push_back(it->second);
        }
    }
    if(cmd== "<="){
        auto ret = _indices[fieldIndex].upper_bound(key);
        for(auto it=_indices[fieldIndex].begin();it!=ret;++it){
            //cout << "vecIndices--PushBack: " << it->second << endl;
            vecIndices.push_back(it->second);
        }
    }
    return vecIndices;
}

//should be composed of 3 strings, field, key, cmd in postfix order
Table Table::select_where(vector<string>whereStr){
    vector<long> vecIndices = select_where_recnos(whereStr);
    Table select_where_table("select_where",_fieldnames);
    for(auto i:vecIndices){
        select_where_table.insert(_table[i]);
    }
    return select_where_table;
}

vector<string> Table::get_fieldvec(){
    return _table[0];
}

#endif // TABLE_H