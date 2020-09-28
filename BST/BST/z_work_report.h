/*
 * Author: Andrew Lam
 * Project: Binary Search Tree
 * Purpose: Binary Search Tree Class
 * Notes: Work Report file.
 */

#ifndef Z_WORK_REPORT_H
#define Z_WORK_REPORT_H
/*
    Features:
        -Not Implemented: 
            
        -Implemented: 
            BST Functions (insert, search, print, clear, etc)
            BST Class with Big 3 Functions
            Interactive Command Line Interface
        -Partly implemented: Have one rare bug where erasing a node sometimes doesn't remove the old node

    Bugs     : features that are implemented are bug-free.

    Reflections:
        95% of my time was spent on bst_functions. The BST class ended up just making calls to the aforementioned
        functions. The most complex part of writing the class itself was remembering how to overload operators.
        With regards to bst_functions I ended up spending a lot of time on tree_erase and tree_print.
        Initially, my erase functions was only erasing the root node because I messed up my return statement
        somewhere. My print function also was printing in a non-formatted fashion. Ended up printing spaces 
        instead of using setw. I had to modify the search function a little bit so it would return the found 
        node instead of a boolean.

*/
#endif // Z_WORK_REPORT_H