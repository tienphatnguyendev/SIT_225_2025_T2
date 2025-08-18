# simple_dht22_logger.py
import serial
import time
from datetime import datetime

port_name = "/dev/cu.usbmodem11101"
baud_rate = 9600
filename = "dht22_data.csv"


arduino = serial.Serial(port_name, baud_rate, timeout=2)
time.sleep(2)  # allow connection to settle

print("Logging started. Press Ctrl+C to stop.")

with open(filename, "a") as f:
    try:
        while True:
            line = arduino.readline().decode().strip()
            if not line:
                continue

            if line == "Error":
                print("Sensor read error, skipping")
                continue
            parts = line.split(",")
            if len(parts) != 2:
                print("Bad data:", line)
                continue

            ts = datetime.now().strftime("%Y%m%d%H%M%S")

            record = ts + "," + parts[0] + "," + parts[1] + "\n"
            f.write(record)
            print("Saved:", record.strip())
    except KeyboardInterrupt:
        print("\nLogging stopped by user.")
    finally:
        arduino.close()
