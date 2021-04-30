import psutil
import json
import shutil


def get_size(bytes):
    factor = 1024
    for unit in ["", "K", "M", "G", "T", "P"]:
        if bytes < factor:
            return f"{bytes:.1f}{unit}"
        bytes /= factor


def format_output(name, val, max_val, label):
    obj = dict(type="graph",
               name=name, val=round(100*val/max_val),
               label=label
               )
    return f"{json.dumps(obj)}\n".encode()


def get_cpu_usage():
    enumerate(psutil.cpu_percent(percpu=True, interval=1))
    cpu_usage = psutil.cpu_percent()
    return format_output("cpu_usage", cpu_usage, 100, f"{cpu_usage}%")


def get_cpu_clock():
    clock_current, clock_min, clock_max = psutil.cpu_freq()
    return format_output("cpu_frq", clock_current, clock_max, f"{clock_current:.0f}MHz")


def get_cpu_temp():
    temp = psutil.sensors_temperatures()["coretemp"][0].current
    temp_max = psutil.sensors_temperatures()["coretemp"][0].high
    return format_output("cpu_tmp", temp, temp_max, f"{temp}C")


def get_cpu_fan():
    fan_speed = psutil.sensors_fans()['asus'][0].current
    fan_max = 3200
    return format_output("cpu_fan", fan_speed, fan_max, f"{fan_speed}RPM")


def get_ram():
    svmem = psutil.virtual_memory()
    ram_size = get_size(svmem.total)
    ram_used = get_size(svmem.used)
    ram_msg = f"{ram_used}/{ram_size}"
    return format_output("ram_usage", svmem.percent, 100, ram_msg)


def get_disk_usage():
    total, used, free = shutil.disk_usage("/")
    return format_output("disk_usage", used, total, f"{get_size(used)}/{get_size(total)}")


def get_graph_data():
    return [get_cpu_usage(), get_cpu_clock(), get_cpu_temp(), get_cpu_fan(), get_ram(), get_disk_usage()]


# Sample Output
# b'{"type": "graph", "name": "cpu_usage", "val": 3, "label": "3.0%"}\n'
# b'{"type": "graph", "name": "cpu_frq", "val": 30, "label": "836MHz"}\n'
# b'{"type": "graph", "name": "cpu_tmp", "val": 33, "label": "33.0C"}\n'
# b'{"type": "graph", "name": "cpu_fan", "val": 66, "label": "2100RPM"}\n'
# b'{"type": "graph", "name": "ram_usage", "val": 40, "label": "3.7G/11.1G"}\n'
# b'{"type": "graph", "name": "disk_usage", "val": 14, "label": "8.7G/63.5G"}\n'
