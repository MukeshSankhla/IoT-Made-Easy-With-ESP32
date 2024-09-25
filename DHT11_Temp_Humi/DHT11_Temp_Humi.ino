/*
Project: IoT Made Easy
Author: Mukesh Sankhla
Website: https://www.makerbrains.com
GitHub: https://github.com/MukeshSankhla
Social Media: Instagram @mukesh.diy
*/

#include <DHT11.h>

DHT11 dht11(5); // DHT11 sensor connected to pin 5

void setup() {
  Serial.begin(115200);
}

void loop() {
    int temperature, humidity;

    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    int result = dht11.readTemperatureHumidity(temperature, humidity);

    // Check the results of the readings.
    // If the reading is successful, print the temperature and humidity values in CSV format.
    if (result == 0) {
        Serial.print("Temperature:");
        Serial.print(temperature);
        Serial.print("*C");
        Serial.print(", Humidity:");
        Serial.print(humidity);
        Serial.println("%");
    }
}
