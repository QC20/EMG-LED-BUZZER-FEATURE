const int emgPin = A0;
const int ledPin = 13;
const int buzzerPin = 8;

bool isArmed = false;
int tenseCount = 0;
unsigned long lastTenseTime = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int emgValue = analogRead(emgPin);
  unsigned long currentTime = millis();

  if (emgValue > 560) { // << YOU MIGHT WANT TO CHANGE THIS VALUE
    if (!isArmed) {
      // Arm the system if it's not already armed
      isArmed = true;
      tenseCount = 1;
      lastTenseTime = currentTime;
    } else if (currentTime - lastTenseTime <= 1500) {
      // If already armed, count the number of consecutive tenses within 1.5 seconds
      tenseCount++;
      lastTenseTime = currentTime;

      if (tenseCount == 2) {
        // Two consecutive tenses within 1.5 se conds, rapid blink for 3 seconds
        rapidBlinkLED();
      }
    } else {
      // Reset the tense count if more than 1.5 seconds have passed since the last tense
      tenseCount = 1;
      lastTenseTime = currentTime;
    }
  } else {
    // Disarm the system if EMG value is below the threshold
    isArmed = false;
    
  }

  Serial.println(emgValue);

  delay(100);
}

void rapidBlinkLED() {
  unsigned long startTime = millis();

  // Blink the LED rapidly for 3 seconds
  while (millis() - startTime <= 3000) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }

void giveBuzz() {
  digitalWrite(buzzerPin, HIGH);
  delay(50);
  digitalWrite(buzzerPin, LOW);
}

}
