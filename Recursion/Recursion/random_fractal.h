#ifndef RANDOM_FRACTAL_H
#define RANDOM_FRACTAL_H
#include <cassert>
#include <iomanip>
#include "../../!includes/useful/useful.h"
using namespace std;

class fractal
{
private:
    int level = 0;
    int call = 0;
public:
    // fractal::fractal(double left_height, double right_height, double width, double epsilon){
    //     this->left_height = left_height;
    //     this->right_height = right_height;
    //     this->width = width;
    //     this->epsilon = epsilon;
    // }
    void random_fractal(double left_height, double right_height, double width, double epsilon);
    void generate_fractal();
};

void fractal::random_fractal(
    double left_height,
    double right_height,
    double width,
    double epsilon)
// Precondition: width and epsilon are both positive.
// Postcondition: The function has generated a random fractal from a line segment. The
// parameters left_height and right_height are the heights of the line segment, and the
// parameter width is the segment’s width. The generation of the random fractal stops when
// the width of the line segments reaches epsilon or less.
// Method of displaying the output: The height of the right endpoint of each line segment in
// the random fractal is displayed by calling the function display(...).
// Library facilities used: cassert, useful.h (from Appendix I)
{
    double mid_height;
    // Height of the midpoint of the line segment
    assert(width > 0);
    assert(epsilon > 0);
    if (width <= epsilon){ //stopping case, display when width is less than or equal to epsilon
        cout << "Max width at reached at level: " << level-- << ", going down a level";
        display(right_height);
        //cout << "Printing fractal" << endl;
    }
    else //else, keep dividing the segment
    {
        mid_height = (left_height + right_height) / 2;
        mid_height += random_real(-width, width);
        cout << "Segment max width not reached at level: " << level++ << ", dividing and going up a level" << endl;
        //cout << "Level: " << level++ << endl;
        random_fractal(left_height, mid_height, width / 2, epsilon);
        random_fractal(mid_height, right_height, width / 2, epsilon);
        //cout << "level: " << level-- << endl;
    }
}

void fractal::generate_fractal(){
    random_fractal(10.0, 10.0, 16.0, 1.0);
    cout << "Max width reached at level 0, ending recursion..." << endl;
}

#endif // RANDOM_FRACTAL_H