#pragma once
#include <Arduino.h>

#define BATTERY_VOLTS A7

void vs_init()
{
    pinMode(BATTERY_VOLTS, INPUT);
}

float vs_get_v_batt()
{
    int BATT_VOLTS_RAW = analogRead(BATTERY_VOLTS);
    float BATT_VOLTS_V = BATT_VOLTS_RAW * 5.0 / 1024;
    float V_BATT_V = 2 * BATT_VOLTS_V;
    return V_BATT_V;
}