#include <mbed.h>
#include <threadLvgl.h>

#//include "demos/lv_demos.h"
#include <cstdio>

ThreadLvgl threadLvgl(30);

static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;
        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

static void Init_2_Button(void) {
    lv_obj_t * btn = lv_btn_create(lv_scr_act()); /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10); /*Set its position*/
    lv_obj_set_size(btn, 120, 50); /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL); /*Assign a →callback to the button*/
    lv_obj_t * label = lv_label_create(btn); /*Add a label to the button*/
    lv_label_set_text(label, "Button"); /*Set the labels text*/
    lv_obj_center(label);

    lv_obj_t * btn2 = lv_btn_create(lv_scr_act()); /*Add a button the current screen*/
    lv_obj_set_pos(btn2, 140, 10); /*Set its position*/
    lv_obj_set_size(btn2, 120, 50); /*Set its size*/
    lv_obj_add_event_cb(btn2, btn_event_cb, LV_EVENT_PRESSED, NULL); /*Assign a →callback to the button*/
    lv_obj_t * label2 = lv_label_create(btn2); /*Add a label to the button*/
    lv_label_set_text(label2, "Button"); /*Set the labels text*/
    lv_obj_center(label2);
}

static lv_style_t style_btn;
static lv_style_t style_btn_pressed;
static lv_style_t style_btn_red;

static lv_color_t darken(const lv_color_filter_dsc_t * dsc, lv_color_t color, lv_opa_t opa)
{
    LV_UNUSED(dsc);
    return lv_color_darken(color, opa);
}

static void style_init(void)
{
    /*Create a simple button style*/
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, 10);
    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn, lv_palette_lighten(LV_PALETTE_GREY, 3));
    lv_style_set_bg_grad_color(&style_btn, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_bg_grad_dir(&style_btn, LV_GRAD_DIR_VER);
    lv_style_set_border_color(&style_btn, lv_color_black());
    lv_style_set_border_opa(&style_btn, LV_OPA_20);
    lv_style_set_border_width(&style_btn, 2);
    lv_style_set_text_color(&style_btn, lv_color_black());
    /*Create a style for the pressed state.
    *Use a color filter to simply modify all colors in this state*/
    static lv_color_filter_dsc_t color_filter;
    lv_color_filter_dsc_init(&color_filter, darken);
    lv_style_init(&style_btn_pressed);
    lv_style_set_color_filter_dsc(&style_btn_pressed, &color_filter);
    lv_style_set_color_filter_opa(&style_btn_pressed, LV_OPA_20);
    /*Create a red style. Change only some colors.*/
    lv_style_init(&style_btn_red);
    lv_style_set_bg_color(&style_btn_red, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_color(&style_btn_red, lv_palette_lighten(LV_PALETTE_RED, 3));
}

/**
* Create styles from scratch for buttons.
*/
void lv_example_get_started_2(void)
{
    /*Initialize the style*/
    style_init();
    /*Create a button and use the new styles*/
    lv_obj_t * btn = lv_btn_create(lv_scr_act());
    /* Remove the styles coming from the theme
    * Note that size and position are also stored as style properties
    * so lv_obj_remove_style_all will remove the set size and position too */
    lv_obj_remove_style_all(btn);
    lv_obj_set_pos(btn, 10, 10);
    lv_obj_set_size(btn, 120, 50);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_style(btn, &style_btn_pressed, LV_STATE_PRESSED);
    /*Add a label to the button*/
    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);
    /*Create another button and use the red style too*/
    lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
    lv_obj_remove_style_all(btn2); /*Remove the styles coming␣from the theme*/
    lv_obj_set_pos(btn2, 10, 80);
    lv_obj_set_size(btn2, 120, 50);
    lv_obj_add_style(btn2, &style_btn, 0);
    lv_obj_add_style(btn2, &style_btn_red, 0);
    lv_obj_add_style(btn2, &style_btn_pressed, LV_STATE_PRESSED);

    lv_obj_set_style_radius(btn2, LV_RADIUS_CIRCLE, 0); /*Add a local style too*/
    label = lv_label_create(btn2);
    lv_label_set_text(label, "Button 2");
    lv_obj_center(label);
}

int main() {

    threadLvgl.lock();

    lv_example_get_started_2();

    //lv_demo_widgets();

    threadLvgl.unlock();

    while (1) {
        // put your main code here, to run repeatedly:
        ThisThread::sleep_for(10ms);
    }
}