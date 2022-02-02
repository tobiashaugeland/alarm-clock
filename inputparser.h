#pragma once
#include <stdio.h>
#include <string.h>

int parseinput()
{
    char inp;
    scanf("%s", &inp);
    if(strcmp(&inp, "s") == 0)
    {
        printf("Please enter the time you want to set the alarm to\n");
        char time[9];
        scanf("%s", &time);
        printf("Please enter the message you want to be displayed\n");
        char message[100];
        scanf("%s", &message);
        printf("You have set the alarm to %s with the message %s\n", time, message);
        return 1;
    }
    else if(strcmp(&inp, "l") == 0)
    {
        printf("You have the following alarms set:\n");
        printf("Alarm 1: 2022-01-31 14:15:23\n");
        printf("Alarm 2: 2022-01-31 14:15:23\n");
        printf("Alarm 3: 2022-01-31 14:15:23\n");
        return 1;
    }
    else if(strcmp(&inp, "c") == 0)
    {
        printf("Please enter the number of the alarm you want to cancel\n");
        int alarm;
        scanf("%d", &alarm);
        printf("You have cancelled alarm %d\n", alarm);
        return 1;
    }
    else if(strcmp(&inp, "x") == 0)
    {
        printf("You have exited the program\n");
        return 0;
    }
    else
    {
        printf("Please enter a valid input\n");
        return 1;
    }
    return 1;
}