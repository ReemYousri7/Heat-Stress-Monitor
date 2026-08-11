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
```

## 🔌 Hardware Components

- **ESP32** — Main IoT controller
- **MAX30102** — Heart Rate & SpO2
- **DS18B20** — Temperature sensor
- **DHT11** — Ambient temperature & humidity

## 🛠️ Technologies

- Python
- Scikit-learn
- FastAPI
- Uvicorn
- Pydantic
- NumPy
- ESP32
- MAX30102
- DS18B20
- DHT11
- Wi-Fi / HTTP
- Flutter
- Dart

## 📁 Project Structure

```text
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
└── README.md
```

## ⚙️ Backend Setup

### 1. Navigate to the backend folder

```bash
cd backend
```

### 2. Install dependencies

```bash
pip install -r requirements.txt
```

### 3. Run the FastAPI server

```bash
uvicorn main:app --host 0.0.0.0 --port 5000
```

The API will be available at:

`http://localhost:5000`

Interactive API documentation:

`http://localhost:5000/docs`

## 🔗 API Endpoint

### POST `/predict`

The backend receives sensor data and returns the predicted heat-stress condition.

#### Example Request

```json
{
  "heart_rate": 75,
  "spo2": 98,
  "body_temp": 36.5,
  "ambient_temp": 30
}
```

#### Example Response

```json
{
  "prediction": {
    "class": 0,
    "label": "safe"
  }
}
```

### Prediction Classes

| Class | Condition |
|------:|-----------|
| 0 | Safe |
| 1 | Heat Load |
| 2 | Heat Stress |

## 📡 ESP32 Setup

Open:

`esp/esp_http.ino`

Configure your Wi-Fi credentials:

```cpp
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
```

Then configure the backend URL:

```cpp
String serverUrl = "http://YOUR_BACKEND_IP:5000/predict";
```

Upload the code to the ESP32.

Make sure the ESP32 and the computer running the backend are connected to the same network.

## 📱 Flutter Application

Navigate to the Flutter project:

```bash
cd flutter_app
```

Install dependencies:

```bash
flutter pub get
```

Run the application:

```bash
flutter run
```

### Android Emulator

Use:

`http://10.0.2.2:5000/predict`

### Physical Device

Use the local IP address of the computer running the backend:

`http://YOUR_PC_IP:5000/predict`

The phone and computer must be connected to the same Wi-Fi network.

## 🔄 How It Works

1. Sensors collect physiological and environmental data.
2. ESP32 reads and processes the sensor values.
3. ESP32 sends the required data to the FastAPI backend.
4. FastAPI validates the incoming data.
5. The Machine Learning model predicts the current heat-stress condition.
6. The prediction is returned by the API.
7. The Flutter application can display the result to the user.

## 🎯 Project Objective

The main objective of Heat Stress Monitor is to demonstrate the integration of:

**Artificial Intelligence + Machine Learning + IoT + Backend Development + Mobile Development**

The complete workflow is:

**Sensor Data → ESP32 → FastAPI → Machine Learning → Heat Stress Prediction → Flutter**

## 🚀 Future Improvements

- Real-time alerts and notifications
- Historical sensor-data tracking
- Cloud deployment
- Real-time monitoring dashboard
- Improved Machine Learning models
- Additional environmental sensors
- Personalized heat-stress recommendations
- Data visualization and analytics

