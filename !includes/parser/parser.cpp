/*
 * Author: Andrew Lam
 * Project: Parser Class
 * Purpose: Parser Class
 * Notes: Main file.
 */
#include "parser.h"
using namespace std;

int main(){
    if(DEBUG) cout << "Initializaing table with following string and vector: " << endl;
    if(DEBUG) cout << "\"student\", {\"first\", \"last\", \"major\"}" << endl;
    Table t("student", {"first", "last", "major"});
    if(DEBUG) cout << "Inserting: " << "{\"Andrew\", \"Lam\", \"CS\"}" << endl;
    t.insert({"Andrew", "Lam", "CS"});
    if(DEBUG) cout << "Inserting: " << "{\"Bob\", \"Smith\", \"Math\"}" << endl;
    t.insert({"Bob", "Smith", "Math"});
    if(DEBUG) cout << "Inserting: " << "{\"James\", \"Doe\", \"EE\"}" << endl;
    t.insert({"James", "Doe", "EE"});
    if(DEBUG) cout << "Inserting: " << "{\"Jane\", \"Appleseed\", \"Physics\"}" << endl;
    t.insert({"Jane", "Appleseed", "Physics"});


    Parser p("SELECT last FROM student"); //verify field is present in table before lookup

    MMap<string, string> ptree = p.getCmdMap(); //string and vector of strings
    if(DEBUG) cout << "TABLE: " << ptree["TABLE"][0] << endl;
    if(DEBUG) cout << "FIELDS: " << ptree["FIELDS"][0] << endl;
    if(DEBUG) cout << "COMMAND: " << ptree["COMMAND"][0] << endl;
    if(DEBUG) cout << "DESTINATION: " << ptree["DESTINATION"][0] << endl;
    if (ptree["COMMAND"][0] == "SELECT"){
        string table_name = ptree["TABLE"][0];  //need to implement current working table in table class
        if(DEBUG) cout << ptree["FIELDS"][0];
        t.select_field(ptree["FIELDS"][0]);
    }

    p.set_string("SELECT first FROM student");
    ptree = p.getCmdMap();
    t.select_field(ptree["FIELDS"][0]);

    cout << endl << endl << "Dumping Entire Table:" << endl;
    cout << t;

    system("PAUSE");
    return 0;
}