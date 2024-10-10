#include <Wire.h>


const int buttonPin = 12;  // the number of the pushbutton pin
const int ledPin = 8;    // the number of the LED pin
const int masterInterruptPin = 10; // pin to trigger the interrupt in the master


int ledState = HIGH;        // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(masterInterruptPin, OUTPUT);

  digitalWrite(ledPin, ledState);
  Wire.begin(1)
  Serial.begin(9600);
  Wire.onRequest(giveData);
}



void giveData() {
  Wire.write("231");
}

void loop() {

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    Serial.println("Switch");
    
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        ledState = !ledState;

        digitalWrite(masterInterruptPin, HIGH);
      }
    }
  }
  // set the LED:
  digitalWrite(ledPin, ledState);

  lastButtonState = reading;
}