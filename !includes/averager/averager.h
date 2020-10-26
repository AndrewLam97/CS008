#ifndef AVERAGER_H
#define AVERAGER_H
#include <vector>
#include <iostream>
using namespace std;

class Averager{
public:
    Averager();
    void add(double x);
    double getAverage();
private:
    vector<double> vec;
    int size;
};

Averager::Averager(){
    this->size = 0;
}

void Averager::add(double x){
    vec.push_back(x);
    size++;
}

double Averager::getAverage(){
    double total = 0;
    for(auto i:vec){
        total += i;
    }
    return (total / size);
}

#endif // AVERAGER_H