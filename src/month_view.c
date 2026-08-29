#include "month_view.h"

/* تعداد روز ماه؛ ۶ ماه اول ۳۱، پنج ماه بعد ۳۰ و اسفند وابسته به کبیسه */
int persian_month_days(int year, int month)
{
    if (month <= 6) return 31;
    if (month <= 11) return 30;

    /* الگوریتم چرخه ۳۳ ساله برای UI؛ موتور دقیق‌تر می‌تواند بعداً جایگزین شود. */
    int r = year % 33;
    return (r == 1 || r == 5 || r == 9 || r == 13 || r == 17 ||
            r == 22 || r == 26 || r == 30) ? 30 : 29;
}

/* برای هم‌راستاسازی جدول، روز ۱ فروردین ۱۴۰۵ برابر شنبه است. */
int persian_weekday_from_jalali(int year, int month, int day)
{
    long offset = 0;
    int y = 1405;

    if (year >= y) {
        for (int yy = y; yy < year; ++yy)
            offset += persian_month_days(yy, 12) == 30 ? 366 : 365;
    } else {
        for (int yy = year; yy < y; ++yy)
            offset -= persian_month_days(yy, 12) == 30 ? 366 : 365;
    }

    for (int mm = 1; mm < month; ++mm)
        offset += persian_month_days(year, mm);

    offset += day - 1;

    /* 0=یکشنبه ... 6=شنبه؛ شنبه=6 */
    int result = (6 + (int)(offset % 7)) % 7;
    if (result < 0) result += 7;
    return result;
}

PersianMonth persian_month_info(int year, int month)
{
    PersianMonth info;
    info.year = year;
    info.month = month;
    info.first_weekday = persian_weekday_from_jalali(year, month, 1);
    info.days_in_month = persian_month_days(year, month);
    return info;
}
