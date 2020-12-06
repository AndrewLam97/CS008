/*
 * Author: Andrew Lam
 * Project: STokenizer
 * Purpose: Returns a single token via extraction operator from a string according to internal FSM
 * Notes: Starting string = "it was the night of october 17th. pi was still 3.14."
 */

#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
     ALPHA         |it|
     SPACE         | |
     ALPHA         |was|
     SPACE         | |
     ALPHA         |the|
     SPACE         | |
     ALPHA         |night|
     SPACE         | |
     ALPHA         |of|
     SPACE         | |
     ALPHA         |october|
     SPACE         | |
    NUMBER         |17|
     ALPHA         |th|
PUNCTUATION         |.|
     SPACE         | |
     ALPHA         |pi|
     SPACE         | |
     ALPHA         |was|
     SPACE         | |
     ALPHA         |still|
     SPACE         | |
    NUMBER         |3.14|
PUNCTUATION         |.|
*/
#endif // Z_OUTPUT_H