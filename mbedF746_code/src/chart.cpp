#include "common.h"

lv_chart_series_t * ser1;
lv_chart_series_t * ser2;
lv_obj_t * chart_temperature;
lv_obj_t * chart_humidity;

#define WIDTH_CHART 200
#define HEIGHT_CHART 150

void chart_Init_humidity(void)
{
    /*Create a chart*/
    
    chart_humidity = lv_chart_create(tab_Chart);
    lv_obj_set_size(chart_humidity, WIDTH_CHART, HEIGHT_CHART);
    lv_obj_center(chart_humidity);
    lv_chart_set_type(chart_humidity, LV_CHART_TYPE_LINE);   /*Show lines and points too*/

    /*Add two data series*/
    lv_chart_set_axis_tick(chart_humidity, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 5, true, 40);
    ser1 = lv_chart_add_series(chart_humidity, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);

    /*Set the next points on 'ser1'*/
    
    //lv_chart_set_next_value(chart, ser1, humidity);

    lv_chart_refresh(chart_humidity); /*Required after direct set*/
}

void chart_refresh_humidity(void) {
    lv_chart_refresh(chart_humidity); /*Required after direct set*/
}

void chart_setNextValue_humidity(float value) {
    lv_chart_set_next_value(chart_humidity, ser1, value);
}

void chart_clear(void) {
    lv_obj_clean(chart_humidity);
}

void chart_Init_temperature(void)
{
    /*Create a chart*/
    
    chart_temperature = lv_chart_create(tab_Chart);
    lv_obj_set_size(chart_temperature, WIDTH_CHART, HEIGHT_CHART);
    lv_obj_set_pos(chart_temperature,WIDTH_SCREEN/2-WIDTH_CHART/2,HEIGHT_SCREEN);
    lv_chart_set_type(chart_temperature, LV_CHART_TYPE_LINE);   /*Show lines and points too*/

    /*Add two data series*/
    lv_chart_set_axis_tick(chart_temperature, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 5, true, 40);
    ser2 = lv_chart_add_series(chart_temperature, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);

    /*Set the next points on 'ser1'*/
    
    //lv_chart_set_next_value(chart, ser1, humidity);

    lv_chart_refresh(chart_temperature); /*Required after direct set*/
}

void chart_refresh_temperature(void) {
    lv_chart_refresh(chart_temperature); /*Required after direct set*/
}

void chart_setNextValue_temperature(float value) {
    lv_chart_set_next_value(chart_temperature, ser2, value);
}