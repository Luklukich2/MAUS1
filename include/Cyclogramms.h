#pragma once

#include "Odometer.h"
#include "Mixer.h"

float v_0 = 0;
float tetha_i0 = 0;

void idle()
{
}
void stop()
{
    odom_reset();
    while (true)
    {
        // Timer
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
            ;
        timer = micros();

        // Sense
        odom_tick();
        // Plan
        v_0 = 0;
        tetha_i0 = 0;
        // Act
        mixer_tick(v_0, tetha_i0);
    }
}

void FWD_1c()
{
    odom_reset();
    while (true)
    {
        // Timer
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
            ;
        timer = micros();

        // Sense
        odom_tick();
        // Plan
        v_0 = MAX_VEL;
        tetha_i0 = 0;

        if (odom_get_S() > CELL_WIDHT)
        {
            return;
        }
        // Act
        mixer_tick(v_0, tetha_i0);
    }
}

void FWD_05c()
{
    odom_reset();
    while (true)
    {
        // Timer
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
            ;
        timer = micros();

        // Sense
        odom_tick();
        // Plan
        v_0 = MAX_VEL;
        tetha_i0 = 0;

        if (odom_get_S() > (CELL_WIDHT / 2))
        {
            return;
        }
        // Act
        mixer_tick(v_0, tetha_i0);
    }
}

void FWD_2c()
{
    odom_reset();
    while (true)
    {
        // Timer
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
            ;
        timer = micros();

        // Sense
        odom_tick();
        // Plan
        v_0 = MAX_VEL;
        tetha_i0 = 0;

        if (odom_get_S() > (CELL_WIDHT * 2))
        {
            return;
        }
        // Act
        mixer_tick(v_0, tetha_i0);
    }
}

void FWD_5c()
{
    odom_reset();
    while (true)
    {
        // Timer
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
            ;
        timer = micros();

        // Sense
        odom_tick();
        // Plan
        v_0 = MAX_VEL;
        tetha_i0 = 0;

        if (odom_get_S() > (CELL_WIDHT * 5))
        {
            return;
        }
        // Act
        mixer_tick(v_0, tetha_i0);
    }
}

void SS90IL()
{
    odom_reset();
    while (true)
    {
        // Timer
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
            ;
        timer = micros();

        // Sense
        odom_tick();
        // Plan
        v_0 = 0;
        tetha_i0 = MAX_ANG_VEL;
        if (odom_get_theta() > M_PI / 2)
        {
            return;
        }
        // Act
        mixer_tick(v_0, tetha_i0);
    }
}

void SS90IR()
{
    odom_reset();
    while (true)
    {
        // Timer
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
            ;
        timer = micros();

        // Sense
        odom_tick();
        // Plan
        v_0 = 0;
        tetha_i0 = -MAX_ANG_VEL;
        if (odom_get_theta() > (-1*(M_PI / 2)))
        {
            return;
        }
        // Act
        mixer_tick(v_0, tetha_i0);
    }
}