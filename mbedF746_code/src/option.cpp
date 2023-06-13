#include "common.h"
#include "chart.h"

static void btn_event_cb(lv_event_t * e)
{
    static char option = 0;

    if (option == 0) {
        //lv_example_calendar_1();
       //menu = MENU_OPTION;
    }
    else if (option == 1) {
        
    }
}

void Btn_Options(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act()); /*Add a button the current screen*/
    lv_obj_set_pos(btn, WIDTH_SCREEN-120, 10); /*Set its position*/
    lv_obj_set_size(btn, 120, 50); /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_PRESSED, NULL); /*Assign a callback to the button*/
    lv_obj_t * label = lv_label_create(btn); /*Add a label to the button*/
    lv_label_set_text(label, "Options"); /*Set the labels text*/
    lv_obj_center(label);
}