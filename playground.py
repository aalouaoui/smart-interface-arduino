import psutil
import json


def get_size(bytes):
    factor = 1024
    for unit in ["", "K", "M", "G", "T", "P"]:
        if bytes < factor:
            return f"{bytes:.1f}{unit}"
        bytes /= factor


def format_output(**obj):
    return f"{json.dumps(obj)}\n".encode()


def get_cpu_usage():
    enumerate(psutil.cpu_percent(percpu=True, interval=1))
    cpu_usage = psutil.cpu_percent()
    return format_output(type="cpu_usage", value=round(cpu_usage), label=f"{cpu_usage}%")


def get_cpu_clock():
    clock_current, clock_min, clock_max = psutil.cpu_freq()
    return format_output(type="cpu_frq", value=round(100*(clock_current/clock_max)), lable=f"{clock_current:.0f}MHz")


def get_cpu_temp():
    temp = psutil.sensors_temperatures()["coretemp"][0].current
    temp_max = psutil.sensors_temperatures()["coretemp"][0].high
    return format_output(type="cpu_tmp", value=round(100*temp/temp_max), label=f"{temp}C")


def get_cpu_fan():
    fan_speed = psutil.sensors_fans()['asus'][0].current
    fan_max = 3200
    return format_output(type="cpu_fan", value=round(100*fan_speed/fan_max), label=f"{fan_speed}RPM")


def get_ram():
    svmem = psutil.virtual_memory()
    ram_size = get_size(svmem.total)
    ram_used = get_size(svmem.used)
    ram_msg = f"{ram_used}/{ram_size}"
    return format_output(type="ram_usage", value=round(svmem.percent), label=ram_msg)


def get_disk_usage():
    total, used, free, percent = psutil.disk_usage("/")
    total = get_size(total)
    used = get_size(used)
    return format_output(type="disk_usage", value=round(percent), label=f"{used}/{total}")


print(get_cpu_usage())
print(get_cpu_clock())
print(get_cpu_temp())
print(get_cpu_fan())
print(get_ram())
print(get_disk_usage())
# print(f"Cores: {psutil.cpu_count(logical=False)}")
# print(f"Threads: {psutil.cpu_count()}")
