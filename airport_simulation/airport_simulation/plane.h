/*
 * Author: Andrew Lam
 * Project: Airport Simulation
 * Purpose: 
 * Notes: 
 */

#ifndef PLANE
#define PLANE

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

plane::plane(unsigned int timestamp){
    this->timestamp = timestamp;
}

unsigned int plane::getTimestamp(){
    return timestamp;
}

void plane::setCrash(bool status){
    crashed = status;
}

#endif // PLANE