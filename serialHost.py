from graph_data import get_graph_data
import psutil
import serial
import time

port = "COM3" if(psutil.WINDOWS) else "/dev/ttyACM0"
baud_rate = 19200
init_wait = 4
send_deltatime = 0.2

ser = serial.Serial(port, baud_rate)

if(ser.is_open):
    ser.close()
ser.open()
time.sleep(init_wait)
try:
    while True:
        for data in get_graph_data():
            ser.write(data)
            time.sleep(send_deltatime)
            if(ser.in_waiting != 0):
                receivedData = ser.readline().decode().strip()
                print(receivedData)

except KeyboardInterrupt:
    ser.close()
