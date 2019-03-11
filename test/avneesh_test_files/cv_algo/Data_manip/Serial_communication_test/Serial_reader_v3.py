"""
Author: Avneesh Mishra
Purpose: Read function from serial monitor
"""

import serial
import time


class SerialParserError(Exception):
    pass


class SerialParser:
    def __init__(self, port_addr: str = "/dev/ttyACM0", baud_rate: int = 115200, timeout: int = 2):
        """
        Constructor function
        :type port_addr: str
        :param port_addr: Port address
        :type baud_rate: int
        :param baud_rate: Baud rate of serial connection
        :type timeout: int
        :param timeout: Serial timeout period
        """
        self.PORT_ADDR = port_addr
        self.BAUD_RATE = baud_rate
        self.TIMEOUT = timeout
        self.ser_connection = serial.Serial(self.PORT_ADDR, self.BAUD_RATE, timeout=self.TIMEOUT)

    @staticmethod
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

    def getADCval(self, num: int):
        """
        Function to get ADC value
        :param num: ADC number
        :return:
        """
        # Send "READ"
        def sendReqGetResp(req_str):
            request = req_str + "\n"
            self.ser_connection.write(request.encode('utf-8'))
            response = self.serialStrFilter(str(self.ser_connection.readline()))
            return response
        response = sendReqGetResp("READ")
        if response != "READ received, send number":
            raise SerialParserError
        response = sendReqGetResp(str(num))
        if "send ADC0_READ" not in response:
            raise SerialParserError
        response = sendReqGetResp("ADC0_READ")
        try:
            result = int(response)
        except:
            raise SerialParserError
        return result

    def __del__(self):
        """
        Destructor
        :return:
        """
        # Close serial connection
        self.ser_connection.close()

if __name__ == '__main__':
    startTime = time.time()
    ser = SerialParser()
    adc_value = ser.getADCval(2)
    print(adc_value)
    del ser
    endTime = time.time()
    print(endTime - startTime)
