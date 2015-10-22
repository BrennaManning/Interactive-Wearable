unsigned long time;
byte sleepTime = 40;

int inPin = A0;    // select the input pin for the potentiometer
int ledPin1 = 12;// select the pin for the LED
int ledPin2 = 11;// select pin for second LED
int val = 0;
float voltage = 0.00;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  time = millis();
  // read the value from the sensor:
  val = analogRead(inPin);
  float voltage = map(val, 0, 1023, 0, 5000);
  // turn the ledPin on
  voltage = voltage/1000;
  Serial.println(voltage);

  // TODO: IMPLEMENT MOVING AVERAGE CODE AND UPDATE DIGITAL WRITES TO CORRECT
  // PINS
  float heartbeat0 = 2;
  float heartbeat1 = 1;

  //When should lights turn on:
  if (voltage > heartbeat0)
  {
  digitalWrite(ledPin1, HIGH);
  }
  else
  {
    digitalWrite(ledPin1, LOW);
  }
  if (voltage > heartbeat1)
  {
    digitalWrite(ledPin2, HIGH);
  }
  else
  {
    digitalWrite(ledPin2, LOW);
  }
  delay(sleepTime - (millis() - time));
}
