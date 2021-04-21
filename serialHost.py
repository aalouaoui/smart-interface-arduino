import psutil
import serial
import time


def get_size(bytes):
    factor = 1024
    for unit in ["", "K", "M", "G", "T", "P"]:
        if bytes < factor:
            return f"{bytes:.1f}{unit}"
        bytes /= factor


def get_factor(bytes):
    factor = 0
    while bytes > 99:
        bytes /= 1024
        factor += 1

    return factor


units = ["", "K", "M", "G", "T", "P"]

# CPU
enumerate(psutil.cpu_percent(percpu=True, interval=1))
cpu_usage = psutil.cpu_percent()

# RAM
svmem = psutil.virtual_memory()
ram_percent = svmem.percent
ram_size = get_size(svmem.total)
ram_used = get_size(svmem.used)

cpu_msg = f"cpu;{cpu_usage:.0f};{cpu_usage}%"
ram_msg = f"ram;{ram_percent:.0f};{ram_used}/{ram_size}"


print(cpu_msg)
print(ram_msg)

# ser = serial.Serial("COM3", 9600)
# # ser.write(b'100')

# if(not ser.is_open):
#     ser.open()
# time.sleep(4)
# ser.write(b'50')
# ser.close()
