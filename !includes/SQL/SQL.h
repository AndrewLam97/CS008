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
#include "../table/table.h"
#include "../map/map.h"
#include "../multimap/multimap.h"
#include "../binary_file/binary_file.h"
#include "../binary_file/Record.h"
using namespace std;




class SQL{
public:
//CTORS
    SQL();
//RUN




private:
    vector<string> _table_names;        //stores table names
    Map<string, Table> _table_map;      //redo on initialization      


};


#endif // SQL_H