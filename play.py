import atexit
import time


def goodbye():
    print("Good Bye")


atexit.register(goodbye)

try:
    time.sleep(10)
except KeyboardInterrupt:
    print("catched you")
