#include "calendar_events.h"

/*
 * داده نهایی مناسبت‌ها در زمان Sync از Time.ir تولید می‌شود.
 * این لایه باعث می‌شود UI به منبع داده وابسته نباشد.
 */
static CalendarEvent events[] = {
    {1405, 1, 1, true, "نوروز"},
    {0, 0, 0, false, 0}
};

const CalendarEvent *calendar_event_for_day(int year, int month, int day)
{
    for (int i = 0; events[i].year != 0; ++i) {
        if (events[i].year == year &&
            events[i].month == month &&
            events[i].day == day) {
            return &events[i];
        }
    }
    return 0;
}
