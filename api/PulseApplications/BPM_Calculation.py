import serial 
import csv
import time
ser = serial.Serial('COM7',112500)
ser.flushInput()

BPM = 0
IBI = 600 #INter beat Interval
Thresh = 2048 # ADC resolution - 12 bits. So taking 50% of the signal for threshold
Peak = 2048
Through = 2048
amp = 100
Bpm = 0
firstBeat = True
secondBeat = False
Pulse = False
samplecounter = 0
lastBeatTime = 0
rate = [0,0,0,0,0,0,0,0,0,0]

def Calculate_BPM(signal):
    runningTotal = 0
    for i in range(8):
        rate[i] = rate[i-1]
        runningTotal += rate[i]      
    
    rate[9] = IBI                  
    runningTotal += rate[9]             
    runningTotal /= 10           
    Bpm = 60000/runningTotal
    return Bpm
              

while True:

    ser_bytes = ser.readline()
    signal = int(ser_bytes[1:len(ser_bytes)-1].decode("utf-8"))
    print(signal)
    time.sleep(0.02)
    samplecounter+= 2
    N = samplecounter - lastBeatTime

    if signal < Thresh and N > (IBI/5)*3:
        if signal<Thresh:
            Through = signal
    if signal > Thresh and signal>Peak:
        Peak = signal  

    if N>250:
        if (signal > Thresh) and (Pulse == False) and (N > ((IBI/5)*3) ):  
            Pulse = True                                
            IBI = samplecounter - lastBeatTime
            lastBeatTime = samplecounter   

    if secondBeat:
        secondBeat = False
        for i in range(9):
            rate[i] = IBI

    if firstBeat:
        firstBeat = False
        secondBeat = True
        


    if signal<Thresh and Pulse ==True:
        Pulse = False
        amp = Peak - Through
        Thresh = amp/2 + Through
        Peak = Thresh
        Through = Thresh

    if N > 2500:
        Thresh = 2048
        Peak = 2048
        Through = 2048
        firstBeat = True
        secondBeat = False
    BPM = Calculate_BPM(signal)

print(BPM)

        # print("Keyboard Interrupt")
        # break

