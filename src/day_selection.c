#include "day_selection.h"

static int selected_year = 1405;
static int selected_month = 1;
static int selected_day = 1;

void day_selection_set(int year, int month, int day)
{
    selected_year = year;
    selected_month = month;
    selected_day = day;
}

void day_selection_get(int *year, int *month, int *day)
{
    if (year) *year = selected_year;
    if (month) *month = selected_month;
    if (day) *day = selected_day;
}
