#include <mbed.h>
#include <threadLvgl.h>

#//include "demos/lv_demos.h"
#include <cstdio>
//#include <time.h>
#include "DHT.h"

#define WIDTH_SCREEN 480
#define HEIGHT_SCREEN 270

ThreadLvgl threadLvgl(30);

DHT dht(A0,DHT22);
PwmOut pwmout(D1);

float humidity;
lv_obj_t * label_humidity;

void lv_example_style_6(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    /*Set a background color and a radius*/
    
    /*Create an object with the new style*/
    lv_obj_t * obj = lv_img_create(lv_scr_act());
    lv_obj_add_style(obj, &style, 0);
    LV_IMG_DECLARE(button_UI);
    lv_img_set_src(obj, &button_UI);
    lv_obj_center(obj);
}

void Label_event_humidity(void) {

    char tab[20];
    sprintf(tab,"Humidite %2.0f",humidity);
    lv_label_set_text_fmt(label_humidity, tab); /*Set the labels text*/
    lv_obj_center(label_humidity);
}

void Label_Humidity(void)
{
    label_humidity = lv_label_create(lv_scr_act());
    lv_label_set_text(label_humidity, "Humidite");
    lv_obj_set_pos(label_humidity, 100, 10);

}



static void btn_event_cb(lv_event_t * e)
{
    /*
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
    */
}


void Btn_Options(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act()); /*Add a button the current screen*/
    lv_obj_set_pos(btn, WIDTH_SCREEN-120, 10); /*Set its position*/
    lv_obj_set_size(btn, 120, 50); /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL); /*Assign a callback to the button*/
    lv_obj_t * label = lv_label_create(btn); /*Add a label to the button*/
    lv_label_set_text(label, "Options"); /*Set the labels text*/
    lv_obj_center(label);
}

int main() {

    threadLvgl.lock();

    threadLvgl.unlock();

    pwmout.period_ms(10);
    pwmout.write(0.4f);
     
    
    //DigitalIn digitalin
    //lv_example_style_6();
    Btn_Options();
    Label_Humidity();

    while (1) {
        //digitalin.read();
        
        if(dht.readData() == ERROR_NONE) {
            humidity = dht.ReadHumidity();
            printf("humidité %4.2f \n",humidity);
            Label_event_humidity();
        }

        // put your main code here, to run repeatedly:
        ThisThread::sleep_for(10ms);
    }
}