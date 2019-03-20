"""
Author: Avneesh Mishra
Purpose: To interface with a microcontroller connected to a serial and returning some data when
        'read' is sent to it. Upload the code 'Analog_val_lock.ino' and send 'read 0' to get the
        value of ADC 0
"""

import serial
import re
# Establish Serial connection
port_addr = "/dev/ttyACM0"
baud_rate = 115200
ser_connection = serial.Serial(port_addr, baud_rate, timeout=2)
while True:
    try:
        key = input("Enter 'read': ")
        ser_connection.write(key.encode('utf-8'))   # Convert to bytearray and send
        txt = str(ser_connection.readline())[2:-5]
        print("Data received:", txt)
        num = int(re.split(': ', txt)[1])
        print("Value received is:", num)
    except KeyboardInterrupt:
        print("Keyboard Interrupt has occurred...")
        break
    except serial.SerialTimeoutException:
        print("Serial timed out... No response...")
        continue
    except Exception as e:
        print(e)
        break

print("Closing Serial...")
# Close connection
ser_connection.close()
