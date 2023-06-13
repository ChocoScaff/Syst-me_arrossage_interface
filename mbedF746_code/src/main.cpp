#include "common.h"

//#include "demos/lv_demos.h"
#include <cstdio>
//#include <time.h>
#include "DHT.h"
#include "option.h"
#include "chart.h"

ThreadLvgl threadLvgl(30);

DHT dht(A0, DHT22);
PwmOut pwmout(D1);

float humidity;
float temperature;
lv_obj_t *label_humidity;
lv_obj_t *label_temperature;


void Label_event_humidity(void)
{

    char tab[20];
    sprintf(tab, "Humidite %2.0f", humidity);
    lv_label_set_text_fmt(label_humidity, tab); /*Set the labels text*/
    // lv_obj_center(label_humidity);
}

void Label_event_temperature(void)
{

    char tab[30];
    sprintf(tab, "temperature %2.0f", temperature);
    lv_label_set_text_fmt(label_temperature, tab); /*Set the labels text*/
    // lv_obj_center(label_humidity);
}

void Label_Humidity(void)
{
    label_humidity = lv_label_create(tab_Chart);
    lv_label_set_text(label_humidity, "Humidite");
    lv_obj_set_pos(label_humidity, WIDTH_SCREEN / 2 -40, 0);
}

void Label_Temperature(void) {
    label_temperature = lv_label_create(tab_Chart);
    lv_label_set_text(label_temperature, "Temperature");
    lv_obj_set_pos(label_temperature, WIDTH_SCREEN / 2 -40, HEIGHT_SCREEN-20);
}

static void event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        lv_calendar_date_t date;
        if (lv_calendar_get_pressed_date(obj, &date))
        {
            LV_LOG_USER("Clicked date: %02d.%02d.%d", date.day, date.month, date.year);
        }
    }
}

void lv_example_calendar_1(void)
{
    lv_obj_t *calendar = lv_calendar_create(lv_scr_act());
    lv_obj_set_size(calendar, 185, 185);
    lv_obj_align(calendar, LV_ALIGN_CENTER, 0, 27);
    lv_obj_add_event_cb(calendar, event_handler, LV_EVENT_ALL, NULL);

    lv_calendar_set_today_date(calendar, 2021, 02, 23);
    lv_calendar_set_showed_date(calendar, 2021, 02);

    /*Highlight a few days*/
    static lv_calendar_date_t highlighted_days[3]; /*Only its pointer will be saved so should be static*/
    highlighted_days[0].year = 2021;
    highlighted_days[0].month = 02;
    highlighted_days[0].day = 6;

    highlighted_days[1].year = 2021;
    highlighted_days[1].month = 02;
    highlighted_days[1].day = 11;

    highlighted_days[2].year = 2022;
    highlighted_days[2].month = 02;
    highlighted_days[2].day = 22;

    lv_calendar_set_highlighted_dates(calendar, highlighted_days, 3);

#if LV_USE_CALENDAR_HEADER_DROPDOWN
    lv_calendar_header_dropdown_create(calendar);
#elif LV_USE_CALENDAR_HEADER_ARROW
    lv_calendar_header_arrow_create(calendar);
#endif
    lv_calendar_set_showed_date(calendar, 2021, 10);
}

void lv_example_tabview_1(void)
{
    /*Create a Tab view object*/
    lv_obj_t *tabview;
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 50);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Tab 1");
    tab_Chart = lv_tabview_add_tab(tabview, "Chart");
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Tab 3");

    /*Add content to the tabs*/
    lv_obj_t *label = lv_label_create(tab1);
    lv_label_set_text(label, "This the first tab\n\n"
                             );

    label = lv_label_create(tab_Chart);
    lv_label_set_text(label, "");

    label = lv_label_create(tab3);
    lv_label_set_text(label, "Third tab");

    lv_obj_scroll_to_view_recursive(label, LV_ANIM_ON);
}

int main()
{

    threadLvgl.lock();

    threadLvgl.unlock();

    pwmout.period_ms(10);
    pwmout.write(0.4f);


    lv_example_tabview_1();
    chart_Init_humidity();
    chart_Init_temperature();
    // Btn_Options();
    Label_Humidity();
    Label_Temperature();

    while (1)
    {
        // digitalin.read();

        if (dht.readData() == ERROR_NONE)
        {
            humidity = dht.ReadHumidity();
            temperature = dht.ReadTemperature(CELCIUS);
            printf("humidité %4.2f \n", humidity);
            printf("temperature %4.2f \n", temperature);
            chart_setNextValue_humidity(humidity);
            chart_refresh_humidity();
            chart_setNextValue_temperature(temperature);
            chart_refresh_temperature();
            Label_event_humidity();
            Label_event_temperature();

        }
        // put your main code here, to run repeatedly:
        ThisThread::sleep_for(10ms);
    }
}