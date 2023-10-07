#include <Arduino.h>

const int redPin = 9;    // Red LED connected to digital pin 9
const int greenPin = 10; // Green LED connected to digital pin 10
const int bluePin = 11;  // Blue LED connected to digital pin 11
const int potPin = A0;   // Potentiometer connected to analog pin A0

int redValue = 0;    // Red LED intensity (0-255)
int greenValue = 0;  // Green LED intensity (0-255)
int blueValue = 0;   // Blue LED intensity (0-255)
int potReading = 0;  // Potentiometer reading (0-1023)

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Read potentiometer value
  potReading = analogRead(potPin);

  // Map potentiometer value to LED intensities
  redValue = map(potReading, 0, 1023, 0, 255);
  greenValue = map(potReading, 0, 1023, 0, 255);
  blueValue = map(potReading, 0, 1023, 0, 255);

  // Set LED colors using PWM
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);

  // Check for serial commands
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'r': // Turn on Red LED
        redValue = 255;
        greenValue = 0;
        blueValue = 0;
        break;
      case 'g': // Turn on Green LED
        redValue = 0;
        greenValue = 255;
        blueValue = 0;
        break;
      case 'b': // Turn on Blue LED
        redValue = 0;
        greenValue = 0;
        blueValue = 255;
        break;
      case 'o': // Turn off all LEDs
        redValue = 0;
        greenValue = 0;
        blueValue = 0;
        break;
      default:
        break;
    }
    
    // Set LED colors using PWM based on the serial command
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
  }
}
