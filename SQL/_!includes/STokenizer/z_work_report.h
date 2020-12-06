/*
 * Author: Andrew Lam
 * Project: STokenizer
 * Purpose: Returns a single token via extraction operator from a string according to internal FSM
 * Notes: Work Report file.
 */

#ifndef Z_WORK_REPORT_H
#define Z_WORK_REPORT_H
/*
    Features:
        -Not Implemented: File Tokenization
            
        -Implemented: Return of token from string using extraction operator
            Hard-coded internal FSM
        -Partly implemented: none

    Bugs     : features that are implemented are bug-free.

    Reflections:
        Pretty easy once get_token() was finished. Hardest part was honestly making the table.
        One thing that confused me for a little bit was as to why we pass get_token a string by 
        reference and not just a token. We end up assigning that string to the token in the
        overloaded extraction operator anyways. Seems like passing get_token a token object would
        simplify the overloaded operator.

*/
#endif // Z_WORK_REPORT_H