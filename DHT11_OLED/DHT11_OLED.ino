/*
Project: IoT Made Easy
Author: Mukesh Sankhla
Website: https://www.makerbrains.com
GitHub: https://github.com/MukeshSankhla
Social Media: Instagram @mukesh.diy
*/

#include <DHT11.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT11 dht11(5); // DHT11 sensor connected to pin 5

void setup() {
  Serial.begin(115200);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is the I2C address of the OLED display
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Infinite loop to stop execution
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void loop() {
  int temperature, humidity;

  // Attempt to read the temperature and humidity values from the DHT11 sensor
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  // Check the results of the readings
  if (result == 0) {
    // Display the temperature and humidity on the OLED
    display.clearDisplay();
    display.setCursor(0, 0); // Set the cursor position at the top-left of the screen
    display.print(temperature);
    display.println(" *C");
    display.setCursor(0, 20);
    display.print(humidity);
    display.println(" %");
    display.display(); // Update the OLED display with the new data
    
    // Also print to Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("*C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  } else {
    Serial.println("Failed to read from DHT11 sensor!");
  }
  
  delay(2000); // Wait for 2 seconds before reading again
}
