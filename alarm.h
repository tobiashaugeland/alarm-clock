#define __USE_XOPEN
#define _GNU_SOURCE
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

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

void print_active_alarms()
{
    for (int i = 0; i < MAX_ALARMS; i++)
    {
        if (alarms[i].pid != 0)
        {
            // printf("Pid is %d\n", alarms[i].pid);
            char time_str[32];
            struct tm tm_time;
            tm_time = *localtime(&alarms[i].time);
            strftime(time_str, sizeof(time_str), DATE_FORMAT, &tm_time);
            printf("Alarm %d at %s\n", i + 1, time_str);
        }
    }
}

void set_alarm_x_seconds_from_now(int seconds)
{

    if (idx >= MAX_ALARMS)
    {
        idx = 0;
    }
    struct alarm a;
    a.time = time(NULL) + seconds;
    // Create child process
    pid_t local_pid = fork();
    if (local_pid == -1)
    {
        fprintf(stderr, "An error has occured forking");
    }
    if (local_pid == 0)
    {
        sleep(seconds);
        printf("\rAlarm!\n>");
        fflush(stdout);
        execlp("mpg123", "mpg123", "-q", "alarm.mp3", NULL);
        exit(0);
    }
    else
    {
        a.pid = local_pid;
        alarms[idx] = a;
        idx++;
    }
}

void add_alarm(char *time_str)
{
    struct tm tm_time;
    time_t alarm_time;
    strptime(time_str, DATE_FORMAT, &tm_time);
    alarm_time = mktime(&tm_time);
    time_t current_time = time(NULL);
    if (alarm_time - current_time > 0)
    {
        printf("Scheduling alarm in %ld seconds\n", alarm_time - current_time);
        set_alarm_x_seconds_from_now(alarm_time - current_time);
    }
    else
    {
        printf("Invalid time\n");
    }
}

void kill_alarm(int alarm_id)
{
    if (alarm_id >= 0 && alarm_id < 100 && alarms[alarm_id - 1].pid != 0)
    {

        kill(alarms[alarm_id - 1].pid, SIGKILL);
        memset(&alarms[alarm_id - 1], 0, sizeof(alarms[alarm_id - 1]));

        waitpid(alarms[alarm_id - 1].pid, NULL, 0);
        printf("You have cancelled alarm %d\n", alarm_id);
    }
    else
    {
        printf("%d is not a valid alarm ID\n", alarm_id);
    }
}

void kill_all_alarms()
{
    for (int i = 0; i < MAX_ALARMS; i++)
    {
        if (alarms[i].pid != 0)
        {
            kill(alarms[i].pid, SIGKILL);
            memset(&alarms[i], 0, sizeof(alarms[i]));
            waitpid(alarms[i].pid, NULL, 0);
        }
    }
}

void kill_inactive_alarms()
{
    for (int i = 0; i < MAX_ALARMS; i++)
    {
        if (alarms[i].pid != 0 && !waitpid(alarms[i].pid, NULL, WNOHANG) == 0)
        {
            memset(&alarms[i], 0, sizeof(alarms[i]));
        }
    }
}