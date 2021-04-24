import requests


def get_size(bytes):
    factor = 1024
    for unit in ["", "K", "M", "G", "T", "P"]:
        if bytes < factor:
            return f"{bytes:.1f}{unit}"
        bytes /= factor


r = requests.get("http://localhost:61208/api/3/network")
data = r.json()


print(get_size(data[3]["speed"]))  # Max
print(get_size(data[3]["tx"]))
print(get_size(data[3]["rx"]))  # Downlod
