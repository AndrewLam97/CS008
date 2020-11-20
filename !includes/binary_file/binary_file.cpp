#include "Record.h"
#include "binary_file.h"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    cout <<endl<<endl<<endl<< "================================" << endl;
    string list[10] = {"zero",
                       "one",
                       "two",
                       "three",
                       "four",
                       "five",
                       "six",
                       "seven",
                       "eight",
                       "nine"};

    for (int i = 0; i< 10; i++){
        cout<<list[i]<<endl;
    }

    fstream f;
    //reset the file:
    open_fileW(f, "record_list.bin");
    for (int i= 0; i<10; i++){
        Record r(list[i]);      //filling the envelop
        long recno = r.write(f);
        cout<<"["<<list[i] <<"]"<< " was written into file as record: "<<recno<<endl;
    }
    f.close();



    Record r;
    //open the file for reading and writing.
    open_fileRW(f, "record_list.bin" );
    r.read(f, 3);       //empty envelop to be filled by the Record object
    cout<<"record 3: "<<r<<endl;    //insertion operator of the Record object
    r.read(f, 6);
    cout<<"record 6: "<<r<<endl;

    //reading passed the end of file:
    long bytes = r.read(f, 19);
    cout<<"number of bytes read: "<<bytes<<endl;

    cout <<endl<<endl<<endl<< "================================" << endl;
    return 0;
}


/*
 *
 *     int recno = 0;
    //get_record returns a vector containing all
    //      the rows of the Record object.
    r.read(f, recno); //first record
    while (!f.eof()){
        cout<<"["<<recno<<"]"<<r.get_record()<<endl;
        recno++;

        r.read(f, recno); //read the next record

 *
 *
 */
