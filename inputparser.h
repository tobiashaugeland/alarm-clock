#pragma once
#include <stdio.h>
#include <string.h>
#include "alarm.h"

int parseinput()
{
    char inp;
    printf("> ");
    if (fgets(&inp, 3, stdin))
    {
        char *p;
        if (p = strchr(&inp, '\n'))
        { // check exist newline
            *p = 0;
        }
        else
        {
            scanf("%*[^\n]");
            scanf("%*c"); // clear upto newline
        }
    }
    if (strcmp(&inp, "s") == 0)
    {
        printf("Please enter the time you want to set the alarm to: ");
        char time_str[20];
        fgets(time_str, 20, stdin);
        add_alarm(time_str);
    }
    else if (strcmp(&inp, "l") == 0)
    {
        printf("You have the following alarms set:\n");
        print_active_alarms();
    }
    else if (strcmp(&inp, "c") == 0)
    {
        printf("Please enter the number of the alarm you want to cancel: ");
        int alarm;
        scanf("%d", &alarm);
        kill_alarm(alarm);
        printf("You have cancelled alarm %d\n", alarm);
    }
    else if (strcmp(&inp, "r") == 0)
    {
        printf("Enter in how many seconds to set the alarm: ");
        int time_str;
        scanf("%d", &time_str);
        set_alarm_x_seconds_from_now(time_str);
        printf("You have set the alarm in %d seconds\n", time_str);
    }
    else if (strcmp(&inp, "x") == 0)
    {
        printf("You have exited the program\n");
        kill_all_alarms();
        return 0;
    }
    else
    {
        printf("%s is not a valid input\n", &inp);
    }
    getchar();
    return 1;
}