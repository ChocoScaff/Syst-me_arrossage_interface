
void chart_Init_humidity(void);
void chart_refresh_humidity(void);
void chart_setNextValue_humidity(float value);
void chart_clear(void);
void chart_Init_temperature(void);
void chart_refresh_temperature(void);
void chart_setNextValue_temperature(float value);

typedef enum {
    MENU_OPTIONS,
    MENU_HUMIDITY,
}MENU;