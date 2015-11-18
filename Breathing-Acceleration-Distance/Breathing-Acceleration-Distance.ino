// Define constants
int brightness = 255;
int power = 1000;
int count = 0;

int breathing_sensor_value = 0;
int distance_sensor_value = 0;
int accelerometer_sensor_value = 0;

int breathing_lights_ouput = 0;        // value output to the PWM (analog out)
int distance_motor_output = 0;        // value output to the PWM (analog out)
int accel_vibration_output = 0;        // value output to the PWM (analog out)

unsigned long time;

// Define output pins (PWM)
const int breathing_lights_out_pin = 3;
const int distance_motor_out_pin = 5;
const int accelerometer_motor_out_pin = 6;

// Define input pins
const int breathing_in_pin = A0;
const int distance_in_pin = A1;
const int accel_in_pin = A2;


void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  pinMode(breathing_lights_out_pin, OUTPUT);
  pinMode(distance_motor_out_pin, OUTPUT);
  pinMode(accelerometer_motor_out_pin, OUTPUT);
}

// takes in current breathing sensor in mV and returns our output in mV (0-5000)
// TODO: IMPLEMENT THIS LOGIC
int get_breathing_out(int breathing_in)
{
  int output_value = breathing_in;
  return output_value;
}

// takes in current distance sensor in mV and returns our output in mV (0-5000)
// TODO: IMPLEMENT THIS LOGIC
int get_distance_out(int distance_in)
{
  int output_value = distance_in;
  return output_value;
}

// takes in current accelerometer sensor in mV and returns our output in mV
// (0-5000)
// TODO: IMPLEMENT THIS LOGIC
int get_accel_out(int accel_in)
{
  int output_value = accel_in;
  return output_value;
}

void set_outputs(int breathing_out, int distance_out, int accel_out)
{
  analogWrite(breathing_lights_out_pin, map(breathing_out, 0, 5000, 0, 255));
  analogWrite(distance_motor_out_pin, map(distance_out, 0, 5000, 0, 255));
  analogWrite(accelerometer_motor_out_pin, map(accel_out, 0, 5000, 0, 255));
}

void loop() {

  time = millis();

  // read the analog in value and covert them to millivolts:
  breathing_sensor_value = map(analogRead(breathing_in_pin), 0, 1023, 0, 5000);
  distance_sensor_value = map(analogRead(distance_in_pin), 0, 1023, 0, 5000);
  accelerometer_sensor_value = map(analogRead(accel_in_pin), 0, 1023, 0, 5000);

  // get the output values we want to send to the breathing lights, the distance
  // motors, and the accelerometer motors. These values range from 0-5000 mV

  breathing_lights_ouput = get_breathing_out(breathing_sensor_value);
  distance_motor_output = get_distance_out(distance_sensor_value);
  accel_vibration_output = get_accel_out(accelerometer_sensor_value);

  set_outputs(breathing_lights_ouput, distance_motor_output,
              accel_vibration_output);

  delay(20);
}
