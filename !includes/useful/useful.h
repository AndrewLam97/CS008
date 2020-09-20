// FILE: useful.h
// PROVIDES: Five useful functions for random numbers and displays. These functions are
// in the global namespace.
//
// FUNCTIONS PROVIDED:
// double random_fraction( )
//   Postcondition: The return value is a random real number in the closed interval [0..1]
//   (including the endpoints).
//
// double random_real(double low, double high)
//   Precondition: low <= high.
//   Postcondition: The return value is a random real number in the closed interval [low..high]
//   (including the endpoints).
//
// void display(double x)
//   Postcondition: The function has written one line of output to the standard output, with a
//   vertical bar in the middle. If x is positive, then approximately x stars are printed to the
//   right of the vertical bar. If x is negative, then approximately -x stars are printed to the
//   left of the vertical bar. If the absolute value of x is more than 39, then only 39 stars
//   are printed. Examples:
//   display(8) prints: |********
//   display(-4) prints: ****|
//
// void eat_line( )
//   Postcondition: Up to next newline has been read and discarded from cin.
//
// bool inquire(const char query[ ])
//   Precondition: query is a null-terminated string of characters.
//   Postcondition: query has been printed, and a one-line response read from the user.
//   The function returns true if the user’s response begins with 'Y' or 'y', and returns false if
//   the user’s response begins with 'N' or 'n'. (If the response begins with some other letter,
//   then the query is repeated.)
#ifndef USEFUL_H
#define USEFUL_H
#include <cassert>
// Provides assert
#include <cctype>
// Provides toupper
#include <iostream>
// Provides cout, cin, get
#include <cstdlib>
// Provides rand, RAND_MAX
#include <ctime>
using namespace std;

double random_fraction();
double random_real(double low, double high);
void display(double x);
void eat_line();
bool inquire(const char query[]);

// FILE: useful.cxx
// IMPLEMENTS: Five useful functions (see useful.h for documentation)
// These functions are in the global namespace.

void display(double x)
// Library facilities used: iostream
{
    const char STAR = '*';
    const char BLANK = ' ';
    const char VERTICAL_BAR = '|';
    const int LIMIT = 39;
    int i;
    if (x < -LIMIT)
        x = -LIMIT;
    else if (x > LIMIT)
        x = LIMIT;
    for (i = -LIMIT; i < 0; i++)
    {
        if (i >= x)
            cout << STAR;
        else
            cout << BLANK;
    }
    cout << VERTICAL_BAR;
    for (i = 1; i <= LIMIT; i++)
    {
        if (i <= x)
            cout << STAR;
        else
            cout << BLANK;
    }
    cout << endl;
}

void eat_line()
// Library facilities used: iostream
// Reads characters from cin until and end-of-line has been read.
{
    char next;
    do
        cin.get(next);
    while (next != '\n');
}

bool inquire(const char query[])
// Library facilities used: cctype, iostream
{
    char answer;
    do
    {
        cout << query << " [Yes or No]" << endl;
        cin >> answer;
        answer = toupper(answer);
        eat_line();
    } while ((answer != 'Y') && (answer != 'N'));
    return (answer == 'Y');
}

double random_fraction()
// Library facilities used: cstdlib
{
    
    return rand() / double(RAND_MAX);
}

double random_real(double low, double high)
// Library facilities used: cassert
{
    assert(low <= high);
    return low + random_fraction() * (high - low);
}

#endif // USEFUL_H