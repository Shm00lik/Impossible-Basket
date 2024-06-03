import serial
import time


class ArduinoIO:
    def __init__(self, port: str, baudrate: int = 9600, timeout: int = 2):
        try:
            self.ser = serial.Serial(port, baudrate)
        except serial.SerialException:
            print(f"Could not connect to {port}.")

        time.sleep(timeout)

    def read(self):
        return self.ser.readline().decode().strip()

    def write(self, data: str):
        self.ser.write(data.encode())

    def close(self):
        self.ser.close()
