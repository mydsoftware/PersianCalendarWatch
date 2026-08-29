#ifndef DAY_DETAILS_H
#define DAY_DETAILS_H

#include <stdbool.h>

typedef struct {
    int year;
    int month;
    int day;
    bool holiday;
    const char *title;
} DayDetails;

DayDetails day_details_get(int year, int month, int day);

#endif
