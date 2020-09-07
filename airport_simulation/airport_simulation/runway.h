/*
 * Author: Andrew Lam
 * Project: Airport Simulation
 * Purpose: Runway class implements an in-use timer and status
 * Notes: Advances one tick at a time, dependent on busy boolean
 */

#ifndef RUNWAY
#define RUNWAY
#include <cassert>
class runway{
public:
    runway(unsigned int time_reserved);
    void start(); //pre: runway != busy
    void advance(); //advance one tick
    bool is_busy() const;
    void set_time(unsigned int newtime);
private:
    unsigned int time_reserved;
    unsigned int time_left;
};

runway::runway(unsigned int time_reserved){
    this->time_reserved = time_reserved;
    time_left = 0;
}

//Start runway "timer"
void runway::start(){
    assert(!is_busy() && "runway already in use");
    time_left = time_reserved;
}

bool runway::is_busy() const {
    return (time_left > 0);
}

//Advance runway "timer" one tick
void runway::advance(){
    if(is_busy()){
        --time_left;
    }
}

//Update runway usage time
void runway::set_time(unsigned int newtime){
    time_reserved = newtime;
}

#endif // RUNWAY