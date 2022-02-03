#define __USE_XOPEN
#define _GNU_SOURCE

#include <time.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_ALARMS 100
#define DATE_FORMAT "%Y-%m-%d %H:%M:%S"

#ifdef __linux__
    #define SOUND_PLAYER "mpg123 -q alarm.mp3"
#elif __APPLE__
    #define SOUND_PLAYER "afplay alarm.mp3"
#endif

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
            printf("Pid is %d\n", alarms[i].pid);
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
    struct alarm a;
    a.time = time(NULL) + seconds;
    // Create child process
    pid_t p[2];
    if (pipe(p) < 0)
        exit(1);

    pid_t local_pid = fork();
    if (local_pid == -1){
        fprintf(stderr, "An error has occured forking");
    }
    if (local_pid == 0)
    {
        pid_t pid = getpid();
        write(p[1], &pid, sizeof(pid));
        close(p[1]);
        close(p[0]);
        while (time(NULL) < a.time)
        {
            sleep(1);
        }
        printf("\rAlarm!\n>");
        fflush(stdout);
        char *mp3_command[] = {"mpg123", "-q", "alarm.mp3", NULL};
        execvp(mp3_command[0], mp3_command);
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

void add_alarm(char *time_str)
{
    struct tm tm_time;
    time_t alarm_time;
    strptime(time_str, DATE_FORMAT, &tm_time);
    alarm_time = mktime(&tm_time);
    time_t current_time = time(NULL);
    printf("Scheduling alarm in %ld seconds\n", alarm_time - current_time);
    set_alarm_x_seconds_from_now(alarm_time - current_time);
}

void kill_alarm(int alarm_id)
{
    if (alarms[alarm_id - 1].pid != 0)
    {
        kill(alarms[alarm_id - 1].pid, SIGKILL);
        alarms[alarm_id - 1].pid = 0;
        waitpid(alarms[alarm_id - 1].pid, NULL, 0);
    }
}

void kill_all_alarms()
{
    for (int i = 0; i < MAX_ALARMS; i++)
    {
        if (alarms[i].pid != 0)
        {
            kill(alarms[i].pid, SIGKILL);
            alarms[i].pid = 0;
            waitpid(alarms[i].pid, NULL, 0);
        }
    }
}

void remove_inactive_alarms()
{
    for (int i = 0; i < MAX_ALARMS; i++)
    {
        if (alarms[i].pid != 0 && !waitpid(alarms[i].pid, NULL, WNOHANG) == 0)
        {
            alarms[i].pid = 0;
        }
    }
}