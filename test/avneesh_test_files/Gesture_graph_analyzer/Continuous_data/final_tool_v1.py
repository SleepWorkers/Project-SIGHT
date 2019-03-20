"""
Author: Avneesh Mishra
Purpose: To view the graphical interface of flex sensors over serial
"""
from matplotlib import pyplot as plt
from matplotlib import animation
from Communication_package.Serial_reader_v3 import SerialParser

PORT_ADDR = "/dev/ttyACM0"
BAUD_RATE = 115200
TIMEOUT = 2
FINGERS = [4, 3, 2, 1, 0]  # Finger selection values: Thumb to Little
MAX_NUM = 10

print("Initializing serial handler...")
serial_port = SerialParser(PORT_ADDR, BAUD_RATE, TIMEOUT)

print("Initializing plotter tool...")
fig = plt.figure()
# Individual fingers
tf_axis = fig.add_subplot(2, 3, 1)
num_t = []
if_axis = fig.add_subplot(2, 3, 2)
num_i = []
mf_axis = fig.add_subplot(2, 3, 3)
num_m = []
rf_axis = fig.add_subplot(2, 3, 4)
num_r = []
lf_axis = fig.add_subplot(2, 3, 5)
num_l = []


def update_axis(fnum):
    # Fetch new data
    num_t.append(serial_port.getADCval(FINGERS[0]))
    num_i.append(serial_port.getADCval(FINGERS[1]))
    num_m.append(serial_port.getADCval(FINGERS[2]))
    num_r.append(serial_port.getADCval(FINGERS[3]))
    num_l.append(serial_port.getADCval(FINGERS[4]))
    # Cap the length to MAX_NUM data points
    if len(num_t) > MAX_NUM:
        del num_t[0]
    if len(num_i) > MAX_NUM:
        del num_i[0]
    if len(num_m) > MAX_NUM:
        del num_m[0]
    if len(num_r) > MAX_NUM:
        del num_r[0]
    if len(num_l) > MAX_NUM:
        del num_l[0]
    # Assign them to the graphs
    tf_axis.clear()
    tf_axis.plot(num_t)
    tf_axis.set_title("Thumb")
    tf_axis.set_ylim(0, 4095)
    if_axis.clear()
    if_axis.plot(num_i)
    if_axis.set_title("Index")
    if_axis.set_ylim(0, 4095)
    mf_axis.clear()
    mf_axis.plot(num_m)
    mf_axis.set_title("Middle")
    mf_axis.set_ylim(0, 4095)
    rf_axis.clear()
    rf_axis.plot(num_r)
    rf_axis.set_title("Ring")
    rf_axis.set_ylim(0, 4095)
    lf_axis.clear()
    lf_axis.plot(num_l)
    lf_axis.set_title("Little")
    lf_axis.set_ylim(0, 4095)


try:
    ani = animation.FuncAnimation(fig, update_axis, interval=1)
    plt.show()
except KeyboardInterrupt:
    print("Exit received...")

del serial_port