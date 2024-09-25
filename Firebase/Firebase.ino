/*
Project: IoT Made Easy
Author: Mukesh Sankhla
Website: https://www.makerbrains.com
GitHub: https://github.com/MukeshSankhla
Social Media: Instagram @mukesh.diy
*/

#include <WiFi.h>
#include <FirebaseESP32.h>

#define FIREBASE_HOST "https://test-4c3e7-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "68ALoBhe16PQxLZxeq2CAm1P476T37jUDINCEIgD"

char ssid[] = "Makerbrains";
char pass[] = "Balaji2830";

FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

int soilMoisturePin = A4;  // Pin connected to the soil moisture sensor
int pumpPin = 2;           // Pin connected to the pump (relay)

void setup() {
  Serial.begin(115200);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);  // Keep pump off by default

  WiFi.begin(ssid, pass);

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  // Assign Firebase configuration and authentication
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Initial read to check connection and pump state from Firebase
  if (Firebase.getInt(firebaseData, "/pumpState")) {
    if (firebaseData.dataType() == "int") {
      Serial.print("Pump State: ");
      Serial.println(firebaseData.intData());
    }
  } else {
    Serial.println("Failed to get pump state from Firebase");
  }
}

void loop() {
  // Read soil moisture sensor data
  int soilMoistureValue = analogRead(soilMoisturePin);
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);

  // Upload soil moisture data to Firebase
  if (Firebase.setInt(firebaseData, "/sensorData/soilMoisture", soilMoistureValue)) {
    Serial.println("Soil moisture value uploaded");
  } else {
    Serial.println("Failed to upload soil moisture value");
  }

  // Read the pump state from Firebase
  if (Firebase.getInt(firebaseData, "/pumpState")) {
    int pumpState = firebaseData.intData();

    // Control the pump based on the Firebase value
    if (pumpState == 1) {
      digitalWrite(pumpPin, HIGH); // Turn pump ON
      Serial.println("Pump is ON");
    } else {
      digitalWrite(pumpPin, LOW);  // Turn pump OFF
      Serial.println("Pump is OFF");
    }
  } else {
    Serial.println("Failed to get pump state from Firebase");
  }

  delay(2000);  // Delay before the next update
}
