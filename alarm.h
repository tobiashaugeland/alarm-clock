#pragma once
#define __USE_XOPEN
#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#define MAX_ALARMS 100
#define DATE_FORMAT "%Y-%m-%d %H:%M:%S"

struct alarm
{
    time_t time;
    int pid;
};

struct alarm alarms[MAX_ALARMS];
int idx = 0;

void add_alarm(char *time_str)
{
    struct alarm a;
    struct tm tm_time;
    time_t alarm_time;
    strptime(time_str, DATE_FORMAT, &tm_time);
    alarm_time = mktime(&tm_time);
    printf("Scheduling alarm in %d seconds\n", alarm_time - time(NULL));
    a.time = alarm_time;
    a.pid = 123;
    alarms[idx] = a;
    idx++;
}

void print_active_alarms()
{
    for (int i = 0; i < MAX_ALARMS; i++)
    {
        if (alarms[i].pid != 0)
        {
            char time_str[32];
            struct tm tm_time;
            tm_time = *localtime(&alarms[i].time);
            strftime(time_str, sizeof(time_str), DATE_FORMAT, &tm_time);
            printf("Alarm %d at %s\n", i, time_str);
        }
    }
}