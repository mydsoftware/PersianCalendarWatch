#ifndef CALENDAR_EVENTS_H
#define CALENDAR_EVENTS_H

#include <stdbool.h>

typedef struct {
    int year;
    int month;
    int day;
    bool holiday;
    const char *title;
} CalendarEvent;

const CalendarEvent *calendar_event_for_day(int year, int month, int day);

#endif
