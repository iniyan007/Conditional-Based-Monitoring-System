#include <Wire.h>
#include <MPU6050.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h> 
#include <ArduinoJson.h>

MPU6050 accelgyro;

#define FIREBASE_HOST "tunnel-booster-fan-default-rtdb.firebaseio.com"  
#define FIREBASE_AUTH "AIzaSyDQ3HdzrxqS84AI0EgI-e_-hDGFjR8Opes"  
int16_t ax, ay, az;
float vibrationValue = 0;
const int analogPin = A0;
const float sensitivity = 5.0 / 1023.0;

float voltage;
float currentRMS;
int rawValue;
const float mVperAmp = 100.0;

volatile int pulseCount = 0;
unsigned long lastTime = 0;
int fanRPM = 0;
const int sensorPin = D5; 

const char* ssid = "iniyan";     
const char* password = "12345678"; 

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

void ICACHE_RAM_ATTR IRsensorISR() {
  pulseCount++;                
}

void setup() {
  Serial.begin(9600);
  
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(analogPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(sensorPin), IRsensorISR, FALLING);

  Wire.begin();
  accelgyro.initialize();
  
  if (!accelgyro.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi...");
  
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) { // 10 seconds timeout
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect to Wi-Fi");
    return; 
  }

  Serial.println("Connected to Wi-Fi.");

  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  unsigned long currentTime = millis();
  accelgyro.getAcceleration(&ax, &ay, &az);

  float accelX = ax / 16384.0;
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;

  vibrationValue = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);
  Serial.print("Vibration: ");
  Serial.println(vibrationValue);

  if (currentTime - lastTime >= 1000) {
    fanRPM = ((pulseCount * 60)/45);
    pulseCount = 0;
    lastTime = currentTime;
    Serial.print("Fan RPM: ");
    Serial.println(fanRPM);
  }

  long sum = 0;
  const int sampleCount = 500;
  
  for (int i = 0; i < sampleCount; i++) {
    rawValue = analogRead(analogPin);
    voltage = rawValue * sensitivity;
    float currentInstant = (voltage - 2.5) * (1000 / mVperAmp);
    sum += sq(currentInstant);
    delay(2);
  }

  currentRMS = sqrt(sum / sampleCount) - 21.35;  
  Serial.print("Current: ");
  Serial.print(currentRMS);
  Serial.println(" A");

  if (WiFi.status() == WL_CONNECTED) {
    if (Firebase.pushInt(firebaseData, "/sensorData/rpm", fanRPM)) {
      Serial.println("RPM data sent successfully");
    } else {
      Serial.println("Failed to send RPM data");
      Serial.println(firebaseData.errorReason());
    }
    if (Firebase.pushFloat(firebaseData, "/sensorData/vibration", vibrationValue)) {
      Serial.println("Vibration data sent successfully");
    } else {
      Serial.println("Failed to send Vibration data");
      Serial.println(firebaseData.errorReason());
    }
    if (Firebase.pushFloat(firebaseData, "/sensorData/current", currentRMS)) {
      Serial.println("Current data sent successfully");
    } else {
      Serial.println("Failed to send Current data");
      Serial.println(firebaseData.errorReason());
    }
  } else {
    Serial.println("WiFi Disconnected.");
  }

  delay(10000);
}
