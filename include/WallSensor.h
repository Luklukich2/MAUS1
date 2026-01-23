#pragma once

#include "Arduino.h"
#include "Config.h"

int counter = 1;
uint32_t updateTime;
uint32_t updateInterval = 40; // (ms) do not make this smaller than 25ms for performance reasons

// the default values for the front sensor when the robot is backed up to a wall
const int FRONT_REFERENCE = 44;
// the default values for the side sensors when the robot is centred in a cell
const int LEFT_REFERENCE = 38;
const int RIGHT_REFERENCE = 49;

// the values above which, a wall is seen
const int FRONT_WALL_THRESHOLD = FRONT_REFERENCE / 20; // minimum value to register a wall
const int LEFT_WALL_THRESHOLD = LEFT_REFERENCE / 2;    // minimum value to register a wall
const int RIGHT_WALL_THRESHOLD = RIGHT_REFERENCE / 2;  // minimum value to register a wall

// working copies of the reference values
int gFrontReference = FRONT_REFERENCE;
int gLeftReference = LEFT_REFERENCE;
int gRightReference = RIGHT_REFERENCE;
int gFLeftReference = LEFT_REFERENCE;
int gFRightReference = RIGHT_REFERENCE;
// the current value of the sensors
volatile int gSensorFront;
volatile int gSensorLeft;
volatile int gSensorRight;
volatile int gFSensorLeft;
volatile int gFSensorRight;
// true f a wall is present
volatile bool gFrontWall;
volatile bool gLeftWall;
volatile bool gRightWall;
volatile bool gFLeftWall;
volatile bool gFRightWall;
// steering and turn position errors
volatile int gSensorFrontError; // zero when robot in cell centre
volatile float gSensorCTE;      // zero when robot in cell centre

void analogueSetup()
{
  // increase speed of ADC conversions to 28us each
  // by changing the clock prescaler from 128 to 16
  bitClear(ADCSRA, ADPS0);
  bitClear(ADCSRA, ADPS1);
  bitSet(ADCSRA, ADPS2);
}

/***
 * If you are interested in what all this does, the ATMega328P datasheet
 * has all the answers but it is not easy to follow until you have some
 * experience. For now just use the code as it is.
 */
void setupSystick()
{
  // set the mode for timer 2
  bitClear(TCCR2A, WGM20);
  bitSet(TCCR2A, WGM21);
  bitClear(TCCR2B, WGM22);
  // set divisor to 128 => timer clock = 125kHz
  bitSet(TCCR2B, CS22);
  bitClear(TCCR2B, CS21);
  bitSet(TCCR2B, CS20);
  // set the timer frequency
  OCR2A = 249; // (16000000/128/500)-1 = 249
  // enable the timer interrupt
  bitSet(TIMSK2, OCIE2A);
}

void updateSideWallSensor()
{
  // first read them dark
  int right = analogRead(A1);
  int left = analogRead(A2);
  // light them up
  digitalWrite(EMITTER_S, 1);
  // wait until all the detectors are stable
  delayMicroseconds(50);
  // now find the differences
  right = analogRead(A1) - right;
  left = analogRead(A2) - left;
  // and go dark again.
  digitalWrite(EMITTER_S, 0);

  gLeftWall = left > gLeftReference / 2;
  gRightWall = right > gRightReference / 2;
  // make the results available to the rest of the program
  gSensorLeft = left;
  gSensorRight = right;
}

void updateFrontWallSensors()
{
  // first read them dark
  int f_right = analogRead(A1);
  int f_left = analogRead(A2);
  // light them up
  digitalWrite(EMITTER_F, 1);
  // wait until all the detectors are stable
  delayMicroseconds(50);
  // now find the differences
  f_right = analogRead(A1) - f_right;
  f_left = analogRead(A2) - f_left;
  // and go dark again.
  digitalWrite(EMITTER_F, 0);

  gFLeftWall = f_left > gFLeftReference / 2;
  gFRightWall = f_right > gFRightReference / 2;
  // make the results available to the rest of the program
  gFSensorLeft = f_left;
  gFSensorRight = f_right;
}

ISR(TIMER2_COMPA_vect)
{
  if(counter%2 == 0)
  {
    updateFrontWallSensors();
  }
  if(counter)
  {
    updateSideWallSensor();
  }
  counter++;
}