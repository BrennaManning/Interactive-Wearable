#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(4);

// Define constants
int brightness = 255;
int power = 1000;
int count = 0;
int beat_pre_death = 10;
int beat_length;
int breath_length;
int beats_while_dieing = 5;

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

unsigned long time;

// Define pins
const int lights = 6;
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to


void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(0);
  myMotor->run(FORWARD);

  myMotor1->setSpeed(0);
  myMotor1->run(FORWARD);

  myMotor2->setSpeed(0);
  myMotor2->run(FORWARD);

  myMotor3->setSpeed(0);
  myMotor3->run(FORWARD);

  // Define pin modes
  beat_length = 1000;
  pinMode(lights, OUTPUT);
}

void beat(int beat_length)
{
  int phase = time % beat_length;
  int write_value = 0;
  if (phase < beat_length / 10)
  {
  } else if (phase < 3 * beat_length / 20)
  {
    write_value = brightness;
  } else if (phase < 19 * beat_length / 20)
  {
  } else {
    write_value = brightness;
  }
  analogWrite(lights, write_value);

}

void breath(int reading)
{
  int motor_speed = map(reading, 0, 5000, 0, 70);
  Serial.println(motor_speed);


  myMotor->setSpeed(motor_speed);
  myMotor1->setSpeed(motor_speed);
  myMotor2->setSpeed(motor_speed);
  myMotor3->setSpeed(motor_speed);
}


void loop() {
  time = millis();
  beat_length = 1000;

  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 5000);
  beat(beat_length);
  breath(outputValue);
  delay(20);
}
