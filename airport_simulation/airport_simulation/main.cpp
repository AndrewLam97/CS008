/*
 * Author: Andrew Lam
 * Project: Airport Simulation
 * Purpose: 
 * Notes: main source file
 */

#include <iostream>
#include "airport.h"
using namespace std;

int main(){
    unsigned int takeoff_time = 15;
    double takeoff_probability = 0.08;
    unsigned int landing_time = 5;
    double landing_probability = 0.1;
    unsigned int fuel_limit = 20;
    unsigned int total_time = 100000;

    airport a(takeoff_time, takeoff_probability, landing_time, landing_probability, fuel_limit, total_time);

    a.simulate();

    return 0;
}
