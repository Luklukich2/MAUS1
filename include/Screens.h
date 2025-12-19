#pragma once

#include "argviz.h"
#include "Encoder.h"
#include "Mixer.h"
#include "Servo_motor.h"
#include "VE.h"
#include "voltage_sensor.h"
#include "fnSelector.h"
#include "Odometer.h"
#include "ASMR.h"

int left_u = 0;
int right_u = 0;

float tetha_i0 = 0;
float v_0 = 0;

SCREEN(volts,
       {
           ROW("Vbatt [mv]: %d", int(vs_get_v_batt() * 1000));
           CLICK_ROW(
               [](CLICK_STATE state)
               {
                   switch (state)
                   {
                   case CLICK_LEFT:
                       left_u--;
                       break;
                   case CLICK_RIGHT:
                       left_u++;
                       break;
                   case CLICK_DOWN:
                       left_u++;
                       break;
                   default:
                       break;
                   }
               },
               "left u [V]: %d", left_u)
           CLICK_ROW(
               [](CLICK_STATE state)
               {
                   switch (state)
                   {
                   case CLICK_LEFT:
                       right_u--;
                       break;
                   case CLICK_RIGHT:
                       right_u++;
                       break;
                   case CLICK_DOWN:
                       right_u++;
                       break;
                   default:
                       break;
                   }
               },
               "right u [V]: %d", right_u)
       })
SCREEN(encoders,
       {
           ROW("Left phi[deg]: %d", (int)(enc_l_get_phi() * 180 / M_PI));
           ROW("Right phi[deg]: %d", (int)(enc_r_get_phi() * 180 / M_PI));
           ROW("Left w [deg/s]: %d", (int)(ve_l_get_w_est_f() * 1000));
           ROW("Right w [deg/s]: %d", (int)(ve_r_get_w_est_f() * 1000));
           ROW("fn_select[]: %d", fns_tick(analogRead(FN_SELECTOR_PIN)));
       })

SCREEN(mixer,
       {CLICK_ROW([](CLICK_STATE state)
                  {
        switch (state)
        {
        case CLICK_LEFT:
            tetha_i0 -= 0.1;
            break;
        case CLICK_RIGHT:
            tetha_i0 += 0.1;
            break;
        case CLICK_DOWN:
            tetha_i0 = 0;
            break;
        default:
            break;
        } },
                  "tetha_i0: %s", String(tetha_i0).c_str())
            CLICK_ROW([](CLICK_STATE state)
                      {
            switch (state)
            {
            case CLICK_LEFT:
               v_0 -= 0.1;
                break;
            case CLICK_RIGHT:
                v_0 += 0.1;
                break;
            case CLICK_DOWN:
                v_0 = 0;
                break;
            default:
                break;
            } },
                      "v_0: %s", String(v_0).c_str())
                ROW("odom_S: %s", String(odom_get_S()).c_str())
                    ROW("odom_theta: %s", String(odom_get_theta()).c_str())})
SCREEN(asmr,

       {
        ROW("prog_couter %d", asmr_get_prog_counter())
       })