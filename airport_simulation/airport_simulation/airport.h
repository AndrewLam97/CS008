/*
 * Author: Andrew Lam
 * Project: Airport Simulation
 * Purpose: Simulating an airport runway with takeoff and landing queues
 * Notes: Landings prioritized over takeoffs
 */

#ifndef AIRPORT
#define AIRPORT
#include "../../!includes/queue/queue.h"
#include "runway.h"
#include "plane.h"
#include "averager.h"
#include "bool_source.h"
class airport{
public:
    //DEBUG FLAG
    bool const debug = true;

    airport(unsigned int takeoff_time, double takeoff_probability, unsigned int landing_time, 
        double landing_probability, unsigned int fuel_limit, unsigned int total_time);
    void simulate();
private:
    unsigned int takeoff_time;
    double takeoff_probability;
    unsigned int landing_time;
    double landing_probability;
    unsigned int fuel_limit;
    unsigned int total_time;

    unsigned int current_time = 1;
};

airport::airport(unsigned int takeoff_time, double takeoff_probability, unsigned int landing_time, 
double landing_probability, unsigned int fuel_limit, unsigned int total_time){
    this->takeoff_time = takeoff_time;
    this->takeoff_probability = takeoff_probability;
    this->landing_time = landing_time;
    this->landing_probability = landing_probability;
    this->fuel_limit = fuel_limit;
    this->total_time = total_time;
}

void airport::simulate(){
    averager avg;
    queue<plane> landing_queue, takeoff_queue;
    runway runway1(landing_time);
    bool_source landing_source(landing_probability), takeoff_source(takeoff_probability);
    unsigned int next_timestamp;

    //Initial Values
    cout << "____________________________________________________" << endl << "INITIAL VALUES" << endl;
    cout << "Time to takeoff a plane: " << takeoff_time << endl;
    cout << "Probability of plane arrival into takeoff queue: " << takeoff_probability << endl;
    cout << "Time to land a plane: " << landing_time << endl;
    cout << "Probability of plane arrival into landing queue: " << landing_probability << endl;
    cout << "____________________________________________________" << endl;
    if(debug){
        cout << "DEBUG" << endl;
    }
    else{
        cout << "DEBUG OFF" << endl;
    }

    for(current_time = 1; current_time <= total_time; ++current_time){
        if(landing_source.query()){ //Plane arrival for landing
            plane temp_plane(current_time);
            landing_queue.push(temp_plane);
            if(debug) cout << endl << ">>Pushed plane into landing queue with timestamp " << temp_plane.getTimestamp() << endl;
        }
        if(takeoff_source.query()){ //Plane arrival for takeoff
            plane temp_plane(current_time);
            takeoff_queue.push(temp_plane);
            if(debug) cout << endl << ">>Pushed plane into takeoff queue with timestamp " << temp_plane.getTimestamp() << endl;
        }
        //Plane landing
        if((!runway1.is_busy()) && (!landing_queue.empty())){
            runway1.set_time(landing_time);
            next_timestamp = landing_queue.pop().getTimestamp();
            if(next_timestamp + fuel_limit < current_time){ //Current plane ran out of fuel
                if(debug) cout << endl << "Plane crashed :(" << endl;
                avg.add_crash();
                continue;
            }
            avg.add_wait_landing(current_time - next_timestamp);
            if(debug) cout << endl << "<<Popped plane from landing queue with timestamp " << next_timestamp << endl;
            runway1.start();
        }
        //Plane takeoff
        if((!runway1.is_busy()) && (!takeoff_queue.empty())){
            runway1.set_time(takeoff_time);
            next_timestamp = takeoff_queue.pop().getTimestamp();
            avg.add_wait_takeoff(current_time - next_timestamp);
            if(debug) cout << endl << "<<Popped plane from takeoff queue with timestamp " << next_timestamp << endl;
            runway1.start();
        }
        runway1.advance();
    }
    //Find planes in landing queue that have ran out of fuel after simulation time
    while(landing_queue.getSize() != 0){
        next_timestamp = landing_queue.pop().getTimestamp();
        if(next_timestamp + fuel_limit < total_time){
            avg.add_crash();
        }
    }
    //Print results
    avg.print_results(landing_queue.getSize(), takeoff_queue.getSize());
}

#endif // AIRPORT