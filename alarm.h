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

/**
 * @brief Lists out every active alarms.
 *
 */
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

/**
 * @brief Set the alarm x seconds from now object.
 *
 * @param seconds number of seconds from now
 */
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

/**
 * @brief Adds alarm to the list of alarms,
 * and activates a child process to handle the waiting.
 *
 * @param time_str format: "%Y-%m-%d %H:%M:%S"
 */
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
/**
 * @brief Kills alarm using the kill(1) system call.
 * Zombies are handled by waitpid(2).
 *
 * @param alarm_id refrence to alarm array
 */
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

/**
 * @brief Kills all alarms using the kill(1) system call.
 *
 */
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

/**
 * @brief Does a check over all alarms and kills any that have passed.
 *
 */
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