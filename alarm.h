#pragma once
#include <time.h>
#include <stdio.h>

struct alarm
{
    time_t time;
    int pid;
};

struct alarm alarms[100];

void add_alarm(char * time){
    struct alarm a;
    struct tm tm_time;
    time_t alarm_time;
    strptime(time, "%F %T",&tm_time);
    alarm_time = mktime(&tm_time);
    printf("Epoch time: %d\n", alarm_time);

}