#include "month_grid.h"
#include "month_view.h"
#include <stdio.h>
#include <string.h>

void month_grid_build(int year, int month, char *out, int out_size)
{
    if (!out || out_size <= 0) return;
    out[0] = '\0';

    PersianMonth info = persian_month_info(year, month);
    int used = 0;

    used += snprintf(out + used, out_size - used,
                     "ش  ی  د  س  چ  پ  ج\n");

    for (int i = 0; i < info.first_weekday; ++i)
        used += snprintf(out + used, out_size - used, "   ");

    for (int day = 1; day <= info.days_in_month; ++day) {
        used += snprintf(out + used, out_size - used, "%2d ", day);

        int weekday = (info.first_weekday + day - 1) % 7;
        if (weekday == 6 && day != info.days_in_month)
            used += snprintf(out + used, out_size - used, "\n");

        if (used >= out_size - 16) break;
    }
}
