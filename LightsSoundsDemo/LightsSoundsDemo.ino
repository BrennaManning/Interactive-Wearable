// Define constants
int power = 1000;
int time = 1000;
int count = 0;
int beat_pre_death = 10;
int beat_length;
int beats_while_dieing = 5;

// Define pins
int speaker = 8;
int lights = 6;

void setup() {
  // Define pin modes
  beat_length = 1000;
  pinMode(lights, OUTPUT);
}

void beat(int beat_length)
{
  tone(speaker, power);
  digitalWrite(lights, 1);
  delay(beat_length / 10);
  noTone(speaker);
  digitalWrite(lights, 0);
  delay(15 * beat_length / 20);
  tone(speaker, power);
  digitalWrite(lights, 1);
  delay(1 * beat_length / 10);
  noTone(speaker);
  digitalWrite(lights, 0);
  delay(1 * beat_length / 20);
}


void loop() {
  
  byte beat_num = 0;
  beat_length = 1000;
  while (beat_num < beat_pre_death)
  {
    beat(beat_length);
    beat_num += 1;
  }
  beat_num = 0;
  while(beat_num < beats_while_dieing)
  {
    beat(beat_length);
    beat_num += 1;
    beat_length -= 100;
  }
  
  // Create constant light and sound
  tone(speaker, power);
  digitalWrite(lights, 0);
  delay(3000);
}
