/*
 * Author: Andrew Lam
 * Project: Airport Simulation
 * Purpose: 
 * Notes: main source file
 */

#include <iostream>
#include "../../!includes/list_functions/list_functions.h"
#include "../../!includes/queue/queue.h"
#include "airport.h"
#include "bool_source.h"
#include "landing_queue.h"
#include "takeoff_queue.h"
#include "plane.h"
#include "averager.h"
using namespace std;

int main(){
    bool_source test(0.5);
    cout << "\n\n\n\n";
    cout << "Test...";
    cout << test.query();
    cout << test.query();
    cout << test.query();
    cout << test.query();
    cout << test.query();
    cout << test.query();
    cout << test.query();
    cout << test.query();
    cout << test.query();
    cout << endl;

    return 0;
}
