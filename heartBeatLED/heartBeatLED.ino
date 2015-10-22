

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
  // read the value from the sensor:
  val = analogRead(inPin);    
  float voltage = map(val, 0, 1023, 0, 5.00);
  // turn the ledPin on
  Serial.println(voltage);
  
  if (val > 410)
  {
  digitalWrite(ledPin1, HIGH);  
  }
  else
  {
    digitalWrite(ledPin1, LOW);
  }
  if (val > 205)
  {
    digitalWrite(ledPin2, HIGH);
  }
  else
  {
    digitalWrite(ledPin2, LOW);
  }
}
