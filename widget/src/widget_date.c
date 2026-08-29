#include <time.h>
#include <stdio.h>
#include "../inc/widget_date.h"
#include "../../src/persian_calendar.h"

void widget_date_text(char *out, int out_size)
{
    if (!out || out_size <= 0) return;

    time_t now = time(NULL);
    struct tm *lt = localtime(&now);
    if (!lt) {
        out[0] = '\0';
        return;
    }

    PersianDate p = gregorian_to_persian(
        lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);

    char d[16], y[16], pd[32], py[32];
    snprintf(d, sizeof(d), "%d", p.day);
    snprintf(y, sizeof(y), "%d", p.year);
    to_persian_digits(d, pd, sizeof(pd));
    to_persian_digits(y, py, sizeof(py));

    snprintf(out, out_size, "%s %s %s",
             pd, persian_month_name(p.month), py);
}
