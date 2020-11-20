#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <fstream>
using namespace std;
class Record{
public:
    //when you construct a Record, it's either empty or it
    //  contains a word
    Record(){
        _record[0] = NULL;
        recno = -1;
    }

    Record(char str[]){
        strncpy(_record, str, MAX);
    }
    Record(string s){
        strncpy(_record, s.c_str(), MAX);
    }
    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file


    friend ostream& operator<<(ostream& outs,
                               const Record& r);
private:
    static const int MAX = 10;
    int recno;
    char _record[MAX+1];
};

long Record::write(fstream &outs){

    //write to the end of the file.
    outs.seekg(0, outs.end);


    long pos = outs.tellp();    //retrieves the current position of the
                                //      file pointer

    //outs.write(&record[0], sizeof(record));
    outs.write(_record, sizeof(_record));

    return pos/sizeof(_record);  //record number
}

long Record::read(fstream &ins, long recno){
    long pos= recno * sizeof(_record);
    ins.seekg(pos, ios_base::beg);


    ins.read(_record, sizeof(_record));
    //don't you want to mark the end of  the cstring with null?
    //_record[] => [zero'\0'trash trash trash trash]
    //don't need the null character, but for those of us with OCD and PTSD:
    _record[ins.gcount()] = '\0';
    return ins.gcount();

}

ostream& operator<<(ostream& outs,
                    const Record& r){
    outs<<r._record;
    return outs;
}


#endif // RECORD_H