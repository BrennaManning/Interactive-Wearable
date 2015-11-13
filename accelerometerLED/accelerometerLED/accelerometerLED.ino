const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int OutPin = 11; // Analog output pin that the LED is attached to
const int voltageCorrection = 170;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)


void setup() {
  
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin); 
  
  
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255); 
  outputValue = abs(outputValue - voltageCorrection); 
  if (outputValue < 20){
  outputValue = 0;
  }
  
  
  // change the analog out value:
  analogWrite(OutPin, outputValue);           

  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t output = ");      
  Serial.println(outputValue);   

  // delay between readings
  delay(2);                     
}
