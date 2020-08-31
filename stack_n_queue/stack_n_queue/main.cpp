/*
 * Author: Andrew Lam
 * Project: Stack and Queue
 * Purpose: Use a doubly linked list to create templated stack and queue classes.
 * Notes: main source file
 */

#include <iostream>
#include "../../!includes/list_functions/list_functions.h"
#include "../../!includes/stack/stack.h"
#include "../../!includes/queue/queue.h"
using namespace std;

int main()
{
    //cout << "Debug test";
    //cout << endl;

    //test_node();
    //test_insert_head();
    //test_delete_all();
    //test_empty();
    //test_insert_after();
    //test_delete_head();
    //test_copy_list();

    //test_stack_push();
    //test_stack_pop_empty();
    //test_stack_top_empty();
    //test_stack_cctor();
    //test_stack_assignment();

    //test_queue_push();
    //test_queue_pop();
    //test_queue_copy();
    //test_queue_pop_empty();
    //test_queue_top_empty();
    //test_queue_size();

    //cout << endl;
    //cout << "---END---" << endl;
    
    test_stack();
    cout << endl << endl << endl;
    test_queue();

    return 0;
}
