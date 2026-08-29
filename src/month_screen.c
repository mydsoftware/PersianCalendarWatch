#include <app.h>
#include <Elementary.h>
#include <stdio.h>
#include "month_view.h"
#include "persian_calendar.h"
#include "month_grid.h"

static Evas_Object *month_label;
static int current_year = 1405;
static int current_month = 1;

static void render_month(void)
{
    char grid[1024];
    char title[128];
    month_grid_build(current_year, current_month, grid, sizeof(grid));
    snprintf(title, sizeof(title), "%s %d\n\n%s",
             persian_month_name(current_month), current_year, grid);
    elm_object_text_set(month_label, title);
}

void month_screen_next(void)
{
    current_month++;
    if (current_month > 12) { current_month = 1; current_year++; }
    render_month();
}

void month_screen_previous(void)
{
    current_month--;
    if (current_month < 1) { current_month = 12; current_year--; }
    render_month();
}

void month_screen_create(Evas_Object *win)
{
    month_label = elm_label_add(win);
    evas_object_size_hint_weight_set(month_label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(month_label, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(month_label);
    elm_win_resize_object_add(win, month_label);
    render_month();
}
