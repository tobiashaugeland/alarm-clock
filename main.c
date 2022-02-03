#include "inputparser.h"
#include <stdio.h>
int main(void)
{
    char current_time_str[32];
    struct tm *current_tm_time;
    time_t epoch_at_start = time(NULL);
    current_tm_time = localtime(&epoch_at_start);
    strftime(current_time_str, sizeof(current_time_str), DATE_FORMAT, current_tm_time);
    printf("Welcome to the alarm clock! It is currently %s\nPlease enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit)\n", current_time_str);

    printf("Please provide input\n");
    while (parseinput()){}
    return 0;
}