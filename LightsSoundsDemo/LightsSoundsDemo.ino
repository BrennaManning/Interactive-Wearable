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
int brightness = 20;
int power = 1000;
int count = 0;
int beat_pre_death = 10;
int beat_length;
int breath_length;
int beats_while_dieing = 5;

unsigned long time;

// Define pins
int speaker = 8;
int lights = 6;

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
  if (phase < beat_length / 10)
  {
    noTone(speaker);
    digitalWrite(lights, 0);
  } else if (phase < 3 * beat_length / 20)
  {
    tone(speaker, power);
    analogWrite(lights, brightness);
  } else if (phase < 19 * beat_length / 20)
  {
    noTone(speaker);
    digitalWrite(lights, 0);
  } else {
    tone(speaker, power);
    analogWrite(lights, brightness);
  }
}

void breath(int breath_length)
{
  long phase = time % breath_length;
  int m_speed;
  if (phase < 2 * breath_length / 4)
  {
    m_speed = 100 * phase / (2 * breath_length / 4);
  } else
  {
    long exhale_time = breath_length - phase;
    m_speed = 100 * exhale_time / (2 * breath_length / 4);
  }
  myMotor->setSpeed(m_speed);
  myMotor1->setSpeed(m_speed);
  myMotor2->setSpeed(m_speed);
  myMotor3->setSpeed(m_speed);
  Serial.print("Commanding motors to :");
  Serial.println(m_speed);
}


void loop() {

  time = millis();

  // byte beat_num = 0;
  beat_length = 1000;
  beat(beat_length);
  breath_length = 6000;
  breath(breath_length);
  // while(beat_num < beat_pre_death + beats_while_dieing)
  // {
  //   beat(beat_length);
  //   beat_num += 1;
  //   beat_length -= 100;
  // }

  // Create constant light and sound
  // tone(speaker, power);
  // digitalWrite(lights, 0);
  // delay(3000);
//  myMotor->run(RELEASE);
//  myMotor1->run(RELEASE);
//  myMotor2->run(RELEASE);
//  myMotor3->run(RELEASE);
}
