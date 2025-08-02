import serial
import time
import random
from datetime import datetime

arduino_port = "/dev/cu.usbmodem11401"

print("Starting Arduino communication...")

arduino = serial.Serial(arduino_port, 9600)
time.sleep(2)

print("Connected to Arduino!")


try:
    while True:

        blink_count = random.randint(1, 10)
        current_time = datetime.now()

        print(f"[{current_time}] Sending: {blink_count} blinks")
        arduino.write(str(blink_count).encode())
        arduino.write("\n".encode())

        print("Waiting for Arduino response...")

        response = arduino.readline().decode().strip()

        if response.isdigit():
            sleep_seconds = int(response)
            current_time = datetime.now()

            print(f"[{current_time}] Received: Sleep for {sleep_seconds} seconds")

            print(f"Sleeping for {sleep_seconds} seconds...")
            time.sleep(sleep_seconds)

            current_time = datetime.now()
            print(f"[{current_time}] Sleep finished!")
            print("-" * 40)

        else:
            print("Got unexpected response:", response)

except KeyboardInterrupt:
    print("\nStopping communication...")
