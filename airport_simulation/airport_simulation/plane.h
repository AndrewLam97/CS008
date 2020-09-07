/*
 * Author: Andrew Lam
 * Project: Airport Simulation
 * Purpose: Plane class contains enqueue timestamp and crash status
 * Notes: 
 */

#ifndef PLANE_H
#define PLANE_H

class plane{
public:
    plane(unsigned int timestamp = 1);
    unsigned int getTimestamp();
    void setCrash(bool status);
private:
    unsigned int timestamp;
    bool crashed = false;
    unsigned int fuel;
};

//Ctor
plane::plane(unsigned int timestamp){
    this->timestamp = timestamp;
}

unsigned int plane::getTimestamp(){
    return timestamp;
}

void plane::setCrash(bool status){
    crashed = status;
}

#endif // PLANE_H