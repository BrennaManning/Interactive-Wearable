// Define constants
int power = 1000;
int time = 250;
int count = 0;

// Define pins
int speaker = 8;
int lights = 5;

void setup() {
  // Define pin modes
  pinMode(lights, OUTPUT);
}

void loop() {
  // Slowly increase rate of toggling
  while (time > 110) {
    tone(speaker, power);
    digitalWrite(lights, 0);
    delay(100);
    noTone(speaker);
    digitalWrite(lights, 1);
    delay(time-100);
    tone(speaker, power);
    digitalWrite(lights, 0);
    delay(100);
    noTone(speaker);
    digitalWrite(lights, 1);
    delay(time*4-100);
    time -= 10;
  }
  
  // Create constant light and sound
  tone(speaker, power);
  digitalWrite(lights, 0);
}
