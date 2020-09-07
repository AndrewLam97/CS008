/*
 * Author: Andrew Lam
 * Project: Airport Simulation
 * Purpose: 
 * Notes: 
 */

#ifndef BOOL_SOURCE
#define BOOL_SOURCE
#include <cassert>
#include <cstdlib>
#include <time.h>

class bool_source{
public:
    bool_source(double p = 0.5);
    bool query() const;

private:
    double probability;
};

bool_source::bool_source(double p){
    assert(p>=0 && "Probability less than 0");
    assert(p<=1 && "Probability greater than 1");
    srand(time(NULL));
    probability = p;
}

bool bool_source::query() const {
    return (rand() < probability * RAND_MAX);
}

#endif // BOOL_SOURCE