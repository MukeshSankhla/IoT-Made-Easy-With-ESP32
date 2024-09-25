/*
Project: IoT Made Easy
Author: Mukesh Sankhla
Website: https://www.makerbrains.com
GitHub: https://github.com/MukeshSankhla
Social Media: Instagram @mukesh.diy
*/

int soilSensorPin = A4; // Soil moisture sensor connected to pin A4/32

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 bps
}

void loop() {
  int sensorValue = analogRead(soilSensorPin); // Read the analog value
  Serial.print("Soil Moisture: ");
  Serial.println(sensorValue); // Print the value to the serial monitor
  delay(2000); // Wait for 2 seconds before next reading
}
