#include <mbed.h>
#include <threadLvgl.h>

#//include "demos/lv_demos.h"
#include <cstdio>
//#include <time.h>

ThreadLvgl threadLvgl(30);

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
        
        // put your main code here, to run repeatedly:
        ThisThread::sleep_for(10ms);
    }
}