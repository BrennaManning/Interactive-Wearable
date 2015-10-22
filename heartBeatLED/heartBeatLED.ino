unsigned long startTime;

byte num_seconds = 4;
int sleepTime = 50; // ms, read 20 times per second

const int numReadings = 80; // TODO: THIS SHOULDNT BE HARDCODED

int inPin = A0;    // select the input pin for the potentiometer
int ledPin = 12;  // select the pin for the LED

int voltage; // variable to store read-in

int readings[numReadings];
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  Serial.begin(9600);
}

void loop() {

  // get the start time
  startTime = millis();

  // subtract the last reading:
  total = total - readings[readIndex];

  // read the value from the sensor and map to mV
  voltage = analogRead(inPin);
  voltage = map(voltage, 0, 1023, 0, 5000);

  //
  readings[readIndex] = voltage;
  total = total + voltage;
  readIndex = readIndex + 1;
    // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  average = total / numReadings;
  Serial.print("Current reading: ");
  Serial.print(voltage);
  Serial.print("...Average: ");
  Serial.println(average);

  float beat_cuttoff = average;

  //When should lights turn on:
  if (voltage > beat_cuttoff)
  {
  digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }

  // the amount of time this loop cycle took to run
  int runTime = (millis() - startTime);

  // take the runtime into account
  delay(max(sleepTime - runTime, 0));
}
