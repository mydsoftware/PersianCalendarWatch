#include "day_details.h"
#include "calendar_events.h"

DayDetails day_details_get(int year, int month, int day)
{
    DayDetails result = {year, month, day, false, 0};
    const CalendarEvent *event = calendar_event_for_day(year, month, day);
    if (event) {
        result.holiday = event->holiday;
        result.title = event->title;
    }
    return result;
}
