import serial

# Set up the serial port
ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)

# Wait for the microcontroller to send data
while True:
    data = ser.readline().decode().strip()
    print(f"Received data: {data}")
    # if data:
    #     print(f"Received data: {data}")
