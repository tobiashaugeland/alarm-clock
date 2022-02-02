#pragma once
#include <stdio.h>
#include <string.h>
#include "alarm.h"

int parseinput()
{
    char inp;
    printf("> ");
    fgets(&inp, 2, stdin);
    if(getchar() != '\n' || inp == '\n')
    {
        printf("Invalid input\n");
        return 1;
    }
    if(strcmp(&inp, "s") == 0)
    {
        printf("Please enter the time you want to set the alarm to: ");
        char time_str[20];
        fgets(time_str, 20, stdin);
        add_alarm(time_str);
    }
    else if(strcmp(&inp, "l") == 0)
    {
        printf("You have the following alarms set:\n");
        print_active_alarms();

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