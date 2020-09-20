#ifndef RECURSION_DRILL_H
#define RECURSION_DRILL_H
/*
RANDOM_FRACTAL COMMENTARY:
    The process of recursion in random_fractal occurs as follows: 
        -   The base case is if the width between endpoints is less than or equal to epsilon. This determines whether
            or not we continue to grab and move midpoints.
        -   If we reach the base case, we should print the height of the fractal.
        -   If the current width is greater than epsilon, we should divide the segment into two separate sections,
            right and left separated by a midpoint.
        -   With this new midpoint, we determine the height by taking the average of the left and right points and 
            adding a random number.
        -   This new midpoint gives us two new separate segments, left and right.
        -   We repeat the process for both segments until we reach the epsilon limited width.

RANDOM_FRACTAL OUTPUT:
    Segment max width not reached at level: 0, dividing and going up a level
    Segment max width not reached at level: 1, dividing and going up a level
    Segment max width not reached at level: 2, dividing and going up a level
    Segment max width not reached at level: 3, dividing and going up a level
    Max width at reached at level: 4, going down a level                                       |*********                   
    Max width at reached at level: 3, going down a level                                       |******                      
    Segment max width not reached at level: 2, dividing and going up a level
    Max width at reached at level: 3, going down a level                                       |*****                       
    Max width at reached at level: 2, going down a level                                       |***                         
    Segment max width not reached at level: 1, dividing and going up a level
    Segment max width not reached at level: 2, dividing and going up a level
    Max width at reached at level: 3, going down a level                                       |**                          
    Max width at reached at level: 2, going down a level                                      *|                            
    Segment max width not reached at level: 1, dividing and going up a level
    Max width at reached at level: 2, going down a level                                       |                            
    Max width at reached at level: 1, going down a level                                       |                            
    Segment max width not reached at level: 0, dividing and going up a level
    Segment max width not reached at level: 1, dividing and going up a level
    Segment max width not reached at level: 2, dividing and going up a level
    Max width at reached at level: 3, going down a level                                       |***                         
    Max width at reached at level: 2, going down a level                                       |*****                       
    Segment max width not reached at level: 1, dividing and going up a level
    Max width at reached at level: 2, going down a level                                       |*******                     
    Max width at reached at level: 1, going down a level                                       |************                
    Segment max width not reached at level: 0, dividing and going up a level
    Segment max width not reached at level: 1, dividing and going up a level
    Max width at reached at level: 2, going down a level                                       |************                
    Max width at reached at level: 1, going down a level                                       |*************               
    Segment max width not reached at level: 0, dividing and going up a level
    Max width at reached at level: 1, going down a level                                       |**********                  
    Max width at reached at level: 0, going down a level                                       |**********                  
    Max width reached at level 0, ending recursion...

BINARY SEARCH COMMENTARY:
    Binary search works in a similar process in which we recursively split the current working area into two halves
    in an attempt to find a desired value. Binary search only works on sorted sets. Binary search's base case
    ends recursion if the current element matches the desired element. Binary search limits the working area by 
    evaluating whether or not the current value is higher or lower than the midpoint of the current working area.
    Once the higher/lower section is determined, binary search redefines the working area to the section and repeats.
    Recursion ends when the current mid value is the desired search value.

 */

#endif // RECURSION_DRILL_H