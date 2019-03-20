"""
Author: Avneesh Mishra
Purpose: To interface with a microcontroller connected to a serial and returning some data when
        'read' is sent to it.

Command interface
```
Enter request: READ
Data received: READ received, send number
Enter request: 4
Data received: 100, send ADC0_READ
Enter request: ADC0_READ
Data received: 0
```
"""

import serial
import re
# Establish Serial connection
port_addr = "/dev/ttyACM0"
baud_rate = 115200
ser_connection = serial.Serial(port_addr, baud_rate, timeout=2)


# Filter the serial strings
def serialStrFilter(srtxt):
    """
    Remove the beginning b' and ending '
    Also remove the \r in the beginning and the \n in the end
    :param srtxt: Main text string
    :return: filtered string - text
    """
    txt = srtxt
    if txt.startswith("b'"):
        txt = txt[2:]
    if txt.endswith("'"):
        txt = txt[:-1]
    if txt.startswith('\\r'):
        txt = txt[2:]
    if txt.endswith("\\n"):
        txt = txt[:-2]
    return txt


while True:
    try:
        key = input("Enter request: ")
        key = "{k}\n".format(k=key)
        ser_connection.write(key.encode('utf-8'))   # Convert to bytearray and send
        txt = str(ser_connection.readline())
        txt = serialStrFilter(txt)
        print("Data received:", txt)
        # num = int(re.split(': ', txt)[1])
        # print("Value received is:", num)
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
