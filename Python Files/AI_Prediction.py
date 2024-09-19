import firebase_admin
from firebase_admin import credentials, db
import pandas as pd
import numpy as np
import joblib
import time
from keras.models import load_model
from twilio.rest import Client

if not firebase_admin._apps:
    cred = credentials.Certificate("/content/tunnel-booster-fan-firebase-adminsdk-nexeb-bd65ef1cce.json")
    firebase_admin.initialize_app(cred, {
        'databaseURL': 'https://tunnel-booster-fan-default-rtdb.firebaseio.com/'
    })

model = load_model('/content/neural_network_motor_model_new.h5')
scaler = joblib.load('/content/scaler_new.pkl')

account_sid = 'my_sid'
auth_token = 'my_token'
client = Client(account_sid, auth_token)
to_phone_number = 'my_number'
from_phone_number = 'twilio_phone number'

def send_sms(message):
    client.messages.create(body=message, from_=from_phone_number, to=to_phone_number)

alert_triggered = False
last_alert_time = None

def fetch_latest_data():
    try:
        rpm_ref = db.reference('/sensorData/rpm')
        vibration_ref = db.reference('/sensorData/vibration')
        current_ref = db.reference('/sensorData/current')

        rpm_data = rpm_ref.order_by_key().limit_to_last(1).get()
        vibration_data = vibration_ref.order_by_key().limit_to_last(1).get()
        current_data = current_ref.order_by_key().limit_to_last(1).get()

        if not rpm_data or not vibration_data or not current_data:
            print("No data found in one or more nodes")
            return None, None, None

        latest_rpm = list(rpm_data.values())[0]
        latest_vibration = list(vibration_data.values())[0]
        latest_current = list(current_data.values())[0]

        return latest_rpm, latest_vibration, latest_current

    except Exception as e:
        print(f"Error fetching latest data: {e}")
        return None, None, None

def process_data(rpm_value, vibration_value, current_value):
    global alert_triggered, last_alert_time
    try:
        print(f"RPM: {rpm_value}, Vibration: {vibration_value}, Current: {current_value}")
        data_df = pd.DataFrame([[rpm_value, vibration_value, current_value]], columns=['RPM', 'Vibration', 'Current'])
        data_scaled = scaler.transform(data_df)
        prediction = model.predict(data_scaled)
        predicted_class = np.argmax(prediction, axis=-1)

        if predicted_class == 1:
            if not alert_triggered:
                last_alert_time = time.time()
                alert_triggered = True
            elif time.time() - last_alert_time >= 190:
                send_sms(f"Alert: The motor needs maintenance!The Last sensor Readings are RPM: {rpm_value}, Vibration: {vibration_value}, Current: {current_value}")
                last_alert_time = time.time()
        else:
            alert_triggered = False
    except Exception as e:
        print(f"Error processing data: {e}")

while True:
    rpm_value, vibration_value, current_value = fetch_latest_data()
    if rpm_value is not None and vibration_value is not None and current_value is not None:
        process_data(rpm_value, vibration_value, current_value)

    time.sleep(30)