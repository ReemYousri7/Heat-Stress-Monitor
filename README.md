# 🔥 Heat Stress Monitor

An AI-powered **Heat Stress Monitoring System** that combines **IoT, Machine Learning, FastAPI, ESP32, and Flutter** to monitor physiological and environmental parameters and predict heat-stress conditions in real time.

## 📌 Overview

Heat Stress Monitor is an intelligent IoT-based system designed to monitor physiological and environmental data and use Machine Learning to classify the user's heat-stress condition.

The system collects sensor readings through an **ESP32**, sends the data to a **FastAPI backend**, and uses a trained Machine Learning model to generate a heat-stress prediction.

The prediction can then be displayed through a **Flutter mobile application**.

## 🧠 Machine Learning

The Machine Learning model uses physiological and environmental features to classify the current condition into three categories:

- 🟢 **Safe**
- 🟡 **Heat Load**
- 🔴 **Heat Stress**

### Input Features

- ❤️ Heart Rate
- 🫁 SpO2
- 🌡️ Body Temperature
- 🌡️ Ambient Temperature

## 🏗️ System Architecture

```text
Sensors
   │
   ▼
ESP32
   │
   │ Wi-Fi / HTTP
   ▼
FastAPI Backend
   │
   ▼
Machine Learning Model
   │
   ▼
Heat Stress Prediction
   │
   ▼
Flutter Mobile App

🔌 Hardware

The project uses:

ESP32 — Main IoT controller
MAX30102 — Heart Rate & SpO2
DS18B20 — Temperature sensor
DHT11 — Ambient temperature & humidity
🛠️ Technologies
Artificial Intelligence
Machine Learning
Classification
Scikit-learn
Python
Backend
FastAPI
Uvicorn
Pydantic
NumPy
IoT
ESP32
MAX30102
DS18B20
DHT11
Wi-Fi
HTTP
Mobile Application
Flutter
Dart
📁 Project Structure
Heat-Stress-Monitor/
│
├── backend/
│   ├── main.py
│   ├── requirements.txt
│   ├── run.sh
│   └── HeatStress_Model_FIXED.pkl
│
├── esp/
│   └── esp_http.ino
│
├── flutter_app/
│   ├── lib/
│   │   └── main.dart
│   └── pubspec.yaml
│
├── .gitignore
└── README.md
⚙️ Backend Setup

Navigate to the backend directory:

cd backend

Install the required dependencies:

pip install -r requirements.txt

Run the FastAPI server:

uvicorn main:app --host 0.0.0.0 --port 5000

The API will be available at:

http://localhost:5000

Interactive API documentation:

http://localhost:5000/docs
🔗 API Endpoint
POST /predict

The backend receives sensor data and returns the predicted heat-stress condition.

Example request:

{
  "heart_rate": 75,
  "spo2": 98,
  "body_temp": 36.5,
  "ambient_temp": 30
}

Example response:

{
  "prediction": {
    "class": 0,
    "label": "safe"
  }
}
📱 Flutter Application

Navigate to the Flutter project:

cd flutter_app

Install dependencies:

flutter pub get

Run the application:

flutter run

For an Android emulator, use:

http://10.0.2.2:5000/predict

For a physical device, use the local IP address of the computer running the backend:

http://YOUR_PC_IP:5000/predict

The phone and computer must be connected to the same network.

📡 ESP32 Setup

Open:

esp/esp_http.ino

Configure the Wi-Fi credentials:

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

Then configure the backend URL:

String serverUrl = "http://YOUR_BACKEND_IP:5000/predict";

Upload the code to the ESP32.

The ESP32 collects sensor readings and sends the required data to the FastAPI backend.

🔄 How It Works
Sensors collect physiological and environmental data.
ESP32 reads and processes the sensor values.
ESP32 sends the data to the FastAPI backend.
FastAPI passes the data to the Machine Learning model.
The Machine Learning model predicts the current heat-stress condition.
The prediction is returned to the application.
Flutter displays the result to the user.
🎯 Project Objective

The main objective of this project is to develop an intelligent monitoring system capable of identifying heat-stress conditions using a combination of IoT sensors and Machine Learning.

The project demonstrates the integration of:

Artificial Intelligence + Machine Learning + IoT + Backend Development + Mobile Development

🚀 Future Improvements
Real-time alerts and notifications
Historical health-data tracking
Improved Machine Learning accuracy
Cloud deployment
Additional environmental sensors
Personalized heat-stress recommendations
Real-time monitoring dashboard
