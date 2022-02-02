#include "inputparser.h"
#include <stdio.h>
int main(void)
{

    printf("Welcome to the alarm clock! It is currently 2022-01-31 14:15:23\nPlease enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit)\n");

    printf("Please provide input\n");
    while (parseinput())
    {

    }

    return 0;
}