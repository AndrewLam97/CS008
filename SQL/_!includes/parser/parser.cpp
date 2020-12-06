/*
 * Author: Andrew Lam
 * Project: Parser Class
 * Purpose: Parser Class
 * Notes: Main file.
 */
#include "parser.h"
using namespace std;


int main(){
    // //if(DEBUG) cout << "Initializaing table with following string and vector: " << endl;
    // //if(DEBUG) cout << "\"student\", {\"first\", \"last\", \"major\"}" << endl;
    // Table t("student", {"first", "last", "major", "salary"});
    // //if(DEBUG) cout << "Inserting: " << "{\"Andrew\", \"Lam\", \"CS\"}" << endl;
    // t.insert({"Andrew", "Lam", "CS", "99"});
    // //if(DEBUG) cout << "Inserting: " << "{\"Bob\", \"Smith\", \"Math\"}" << endl;
    // t.insert({"Bob", "Smith", "Math", "50"});
    // //if(DEBUG) cout << "Inserting: " << "{\"James\", \"Doe\", \"EE\"}" << endl;
    // t.insert({"James", "Doe", "EE", "90"});
    // //if(DEBUG) cout << "Inserting: " << "{\"Jane\", \"Appleseed\", \"Physics\"}" << endl;
    // t.insert({"Jane", "Appleseed", "Physics", "12"});
    // t.insert({"Alex", "Zee", "Math", "42"});



    // Parser p("SELECT salary FROM student"); //verify field is present in table before lookup

    // MMap<string, vector<string> >ptree = p.getCmdMap(); //string and vector of strings
    // if(DEBUG) cout << "TABLE: " << ptree["TABLE"][0] << endl;
    // if(DEBUG) cout << "FIELDS: " << ptree["FIELDS"][0] << endl;
    // if(DEBUG) cout << "COMMAND: " << ptree["COMMAND"][0] << endl;
    // if(DEBUG) cout << "DESTINATION: " << ptree["DESTINATION"][0] << endl;
    // if (ptree["COMMAND"][0] == "SELECT"){
    //     string table_name = ptree["TABLE"][0];  //need to implement current working table in table class
    //     //dif(DEBUG) cout << ptree["FIELDS"][0];
    //     Table tempT(ptree["COMMAND"][0],ptree["FIELDS"]);
    //     tempT = t.select(ptree["FIELDS"]);
    //     tempT.select_all();
    // }

    // // p.set_string("SELECT first FROM student");
    // // ptree = p.getCmdMap();
    // // t.select_field(ptree["FIELDS"][0]);

    // //vector<string> test = {"first", "last", "salary"};
    // //Table tempT = t.select(test);
    // //tempT.select_all();

    // vector<string>testWhereRecnos = {"major", "Math", "=="};
    // vector<long>temp = t.select_where_recnos(testWhereRecnos);
    // // cout << temp << endl;
    // // testWhereRecnos = {"salary", "50", ">"};
    // // temp = t.select_where_recnos(testWhereRecnos);
    // // cout << temp << endl;
    // // testWhereRecnos = {"salary", "50", ">="};
    // // temp = t.select_where_recnos(testWhereRecnos);
    // // cout << temp << endl;
    // // testWhereRecnos = {"salary", "50", "<"};
    // // temp = t.select_where_recnos(testWhereRecnos);
    // // cout << temp << endl;
    // testWhereRecnos = {"salary", "50", "<="};
    // temp = t.select_where_recnos(testWhereRecnos);
    // //cout << temp << endl;

    // Table t1 = t.select_where(testWhereRecnos);
    // t1.select_all();

    // cout << endl << endl
    //      << "---------------------------" << endl
    //      << "Dumping Entire Table:" << endl
    //      << "---------------------------" << endl;
    // cout << t;

    system("PAUSE");
    return 0;
}