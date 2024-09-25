/*
Project: IoT Made Easy
Author: Mukesh Sankhla
Website: https://www.makerbrains.com
GitHub: https://github.com/MukeshSankhla
Social Media: Instagram @mukesh.diy
*/

int ledPin = 2; // Define the pin connected to LED

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin mode to output
}

void loop() {
  digitalWrite(ledPin, HIGH); // Turn the LED on
  delay(1000);                // Wait for 1 second
  digitalWrite(ledPin, LOW);  // Turn the LED off
  delay(1000);                // Wait for 1 second
}
