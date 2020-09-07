/*
 * Author: Andrew Lam
 * Project: Airport Simulation
 * Purpose: Output File
 * Notes: Console output; Tests: many iterations w. debug off, example given in Canvas, low iterations w. debug on
 */
#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
____________________________________________________
INITIAL VALUES
Time to takeoff a plane: 15
Probability of plane arrival into takeoff queue: 0.08
Time to land a plane: 5
Probability of plane arrival into landing queue: 0.1
Fuel: 20
Simulation time: 100000
____________________________________________________
DEBUG OFF
____________________________________________________
RESULTS
9929 landed
3349 took off
116 crashed
Average waiting time to land: 8.6756
Average waiting time to takeoff: 28624.5
Planes in landing queue: 0
Planes in takeoff queue: 4696




____________________________________________________
INITIAL VALUES
Time to takeoff a plane: 15
Probability of plane arrival into takeoff queue: 0.08
Time to land a plane: 5
Probability of plane arrival into landing queue: 0.1
Fuel: 20
Simulation time: 1440
____________________________________________________
DEBUG OFF
____________________________________________________
RESULTS
135 landed
50 took off
1 crashed
Average waiting time to land: 8.59259
Average waiting time to takeoff: 422.42
Planes in landing queue: 0
Planes in takeoff queue: 71




____________________________________________________
INITIAL VALUES
Time to takeoff a plane: 15
Probability of plane arrival into takeoff queue: 0.08
Time to land a plane: 5
Probability of plane arrival into landing queue: 0.1
Fuel: 20
Simulation time: 100
____________________________________________________
DEBUG
>>Pushed plane into takeoff queue with timestamp 4
<<Popped plane from takeoff queue with timestamp 4
>>Pushed plane into landing queue with timestamp 8
<<Popped plane from landing queue with timestamp 8
>>Pushed plane into takeoff queue with timestamp 26
<<Popped plane from takeoff queue with timestamp 26
>>Pushed plane into takeoff queue with timestamp 27
>>Pushed plane into takeoff queue with timestamp 31
>>Pushed plane into landing queue with timestamp 37
<<Popped plane from landing queue with timestamp 37
>>Pushed plane into landing queue with timestamp 43
>>Pushed plane into landing queue with timestamp 44
>>Pushed plane into takeoff queue with timestamp 44
<<Popped plane from landing queue with timestamp 43
>>Pushed plane into takeoff queue with timestamp 47
<<Popped plane from landing queue with timestamp 44
<<Popped plane from takeoff queue with timestamp 27
>>Pushed plane into takeoff queue with timestamp 69
>>Pushed plane into landing queue with timestamp 71
<<Popped plane from landing queue with timestamp 71
>>Pushed plane into landing queue with timestamp 72
<<Popped plane from landing queue with timestamp 72
>>Pushed plane into landing queue with timestamp 77
<<Popped plane from landing queue with timestamp 77
<<Popped plane from takeoff queue with timestamp 31
>>Pushed plane into takeoff queue with timestamp 90
>>Pushed plane into landing queue with timestamp 91
>>Pushed plane into landing queue with timestamp 93
____________________________________________________
RESULTS
7 landed
4 took off
0 crashed
Average waiting time to land: 4.71429
Average waiting time to takeoff: 21
Planes in landing queue: 0
Planes in takeoff queue: 4


 */
#endif // Z_OUTPUT_H