import psutil
import serial
import time


def get_size(bytes):
    factor = 1024
    for unit in ["", "K", "M", "G", "T", "P"]:
        if bytes < factor:
            return f"{bytes:.1f}{unit}"
        bytes /= factor


def get_cpu_msg():
    enumerate(psutil.cpu_percent(percpu=True, interval=1))
    cpu_usage = psutil.cpu_percent()
    cpu_msg = f"cpu;{cpu_usage:.0f};{cpu_usage}%\n"
    return cpu_msg.encode()


def get_ram_msg():
    svmem = psutil.virtual_memory()
    ram_percent = svmem.percent
    ram_size = get_size(svmem.total)
    ram_used = get_size(svmem.used)
    ram_msg = f"ram;{ram_percent:.0f};{ram_used}/{ram_size}\n"
    return ram_msg.encode()


port = "COM3" if(psutil.WINDOWS) else "/dev/ttyACM0"

ser = serial.Serial(port, 11520)
# ser = serial.Serial("COM3", 11520)
# ser = serial.Serial("/dev/ttyACM0", 11520)
if(ser.is_open):
    ser.close()
ser.open()
time.sleep(4)
while True:
    # ser.write(cpu_msg.encode())
    ser.write(get_cpu_msg())
    time.sleep(0.25)
    # ser.write(ram_msg.encode())
    ser.write(get_ram_msg())
    time.sleep(0.25)
