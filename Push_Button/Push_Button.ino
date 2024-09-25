/*
Project: IoT Made Easy
Author: Mukesh Sankhla
Website: https://www.makerbrains.com
GitHub: https://github.com/MukeshSankhla
Social Media: Instagram @mukesh.diy
*/

int ledPin = 2;        // Pin connected to the LED
int buttonPin = 4;     // Pin connected to the push button
int buttonState = 0;   // Variable to store the button state
int ledState = LOW;    // Variable to store the LED state

void setup() {
  pinMode(ledPin, OUTPUT);      // Set the LED pin as output
  pinMode(buttonPin, INPUT);    // Set the button pin as input
  Serial.begin(115200);
}

void loop() {
  // Read the state of the button
  buttonState = digitalRead(buttonPin);

  // Check if the button is pressed
  if (buttonState == HIGH) {
    // Toggle the LED state
    ledState = !ledState;

    // Update the LED to the new state
    digitalWrite(ledPin, ledState);

    // Debounce delay to avoid multiple reads from a single press
    delay(300);  // Adjust this value if necessary
  }

  // Print the current state of the LED for debugging
  Serial.print("LED is: ");
  if (ledState == HIGH) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  delay(50);  // Short delay to stabilize reading
}
