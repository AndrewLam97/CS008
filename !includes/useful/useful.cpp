// FILE: useful.cxx
// IMPLEMENTS: Five useful functions (see useful.h for documentation)
// These functions are in the global namespace.
#include <cassert>
// Provides assert
#include <cctype>
// Provides toupper
#include <iostream>
// Provides cout, cin, get
#include <cstdlib>
// Provides rand, RAND_MAX
#include "useful.h"
using namespace std;

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

void eat_line( )
// Library facilities used: iostream
// Reads characters from cin until and end-of-line has been read.
{
    char next;
    do
        cin.get(next);
    while (next != '\n');
}

bool inquire(const char query[ ])
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

double random_fraction( )
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