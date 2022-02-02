#pragma once
#include <stdio.h>

int parseinput()
{
    char inp;
    scanf("%s", &inp);
    switch (inp)
    {
    case 's':
        printf("Scheduling\n");
        break;

    case 'l':
        printf("Listing\n");
        break;

    case 'c':
        printf("Cancel\n");
        break;

    case 'x':
        printf("Goodbye\n");
        return 0;

    default:
        printf("Invalid input: '%c'. Please try again.\n", inp);
        break;
    }
    return 1;
}