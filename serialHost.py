from graph_data import get_graph_data
import psutil
import serial
import time

port = "COM3" if(psutil.WINDOWS) else "/dev/ttyACM0"
baud_rate = 9600
init_wait = 4
send_deltatime = 0.25

ser = serial.Serial(port, baud_rate)

if(ser.is_open):
    ser.close()
ser.open()
time.sleep(init_wait)
while True:
    for data in get_graph_data():
        ser.write(data)
        time.sleep(send_deltatime)
