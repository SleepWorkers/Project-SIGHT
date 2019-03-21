"""
Author: Bharath Chunduru
Summary: To establish a communication channel between CC2640R2F and Python script running on laptop and transfer data serially between the
         two and to parse the data simultaneouly. Also, to plot the data received on a plot.    
"""



import serial
import time
import csv
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

ser = serial.Serial('COM7',112500)
ser.flushInput()

plot_window = 20
y_var = np.array(np.zeros([plot_window]))

plt.ion()
fig, ax = plt.subplots()
line, = ax.plot(y_var)

while True:
    try:
        ser_bytes = ser.readline()
        try:
            readings = (ser_bytes[1:len(ser_bytes)-1].decode("utf-8")) #Parsing serial data coming from CC2640R2F MCU
            print(readings)
        except:
            continue
        with open("test_data.csv","a") as f:
            writer = csv.writer(f,delimiter=",")
            writer.writerow([time.time(),readings])
        y_var = np.append(y_var,readings)
        y_var = y_var[1:plot_window+1]
        line.set_ydata(y_var)
        ax.relim()
        ax.autoscale_view()
        fig.canvas.draw()
        fig.canvas.flush_events()
    except:
        print("Keyboard Interrupt")
        break