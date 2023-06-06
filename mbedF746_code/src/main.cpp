#include <mbed.h>
#include <threadLvgl.h>

#//include "demos/lv_demos.h"
#include <cstdio>
//#include <time.h>
#include "DHT.h"

ThreadLvgl threadLvgl(30);

static lv_style_t style_btn;
static lv_style_t style_btn_pressed;
static lv_style_t style_btn_red;

DHT dht(A0,DHT22);
PwmOut pwmout(D1);

int main() {

    threadLvgl.lock();
    
    //lv_demo_widgets();

    threadLvgl.unlock();

    pwmout.period_ms(10);
    pwmout.write(0.4f);
     
    //DigitalIn digitalin

    while (1) {
        //digitalin.read();
        if(dht.readData() == ERROR_NONE) {
 

        }        
        // put your main code here, to run repeatedly:
        ThisThread::sleep_for(10ms);
    }
}