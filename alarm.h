#define __USE_XOPEN
#define _GNU_SOURCE

#include <time.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ALARMS 100
#define DATE_FORMAT "%Y-%m-%d %H:%M:%S"

#pragma once

struct alarm
{
    time_t time;
    pid_t pid;
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
            printf("Pid is %d\n", alarms[i].pid);
            char time_str[32];
            struct tm tm_time;
            tm_time = *localtime(&alarms[i].time);
            strftime(time_str, sizeof(time_str), DATE_FORMAT, &tm_time);
            printf("Alarm %d at %s\n", i, time_str);
        }
    }
}

void set_alarm_x_seconds_from_now(int seconds)
{
    struct alarm a;
    a.time = time(NULL) + seconds;
    // Create child process
    pid_t p[2];
    if(pipe(p) < 0) exit(1);

    pid_t local_pid = fork();
    if (local_pid == 0)
    {
        pid_t pid = getpid();
        write(p[1], &pid, sizeof(a));
        close(p[1]);
        close(p[0]);
        while (time(NULL) < a.time)
        {
            sleep(1);
        }
        printf("Alarm!\n");
        exit(0);
    }
    else
    {
        close(p[1]);
        pid_t c;
        read(p[0], &c, sizeof(c));
        a.pid = c;
        alarms[idx] = a;
        idx++;
        close(p[0]);
    }
}