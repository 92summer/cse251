#ifndef  _DISPLAY_
#define _DISPLAY_

#define EVENT_MAX 20
#define EVENT_NAME_SIZE 50

#include <stdio.h>
#include <stdlib.h>
#define __USE_XOPEN
#include <time.h>
#include <string.h>

typedef struct event
{
    char name[EVENT_NAME_SIZE];
    time_t date;
    time_t starttime;
    time_t endtime;
}Event;

void print_opt();
void print_menu();
time_t InputDate(char *prompt);
time_t InputTime(char *prompt, time_t date);
void InputEventName(char *prompt, char *n);
void new_event(Event* eve,int *event_volume);
void print_event(Event* eve);
void display_all_event(Event* eve, int event_);
void print_now_event(Event *eve);
void Delete_expired(Event *eve, int *eve_num);

#endif