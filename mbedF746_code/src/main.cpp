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
lv_obj_t * label_slider;
lv_obj_t * btnm1;

lv_calendar_date_t date;

void Label_event_humidity(void) {
    char tab[20];
    sprintf(tab, "Humidite %2.0f", humidity);
    lv_label_set_text_fmt(label_humidity, tab); /*Set the labels text*/
    // lv_obj_center(label_humidity);
}

void Label_event_temperature(void) {
    char tab[30];
    sprintf(tab, "temperature %2.0f", temperature);
    lv_label_set_text_fmt(label_temperature, tab); /*Set the labels text*/
    // lv_obj_center(label_humidity);
}

void Label_Humidity(void) {
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
        
        if (lv_calendar_get_pressed_date(obj, &date))
        {
            LV_LOG_USER("Clicked date: %02d.%02d.%d", date.day, date.month, date.year);
        }
    }
}

void lv_example_calendar_1(void)
{
    lv_obj_t *calendar = lv_calendar_create(tab3);
    lv_obj_set_size(calendar, 185, 185);
    //lv_obj_align(calendar, LV_ALIGN_CENTER, 0, 27);
    lv_obj_set_pos(calendar,WIDTH_SCREEN/2-185/2, HEIGHT_SCREEN);
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
    tab1 = lv_tabview_add_tab(tabview, "Pompe");
    tab_Chart = lv_tabview_add_tab(tabview, "Chart");
    tab3 = lv_tabview_add_tab(tabview, "Setting");
    tab4 = lv_tabview_add_tab(tabview, "Clavier");

    /*Add content to the tabs*/
    lv_obj_t *label = lv_label_create(tab1);
    lv_label_set_text(label, "Puissance de la pompe\n"
                             );


    lv_obj_scroll_to_view_recursive(label, LV_ANIM_ON);
}

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);

    /*Refresh the text*/
    lv_label_set_text_fmt(label_slider, "%d%%", lv_slider_get_value(slider));
    lv_obj_align_to(label_slider, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
    pwmout.write(lv_slider_get_value(slider)/100.0);
}

void lv_Slider(void)
{
    /*Create a slider in the center of the display*/
    lv_obj_t * slider = lv_slider_create(tab1);
    lv_obj_set_width(slider, 200);                          /*Set the width*/
    lv_obj_center(slider);                                  /*Align to the center of the parent (screen)*/
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*Assign an event function*/

    /*Create a label above the slider*/
    label_slider = lv_label_create(tab1);
    lv_label_set_text(label_slider, "0 %");
    lv_obj_align_to(label_slider, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

static void btnmatrix_1_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        const char * txt = lv_btnmatrix_get_btn_text(obj, id);
        LV_UNUSED(txt);
        LV_LOG_USER("%s was pressed\n", txt);
    }
}


static const char * btnm_map[] = {"1", "2", "3", "4", "5", "\n",
                                  "6", "7", "8", "9", "0", "\n",
                                  "Action1", "Action2", ""
                                 };

void btnmatrix_1(void)
{
    btnm1 = lv_btnmatrix_create(tab3);
    lv_btnmatrix_set_map(btnm1, btnm_map);
    lv_btnmatrix_set_btn_width(btnm1, 10, 2);        /*Make "Action1" twice as wide as "Action2"*/
    lv_btnmatrix_set_btn_ctrl(btnm1, 10, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_btnmatrix_set_btn_ctrl(btnm1, 11, LV_BTNMATRIX_CTRL_CHECKED);
    lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(btnm1, btnmatrix_1_event_handler, LV_EVENT_ALL, NULL);
    //lv_obj_add_flag(btnm1,LV_OBJ_FLAG_HIDDEN);
}

static void lv_Box_Text_event_handler(lv_event_t * e)
{
    //lv_obj_add_flag(btnm1,LV_OBJ_FLAG_HIDDEN);
    //lv_obj_clear_flag(btnm1,LV_OBJ_FLAG_HIDDEN);
    
}

void lv_Box_Text(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 5);

    /*Make a gradient*/
    lv_style_set_width(&style, 150);
    lv_style_set_height(&style, LV_SIZE_CONTENT);

    lv_style_set_pad_ver(&style, 20);
    lv_style_set_pad_left(&style, 5);

    lv_style_set_x(&style, lv_pct(50));
    lv_style_set_y(&style, 80);

    /*Create an object with the new style*/
    lv_obj_t * obj = lv_obj_create(tab3);
    lv_obj_add_style(obj, &style, 0);

    lv_obj_t * label = lv_label_create(obj);
    lv_label_set_text(label, "0");
    lv_obj_add_event_cb(label, lv_Box_Text_event_handler, LV_EVENT_CLICKED, NULL); 

    lv_obj_t * label_text = lv_label_create(tab3);
    lv_label_set_text(label_text, "Valeur min");
    lv_obj_set_style_text_color(tab3, lv_color_hex(0xff000000), LV_PART_MAIN);
    lv_obj_set_pos(label_text,10,80);
}

static void lv_roller_1_event_handler_Month(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        date.month = *buf;
        printf("Roller %s \n",buf);
    }
}


static void lv_roller_1_event_handler_Day(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        date.day = *buf;
        printf("Roller %s \n",buf);
    }
}

static void lv_roller_1_event_handler_Year(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        date.year = *buf;
        printf("Roller %s \n",buf);
    }
}

/**
 * An infinite roller with the name of the months
 */
void lv_roller_1(void)
{
    lv_obj_t * roller1 = lv_roller_create(tab3);
    lv_roller_set_options(roller1,
                          "January\n"
                          "February\n"
                          "March\n"
                          "April\n"
                          "May\n"
                          "June\n"
                          "July\n"
                          "August\n"
                          "September\n"
                          "October\n"
                          "November\n"
                          "December",
                          LV_ROLLER_MODE_INFINITE);

    lv_roller_set_visible_row_count(roller1, 4);
    lv_obj_set_pos(roller1,0,HEIGHT_SCREEN*2);
    //lv_obj_center(roller1);
    lv_obj_add_event_cb(roller1, lv_roller_1_event_handler_Month, LV_EVENT_ALL, NULL);

    lv_obj_t * roller2 = lv_roller_create(tab3);
    lv_roller_set_options(roller2,
                          "1\n"
                          "2\n"
                          "3\n"
                          "4\n"
                          "5\n"
                          "6\n"
                          "7\n"
                          "8\n"
                          "9\n"
                          "10\n"
                          "11\n"
                          "12\n"
                          "13\n"
                          "14\n"
                          "15\n"
                          "16\n"
                          "17\n"
                          "18\n"
                          "19\n"
                          "20\n"
                          "21\n"
                          "22\n"
                          "23\n"
                          "24\n"
                          "25\n"
                          "26\n"
                          "27\n"
                          "28\n"
                          "29\n"
                          "30\n"
                          "31"
                          ,
                          LV_ROLLER_MODE_INFINITE);

    lv_roller_set_visible_row_count(roller2, 4);
    lv_obj_set_pos(roller2,120,HEIGHT_SCREEN*2);
    //lv_obj_center(roller1);
    lv_obj_add_event_cb(roller2, lv_roller_1_event_handler_Day, LV_EVENT_ALL, NULL);

lv_obj_t * roller3 = lv_roller_create(tab3);
    lv_roller_set_options(roller3,
                          "2000\n"
                          "2001\n"
                          "2002\n"
                          "2003\n"
                          "2004\n"
                          "2005\n"
                          "2006\n"
                          "2007\n"
                          "2008\n"
                          "2009\n"
                          "2010\n"
                          "2011\n"
                          "2012\n"
                          "2013\n"
                          "2014\n"
                          "2015\n"
                          "2016\n"
                          "2017\n"
                          "2018\n"
                          "2019\n"
                          "2020\n"
                          "2021\n"
                          "2022\n"
                          "2023\n"
                          "2024\n"
                          "2025\n"
                          "2026\n"
                          "2027\n"
                          "2028\n"
                          "2029\n"
                          "2030\n"
                          "2031"
                          ,
                          LV_ROLLER_MODE_INFINITE);

    lv_roller_set_visible_row_count(roller3, 4);
    lv_obj_set_pos(roller3,200,HEIGHT_SCREEN*2);
    //lv_obj_center(roller1);
    lv_obj_add_event_cb(roller3, lv_roller_1_event_handler_Month, LV_EVENT_ALL, NULL);

}

static lv_obj_t * kb;

static void ta_event_cb(lv_event_t * e)
{
    lv_obj_t * ta = lv_event_get_target(e);
    const char * txt = lv_textarea_get_text(ta);
    if(txt[0] >= '0' && txt[0] <= '9' &&
       txt[1] >= '0' && txt[1] <= '9' &&
       txt[2] != ':') {
        lv_textarea_set_cursor_pos(ta, 2);
        lv_textarea_add_char(ta, ':');
    }
    //printf("%d %d %d %d\n",txt[0],txt[1],txt[2],txt[3]);
}

/**
 * Automatically format text like a clock. E.g. "12:34"
 * Add the ':' automatically.
 */
void lv_example_textarea_3(void)
{
    /*Create the text area*/
    lv_obj_t * ta = lv_textarea_create(tab4);
    lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_textarea_set_accepted_chars(ta, "0123456789:");
    lv_textarea_set_max_length(ta, 5);
    lv_textarea_set_one_line(ta, true);
    lv_textarea_set_text(ta, "");

    /*Create a keyboard*/
    kb = lv_keyboard_create(tab4);
    lv_obj_set_size(kb,  LV_HOR_RES, LV_VER_RES / 2);
    lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_NUMBER);
    lv_keyboard_set_textarea(kb, ta);
}



int main()
{

    threadLvgl.lock();

    threadLvgl.unlock();

    pwmout.period_ms(10);
    pwmout.write(0.0f);

    
    lv_example_tabview_1();
    chart_Init_humidity();
    chart_Init_temperature();
    // Btn_Options();
    Label_Humidity();
    Label_Temperature();
    lv_Slider();
    
    lv_Box_Text();
    lv_example_calendar_1();
    lv_roller_1();
    
    lv_example_textarea_3();
    //btnmatrix_1();

    while (1)
    {
        // digitalin.read();

        if (dht.readData() == ERROR_NONE)
        {
            humidity = dht.ReadHumidity();
            temperature = dht.ReadTemperature(CELCIUS);
            //printf("humidité %4.2f \n", humidity);
            //printf("temperature %4.2f \n", temperature);
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