 #include <Servo.h>

 Servo servo_L;
 Servo servo_R;

 int servo_L_pos = 0;
 int servo_R_pos = 0;

// Define constants
int brightness = 255;
// int power = 1000;
// int count = 0;

int distance_sensor_value = 0;
int accelerometer_sensor_value = 0;
// int breathing_sensor_value = 0;

int servo_out = 0;        // value output to the PWM (analog out)
int accel_leds_out = 0;        // value output to the PWM (analog out)

int accel_threshold = 500; // voltage diff at which to turn LEDs on.
int distance_threshold = 250; // voltage diff at which to turn LEDs on.

unsigned long time;

// Define output pins (PWM)
const int servo_out_pin_L = 9;
const int servo_out_pin_R = 10;
const int accel_leds_out_pin = 6;

// Define input pins
const int distance_in_pin = A1;
const int accel_in_pin = A4;
const int breathing_in_pin = A5;


void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  servo_L.attach(servo_out_pin_L);
  servo_R.attach(servo_out_pin_R);
  pinMode(accel_leds_out_pin, OUTPUT);
}


// takes in current distance sensor in mV and returns the position of the servos.
int get_distance_out(int distance_in)
{
  int output_value = 0;
  if (distance_in < 250)
  {
    if (time % 5000 < 2000)
    {
      int difference = 1000 - abs(time % 5000 - 1000);
      output_value = map(difference, 0, 1000, 0, 60);
    }
    else
    {
      int period = map(distance_in, 250, 2000, 1500, 750);
      int difference = period / 2 - abs(time % period - period / 2);
      output_value = map(difference, 0, period / 2, 0, 60);
    }
  }

}

// takes in current accelerometer sensor in mV and the output for the LEDs.
// If the object is moving fast, then the LEDs flicker.
int get_accel_out(int accel_in)
{
  int diff = abs(accel_in - 2500);
  int output_value = 0;
  if (diff > accel_threshold)
  {
    // this causes output to flicker twice a second.
    if (time % 500 < 400) {
      output_value = 5000;
    }

  }
  return output_value;
}

void set_outputs(int servo_out, int accel_leds)
{
  analogWrite(accel_leds_out_pin, map(accel_leds, 0, 5000, 0, brightness));
  servo_R.write(servo_out);
  servo_L.write(servo_out);

}

void loop() {

  time = millis();

  // read the analog in value and covert them to millivolts:
  distance_sensor_value = map(analogRead(distance_in_pin), 0, 1023, 0, 5000);
  accelerometer_sensor_value = map(analogRead(accel_in_pin), 0, 1023, 0, 5000);
  // breathing_sensor_value = map(analogRead(breathing_sensor_value), 0, 1023, 0, 5000);

  Serial.print("Accelerometer value: ");
  Serial.print(accelerometer_sensor_value);
  Serial.print(". Distance value: ");
  Serial.println(distance_sensor_value);

  servo_out = get_distance_out(distance_sensor_value);
  accel_leds_out = get_accel_out(accelerometer_sensor_value);

  set_outputs(servo_out,
              accel_leds_out);

  delay(100);
}
