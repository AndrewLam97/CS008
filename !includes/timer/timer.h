/*
    Timer Class Usage:

    timer t;
    t.start();
    f(a, size);
    t.stop();
    return t.duration();
 */
#ifndef TIMER_H
#define TIMER_H

#include <time.h>
using namespace std;
class timer{
private:
    clock_t _start;
    clock_t _stop;
public:
    timer():_start(clock()), _stop(clock()){}
    void start(){
        _start = clock();
    }
    void stop(){
        _stop = clock();
    }
    float duration(){
        return (float(_stop) - float(_start))/CLOCKS_PER_SEC;
    }
};

#endif // TIMER_H