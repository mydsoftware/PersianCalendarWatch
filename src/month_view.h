#ifndef MONTH_VIEW_H
#define MONTH_VIEW_H

/* محاسبات مورد نیاز نمایش ماه شمسی روی صفحه گرد واچ */
typedef struct {
    int year;
    int month;
    int first_weekday;
    int days_in_month;
} PersianMonth;

PersianMonth persian_month_info(int year, int month);
int persian_weekday_from_jalali(int year, int month, int day);
int persian_month_days(int year, int month);

#endif
