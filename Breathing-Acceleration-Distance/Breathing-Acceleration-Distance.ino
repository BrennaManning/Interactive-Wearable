
// Define constants
int brightness = 255;
int power = 1000;
int count = 0;

int distance_sensor_value = 0;
int accelerometer_sensor_value = 0;

int distance_motor_output = 0;        // value output to the PWM (analog out)
int accel_speaker_output = 0;        // value output to the PWM (analog out)

int tone_threshold = 250; // voltage diff at which to play a tone
int max_volume_voltage = 1000; // voltage at which to play the highest pitch
                               // tone

int low_speaker_tone = 50;
int high_speaker_tone = 250;

unsigned long time;

// Define output pins (PWM)
const int distance_motor_out_pin = 5;
const int accelerometer_speaker_out_pin = 6;

// Define input pins
const int distance_in_pin = A1;
const int accel_in_pin = A2;


void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  pinMode(distance_motor_out_pin, OUTPUT);
  pinMode(accelerometer_speaker_out_pin, OUTPUT);
}


// takes in current distance sensor in mV and returns our output in mV
int get_distance_out(int distance_in)
{
  // input of 0 corresponds to 1.4 V. Input of 2.75 V correponds to 5 V.
  // This is because with the transistor, 1.4 V converts to 2.5 V, and the motor
  // will not vibrate. 5 V maps to 9V, and it vibrates fast.
  int output_value = (distance_in, 0, 2750, 1389, 5000);
  return min(output_value, 5000);
}

// takes in current accelerometer sensor in mV and returns our output tone.
// 0 for no tone, and 50-250 otherwise
int get_accel_tone(int accel_in)
{
  int diff = abs(accel_in - 2500);
  int output_value = 0;
  if (diff > tone_threshold)
  {
    output_value = map(diff, tone_threshold, max_volume_voltage,
                       low_speaker_tone, high_speaker_tone);
  }
  return min(output_value, high_speaker_tone);
}

void set_outputs(int distance_out, int accel_tone)
{
  analogWrite(distance_motor_out_pin, map(distance_out, 0, 5000, 0, 255));
  if (accel_tone != 0)
  {
    tone(accel_speaker_output, accel_tone);
  }
  else
  {
    noTone(accel_speaker_output);
  }
}

void loop() {

  time = millis();

  // read the analog in value and covert them to millivolts:
  distance_sensor_value = map(analogRead(distance_in_pin), 0, 1023, 0, 5000);
  accelerometer_sensor_value = map(analogRead(accel_in_pin), 0, 1023, 0, 5000);

  // get the output values we want to send to the breathing lights, the distance
  // motors, and the accelerometer motors. These values range from 0-5000 mV

  distance_motor_output = get_distance_out(distance_sensor_value);
  accel_speaker_output = get_accel_tone(accelerometer_sensor_value);

  set_outputs(distance_motor_output,
              accel_speaker_output);

  delay(1000);
}
