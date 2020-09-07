/*
 * Author: Andrew Lam
 * Project: Airport Simulation
 * Purpose: Work Report File
 * Notes: 
 */
#ifndef Z_WORK_REPORT_H
#define Z_WORK_REPORT_H
/*
    Features:
        -Not Implemented: Did not implement priority queue as assignment was changed to 8-9.

        -Implemented: Simulated airport with plane landing and takeoff queues.
            Probability based plane enqueues.
            Runway status and reservation.
            Fuel tracking and crash monitoring.
            Calculated average wait times for takeoff and landing.

        -Partly Implemented: None

    Bugs     : Features that are implemented are bug-free.

    Reflections: The Car Wash program provided a solid basis for this project. Creating most of the other classes from
        the Car Wash program only took minor modifications. The most difficult part was creating the airport class that
        housed the simulation itself.

    Comments: It is clear that with the given values, the airport definitely needs at least another runway.
        About 1% of the planes that were attempting to land crashed.
        Any amount of plane crashes due to running out of fuel is unacceptable and the average takeoff wait time of 28000 
        during a 100000 iteration run is extremely long. I for sure would not like to be flying into or taking off from
        this airport. 

*/

#endif // Z_WORK_REPORT_H