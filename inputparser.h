#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "alarm.h"

#define BUF_SIZE 128

int read_from_stdin(char *output, size_t buffersize){
    memset(output, 0, buffersize);
    char format[32];
    memset(format, 0, 32);
    char size_str[32];
    snprintf(size_str, 32, "%d", buffersize);
    format[0] = '%';
    strcat(format, size_str);
    int size = strlen(format);
    format[size] = 'c';
    char line[buffersize];
    if (fgets(line, buffersize, stdin)){
        if (sscanf(line, format, output) == 1){
            int size = strlen(output);
            output[size-1] = '\0';
            return 1;
        }
    }
    return 0;
}

int parseinput()
{
    char inp[BUF_SIZE];
    printf("> ");
    read_from_stdin(inp, BUF_SIZE);
    
    if (strcmp(inp, "s") == 0)
    {
        printf("Please enter the time you want to set the alarm to: ");
        char time_str[BUF_SIZE];
        read_from_stdin(time_str, BUF_SIZE);
        add_alarm(time_str);
    }
    else if (strcmp(inp, "l") == 0)
    {
        kill_inactive_alarms();
        printf("You have the following alarms set:\n");
        print_active_alarms();
    }
    else if (strcmp(inp, "c") == 0)
    {
        printf("Please enter the number of the alarm you want to cancel: ");
        char alarm_str[BUF_SIZE];
        read_from_stdin(alarm_str, BUF_SIZE);
        int alarm;
        sscanf(alarm_str, "%d", &alarm);
        kill_alarm(alarm);
        printf("You have cancelled alarm %d\n", alarm);
    }
    else if (strcmp(inp, "r") == 0)
    {
        printf("Enter in how many seconds to set the alarm: ");
        char alarm_str[BUF_SIZE];
        read_from_stdin(alarm_str, BUF_SIZE);
        int time;
        sscanf(alarm_str,"%d", &time);
        set_alarm_x_seconds_from_now(time);
        printf("You have set the alarm in %d seconds\n", time);
    }
    else if (strcmp(inp, "x") == 0)
    {
        printf("You have exited the program\n");
        kill_all_alarms();
        return 0;
    }
    else
    {
        printf("%s is not a valid input\n", inp);
    }
    return 1;
}