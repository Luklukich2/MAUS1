#include <Arduino.h>
#include <argviz.h>

#include "voltage_sensor.h"
#include "Motor.h"
#include "Encoder.h"
#include "fnSelector.h"
#include "Config.h"
#include "VE.h"
#include "Servo_motor.h"
#include "Mixer.h"
#include "Screens.h"

void setup()
{
    Serial.begin(115200);

    fns_init();
    m_init();
    vs_init();
    enc_l_init();
    enc_r_init();

    interrupts();

    argviz_init(Serial);
    argviz_registerScreen(0, volts);
    argviz_registerScreen(1, encoders);
    argviz_registerScreen(2, servo);
    argviz_start();
}

void loop()
{
    // Timer
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
        ;
    timer = micros();
    // Sense

    // Plan

    // Act
    mixer_tick(v_0, tetha_i0);
}