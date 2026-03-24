#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int total = 0;
    while (total <= 0 || total > 8)
    {
        total = get_int("Height: ");
    }
    // %s format specifier for "string" of chars
    // initialization; condition; increment
    // example input 4
    // column 1 = ___# // 3 spaces // row1
    // column 2 = __## // 2 spaces // row2
    // column 3 = _### // 1 spaces // row3
    // column 4 = #### // 0 spaces // row4
    // total - row = space count
    // space count + row = total
    // index 1 here because 0th index would be a blank line
    for (int coll = 1; coll <= total; coll++)
    {
        int spaces = (total - coll);
        for (int row = 0; row < total; row++)
        {
            // because coll increments, spaces will get smaller each iteration of coll
            // loop.
            // coll idx says how many # need to be printed
            // use row as LR cursor index
            // when idx is less than spaces meaning should be a space
            if (row < spaces)
            {
                putchar(' ');
            }
            else
            {
                // if row cursor index passes the amount of spaces we need then it
                // should print #
                putchar('#');
            }
        }
        printf("  ");
        // reverse is much easier because no space logic
        for (int row = 0; row < coll; row++)
        {
            putchar('#');
        }
        putchar('\n');
    }
}
