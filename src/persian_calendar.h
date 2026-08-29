#ifndef PERSIAN_CALENDAR_H
#define PERSIAN_CALENDAR_H

typedef struct {
    int year;
    int month;
    int day;
} PersianDate;

PersianDate gregorian_to_persian(int gy, int gm, int gd);
const char *persian_month_name(int month);
const char *persian_weekday_name(int weekday);
void to_persian_digits(const char *ascii, char *out, int out_size);

#endif
