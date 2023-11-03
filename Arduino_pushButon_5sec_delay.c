#include <Arduino.h>
const int buttonPin = 2;
const int ledPin = 13;
int buttonState = 0;
int previousButtonState = 0;
const int debounceTime = 500;
unsigned long startTime = 0;
unsigned long currentTime = 0;
void setup() 
{
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != previousButtonState) 
  {
    previousButtonState = buttonState;
    if (buttonState == HIGH) {
      startTime = millis();
    }
  }
  if (millis() - startTime >= 5000) 
  {
    digitalWrite(ledPin, HIGH);
  } else 
  {
    digitalWrite(ledPin, LOW);
  }
}