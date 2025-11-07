#pragma once

#include "Encoder.h"
#include "Config.h"

float ve_l_w_est = 0;
float ve_r_w_est = 0;
float ve_l_w_est_f = 0;
float ve_r_w_est_f = 0;

void ve_init()
{}

void ve_l_tick(float l_phi)
{
    static float l_phi_old = l_phi;
    float dphi = l_phi - l_phi_old;
    ve_l_w_est = dphi / Ts_s;
    l_phi_old = l_phi;

    // low pass filter
    static float I = 0;
    float c = ve_l_w_est - ve_l_w_est_f;
    float s = c / VE_LPF_T;
    I += s * Ts_s;
    ve_l_w_est_f = I;
}

void ve_r_tick(float r_phi)
{
    static float r_phi_old = r_phi;
    float dphi = r_phi - r_phi_old;
    ve_r_w_est = dphi / Ts_s;
    r_phi_old = r_phi;

    // low pass filter
    static float I = 0;
    float c = ve_r_w_est - ve_r_w_est_f;
    float s = c / VE_LPF_T;
    I += s * Ts_s;
    ve_r_w_est_f = I;
}

float ve_l_get_w_est_f()
{
    return ve_l_w_est_f;
}

float ve_r_get_w_est_f()
{
    return ve_r_w_est_f;
}