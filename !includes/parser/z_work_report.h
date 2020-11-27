/*
 * Author: Andrew Lam
 * Project: Parser Class
 * Purpose: Parser Class
 * Notes: Work Report file.
 */

#ifndef Z_WORK_REPORT_H
#define Z_WORK_REPORT_H
/*
    Features:
        -Not Implemented: 
            Postfix command processing
        -Implemented: 
            SQL lookup map generation and access
            Parser string tokenization
            Command multimap generation from string
            Selecting specified Field from table

        -Partly implemented:
            Adjacency Matrix generation and ruleset
            
    Bugs     : features that are implemented are bug-free.

    Reflections: Makes use of a lot of previously created data structures, a lot
    of interfacing with previously created components. Weird thing was Canvas said
    that ptree is a multimap but I believe a regular map would work better so as 
    to avoid using an extra [0] for each access. Regardless, works surprisingly well.
    I tried to leave myself as much room as possible to grow into the feature set
    required by the final project. The adjacency matrix isn't complete yet as we only
    have three commands right now. In the future, I think I will be using postfix
    notation and a queue to process commands.

*/
#endif // Z_WORK_REPORT_H