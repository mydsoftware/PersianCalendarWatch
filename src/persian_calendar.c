#include "persian_calendar.h"
#include <string.h>

/* تبدیل تاریخ میلادی به شمسی، کاملاً آفلاین */
PersianDate gregorian_to_persian(int gy, int gm, int gd)
{
    static const int g_days[] = {0,31,59,90,120,151,181,212,243,273,304,334};
    int gy2 = (gm > 2) ? gy + 1 : gy;
    long days = 355666L + 365L * gy + (gy2 + 3) / 4
              - (gy2 + 99) / 100 + (gy2 + 399) / 400
              + gd + g_days[gm - 1];

    int jy = -1595 + 33 * (int)(days / 12053);
    days %= 12053;
    jy += 4 * (int)(days / 1461);
    days %= 1461;

    if (days > 365) {
        jy += (days - 1) / 365;
        days = (days - 1) % 365;
    }

    PersianDate p;
    if (days < 186) {
        p.month = 1 + (int)(days / 31);
        p.day = 1 + (int)(days % 31);
    } else {
        p.month = 7 + (int)((days - 186) / 30);
        p.day = 1 + (int)((days - 186) % 30);
    }
    p.year = jy;
    return p;
}

const char *persian_month_name(int month)
{
    static const char *names[] = {"", "فروردین", "اردیبهشت", "خرداد", "تیر", "مرداد", "شهریور", "مهر", "آبان", "آذر", "دی", "بهمن", "اسفند"};
    return (month >= 1 && month <= 12) ? names[month] : "";
}

const char *persian_weekday_name(int weekday)
{
    static const char *names[] = {"یکشنبه", "دوشنبه", "سه‌شنبه", "چهارشنبه", "پنجشنبه", "جمعه", "شنبه"};
    return (weekday >= 0 && weekday <= 6) ? names[weekday] : "";
}

void to_persian_digits(const char *ascii, char *out, int out_size)
{
    static const char *digits[] = {"۰","۱","۲","۳","۴","۵","۶","۷","۸","۹"};
    int pos = 0;
    for (int i = 0; ascii[i] && pos < out_size - 5; ++i) {
        if (ascii[i] >= '0' && ascii[i] <= '9') {
            const char *d = digits[ascii[i] - '0'];
            int n = (int)strlen(d);
            memcpy(out + pos, d, n);
            pos += n;
        } else {
            out[pos++] = ascii[i];
        }
    }
    out[pos] = '\0';
}
