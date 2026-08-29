#include <app.h>
#include <Elementary.h>
#include <time.h>
#include <stdio.h>
#include "persian_calendar.h"

static Evas_Object *date_label;

static void update_date(void)
{
    if (!date_label) return;
    time_t now = time(NULL);
    struct tm *lt = localtime(&now);
    if (!lt) return;

    PersianDate p = gregorian_to_persian(lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);
    char d[16], y[16], pd[32], py[32], text[256];
    snprintf(d, sizeof(d), "%d", p.day);
    snprintf(y, sizeof(y), "%d", p.year);
    to_persian_digits(d, pd, sizeof(pd));
    to_persian_digits(y, py, sizeof(py));

    snprintf(text, sizeof(text),
        "<align=center><font_size=38>%s</font_size><br>"
        "<font_size=24>%s</font_size><br>"
        "<font_size=20>%s %s</font_size></align>",
        pd, persian_month_name(p.month), persian_weekday_name(lt->tm_wday), py);
    elm_object_text_set(date_label, text);
}

static void delete_cb(void *data, Evas_Object *obj, void *event_info)
{
    ui_app_exit();
}

static bool app_create(void *data)
{
    Evas_Object *win = elm_win_util_standard_add("تقویم شمسی", "تقویم شمسی");
    elm_win_autodel_set(win, EINA_TRUE);
    evas_object_smart_callback_add(win, "delete,request", delete_cb, NULL);

    date_label = elm_label_add(win);
    evas_object_size_hint_weight_set(date_label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(date_label, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(date_label);
    elm_win_resize_object_add(win, date_label);
    evas_object_show(win);
    update_date();
    return true;
}

static void app_control(app_control_h app_control, void *data) {}
static void app_pause(void *data) {}
static void app_resume(void *data) { update_date(); }
static void app_terminate(void *data) {}

int main(int argc, char *argv[])
{
    ui_app_lifecycle_callback_s callbacks = {0};
    callbacks.create = app_create;
    callbacks.control = app_control;
    callbacks.pause = app_pause;
    callbacks.resume = app_resume;
    callbacks.terminate = app_terminate;
    return ui_app_main(argc, argv, &callbacks, NULL);
}
