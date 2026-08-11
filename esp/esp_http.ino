
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include "heartRate.h"
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// --------- WiFi settings ----------
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASS";
String serverUrl = "http://YOUR_BACKEND_IP:5000/predict"; // replace with PC IP

// ----------------------- DHT11 -----------------------
#define DHTPIN 18
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ----------------------- DS18B20 ---------------------
#define DS18B20_PIN 4
OneWire oneWire(DS18B20_PIN);
DallasTemperature dsSensors(&oneWire);

// ----------------------- MAX30102 --------------------
MAX30105 particleSensor;

#define BUFFER_SIZE 100
uint32_t irBuffer[BUFFER_SIZE];
uint32_t redBuffer[BUFFER_SIZE];

unsigned long lastDHTRead = 0;
unsigned long lastDS18Read = 0;

float tempRoom = 0;
float hum = 0;
float skinTemp = 0;

void sendToServer(int hr, int spo2, float bodyTemp, float ambientTemp) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
    String payload = "{\"heart_rate\": " + String(hr) + 
                     ", \"spo2\": " + String(spo2) +
                     ", \"body_temp\": " + String(bodyTemp, 2) +
                     ", \"ambient_temp\": " + String(ambientTemp, 2) + "}";
    int code = http.POST(payload);
    if (code > 0) {
      String resp = http.getString();
      Serial.println("Server response:");
      Serial.println(resp);
    } else {
      Serial.print("POST failed, error: ");
      Serial.println(code);
    }
    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP: ");
  Serial.println(WiFi.localIP());

  dht.begin();
  dsSensors.begin();
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30102 not found");
    while (1);
  }
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x1F);
  particleSensor.setPulseAmplitudeIR(0x1F);
  Serial.println("Sensors ready");
}

void loop() {
  // Fill pulse buffers
  for (int i = 0; i < BUFFER_SIZE; i++) {
    irBuffer[i] = particleSensor.getIR();
    redBuffer[i] = particleSensor.getRed();
    delay(10);
  }

  if (millis() - lastDHTRead > 2000) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t)) tempRoom = t;
    if (!isnan(h)) hum = h;
    lastDHTRead = millis();
  }

  if (millis() - lastDS18Read > 1000) {
    dsSensors.requestTemperatures();
    skinTemp = dsSensors.getTempCByIndex(0);
    lastDS18Read = millis();
  }

  int32_t spo2;
  int8_t validSPO2;
  int32_t heartRate;
  int8_t validHR;
  maxim_heart_rate_and_oxygen_saturation(
      irBuffer, BUFFER_SIZE,
      redBuffer, &spo2, &validSPO2,
      &heartRate, &validHR
  );

  Serial.print("HR: "); Serial.print(validHR ? heartRate : 0);
  Serial.print(" SpO2: "); Serial.print(validSPO2 ? spo2 : 0);
  Serial.print(" SkinT: "); Serial.print(skinTemp);
  Serial.print(" RoomT: "); Serial.println(tempRoom);

  if (validHR && validSPO2 && skinTemp > -50) {
    sendToServer(heartRate, spo2, skinTemp, tempRoom);
  }

  delay(2000);
}
