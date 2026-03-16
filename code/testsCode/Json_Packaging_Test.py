import psutil
import json
import serial
import time

port = 'COM6'
ser = serial.Serial(port, 115200, timeout=1)
time.sleep(2)  # Čekej na inicializaci
data = {
    "cpu": 0,
    "ram": 0
}
json_string = json.dumps(data, indent=4, ensure_ascii=False)

while True:
    data = {
    "cpu": psutil.cpu_percent(interval=0.25),
    "ram": psutil.virtual_memory().percent
    }
    json_string = json.dumps(data)
    ser.write(json_string.encode('utf-8') + b'\n')
    ser.flush()
    time.sleep(0.25)
ser.clodse()