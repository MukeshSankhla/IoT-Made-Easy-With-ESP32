/*
Project: IoT Made Easy
Author: Mukesh Sankhla
Website: https://www.makerbrains.com
GitHub: https://github.com/MukeshSankhla
Social Media: Instagram @mukesh.diy
*/

#define BLYNK_TEMPLATE_ID "**********"
#define BLYNK_TEMPLATE_NAME "*********"
#define BLYNK_AUTH_TOKEN "********"

char ssid[] = "*********";
char pass[] = "***********";

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT11.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ledPin = 2;
DHT11 dht11(5);

// Blynk function to control the LED via virtual pin V1
BLYNK_WRITE(V1) {
  int pinValue = param.asInt(); // Get value from the app
  digitalWrite(ledPin, pinValue); // Control LED
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

  // Start Blynk connection
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

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
  Blynk.run(); // Run Blynk connection

  // Read temperature and humidity every 2 seconds
  static unsigned long lastMillis = 0;
  if (millis() - lastMillis >= 2000) {
    lastMillis = millis();

    int result = dht11.readTemperatureHumidity(temperature, humidity);

    display.clearDisplay();
    display.setCursor(0, 0); // Set the cursor position at the top-left of the screen
    display.print(temperature);
    display.println(" *C");
    display.setCursor(0, 20);
    display.print(humidity);
    display.println(" %");
    display.display(); // Update the OLED display with the new data

    // Send temperature and humidity to Blynk app (V2 for temp, V3 for humidity)
    Blynk.virtualWrite(V2, temperature); // Send temperature to virtual pin V2
    Blynk.virtualWrite(V3, humidity);    // Send humidity to virtual pin V3

    // Print values to Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" *C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
}
