#include "table.h"
using namespace std;

int main(){
    cout << "Initializaing table with following string and vector: " << endl;
    cout << "\"student\", {\"first\", \"last\", \"major\"}" << endl << endl;
    Table t("student", {"first", "last", "major"});

    cout << "Inserting: " << "{\"Andrew\", \"Lam\", \"CS\"}" << endl;
    t.insert({"Andrew", "Lam", "CS"});
    cout << "Inserting: " << "{\"Bob\", \"Smith\", \"Math\"}" << endl;
    t.insert({"Bob", "Smith", "Math"});
    cout << "Inserting: " << "{\"James\", \"Doe\", \"EE\"}" << endl;
    t.insert({"James", "Doe", "EE"});
    cout << "Inserting: " << "{\"Jane\", \"Appleseed\", \"Physics\"}" << endl;
    t.insert({"Jane", "Appleseed", "Physics"});

    cout << endl << "Dumping table with select_all()..." << endl;
    t.select_all();

    cout << endl << "Dumping table using insertion operator..." << endl;
    cout << t;

    system("PAUSE");
    return 0;
}