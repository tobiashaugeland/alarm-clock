#pragma once
#include <stdio.h>
#include <string.h>

int parseinput()
{
    char inp;
    printf("> ");
    scanf("%s", &inp);
    if(inp == 's')
    {
        printf("Please enter the time you want to set the alarm to: ");
        char time[32];
        scanf("%s", &time);
        printf("Alarm set for %s\n", time);
    }
    else if(strcmp(&inp, "l") == 0)
    {
        printf("You have the following alarms set:\n");

    }
    else if(strcmp(&inp, "c") == 0)
    {
        printf("Please enter the number of the alarm you want to cancel: ");
        int alarm;
        scanf("%d", &alarm);
        printf("You have cancelled alarm %d\n", alarm);
    }
    else if(strcmp(&inp, "x") == 0)
    {
        printf("You have exited the program\n");
        return 0;
    }
    else
    {
        printf("Please enter a valid input\n");
    }
    return 1;
}