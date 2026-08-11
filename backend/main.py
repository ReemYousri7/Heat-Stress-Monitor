
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from fastapi.middleware.cors import CORSMiddleware
import pickle
import numpy as np

app = FastAPI(title="Heat Stress Prediction API")

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"],
)

MODEL_PATH = "HeatStress_Model_FIXED.pkl"

with open(MODEL_PATH, "rb") as f:
    model = pickle.load(f)

class PredictRequest(BaseModel):
    heart_rate: float
    spo2: float
    body_temp: float
    ambient_temp: float

@app.post("/predict")
def predict(req: PredictRequest):
    X = np.array([[req.heart_rate, req.spo2, req.body_temp, req.ambient_temp]])
    try:
        pred = model.predict(X)
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Model prediction error: {e}")
    label_map = {0: "safe", 1: "heat_load", 2: "heat_stress"}
    result = {"class": int(pred[0]), "label": label_map.get(int(pred[0]), "unknown")}
    return {"prediction": result}
