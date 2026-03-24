#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // char* and scanf
    string name = get_string("What's your name?");
    // %s format specifier for "string" of chars
    printf("hello, %s\n", name);
}
