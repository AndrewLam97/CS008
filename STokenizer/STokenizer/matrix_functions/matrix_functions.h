/*
 * Author: Andrew Lam
 * Project: String Tokenizer
 * Purpose: Adjacency Matrix modification functions
 * Notes: 
 */

#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H
#include <cstring>

//Fill all cells of the array with -1
void init_table(int _table[MAX_ROWS][MAX_COLUMNS])
{
    memset(_table, -1, sizeof(_table[0][0] * MAX_ROWS * MAX_COLUMNS));
}

//Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state);

//Mark this state (row) with a 0 (fail)
void mark_fail(int _table[][MAX_COLUMNS], int state);

//true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state);

//Mark a range of cells in the array.
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state);

//Mark columns represented by the string columns[] for this row
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state);

//Mark this row and column
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state);

//This can realistically be used on a small table
void print_table(int _table[][MAX_COLUMNS])
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            cout << _table[i][j] << " ";
        }
        cout << endl;
    }
}

//show string s and mark this position on the string:
//hello world   pos: 7
//       ^
void show_string(char s[], int _pos);

#endif // MATRIX_FUNCTIONS_H