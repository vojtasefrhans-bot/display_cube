import psutil
import serial
import time
import keyboard

# Nahraď COM3 svým portem (Device Manager > Ports)
port = 'COM9'
ser = serial.Serial(port, 115200, timeout=1)
time.sleep(2)  # Čekej na inicializaci
while not keyboard.is_pressed('c'): 
    cpu = psutil.cpu_percent(interval=0.25)
    ser.write(f"{cpu:.1f}\n".encode())
    time.sleep(0.05)
ser.close()

print(f"Disk: {psutil.disk_usage('/').percent}%")