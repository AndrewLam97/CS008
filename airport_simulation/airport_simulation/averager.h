/*
 * Author: Andrew Lam
 * Project: Airport Simulation
 * Purpose: 
 * Notes: 
 */

#ifndef AVERAGER
#define AVERAGER

class averager{
public:
    void add_wait_takeoff(unsigned int t);
    void add_wait_landing(unsigned int t);
    void add_crash() { total_crash++; }

    void print_results(int landing_size, int takeoff_size);
private:
    double total_wait_takeoff = 0;
    double total_wait_landing = 0;
    int total_takeoff = 0;
    int total_landing = 0;
    int total_crash = 0;
};

void averager::add_wait_takeoff(unsigned int t){
    total_wait_takeoff += t;
    total_takeoff++;
}

void averager::add_wait_landing(unsigned int t){
    total_wait_landing += t;
    total_landing++;
}

void averager::print_results(int landing_size, int takeoff_size){
    cout << endl << "______________________" << endl;
    cout << total_landing << " landed" << endl;
    cout << total_takeoff << " took off" << endl;
    cout << total_crash << " crashed :(" << endl;
    cout << "Average waiting time to land: " << total_wait_landing / total_landing << endl;
    cout << "Average waiting time to takeoff: " << total_wait_takeoff / total_takeoff << endl;
    cout << "Planes in landing queue: " << landing_size << endl;
    cout << "Planes in takeoff queue: " << takeoff_size << endl;

}

#endif // AVERAGER