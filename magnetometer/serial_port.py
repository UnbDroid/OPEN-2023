import serial
from serial.tools import list_ports
import csv
import time
arduino_port = ""
ports = list_ports.comports()
nomeArquivo = "leituras.csv"
for port in ports:
    print(port[0])
    arduino_port = port[0]
f = open(nomeArquivo, "w", newline='')
f.truncate()
baund = 9600
serialCon = serial.Serial(arduino_port,baund)
serialCon.setDTR(False)
time.sleep(1)
serialCon.flushInput()
serialCon.setDTR(True)
max = 1000
maxX =-999999999
maxY=-99999999999
lowX=10000000000
lowY=10000000000
for k in range(max):
    try:
        # Read the line
        s_bytes = serialCon.readline()
        decoded_bytes = s_bytes.decode("utf-8").strip('\r\n')
        print("valores inicio : ",decoded_bytes)
        # Parse the line
        if k == 0:
            values = decoded_bytes.split(",")
        else:
            #values = 
            values =[float(x) for x in decoded_bytes.split(" ")]
            
            x = float(values[0])
            y = float(values[1])
            if x>maxX:
                maxX=x
            elif x<lowX:
                lowX =x
            if y>maxY:
                maxY =y
            elif y<lowY:
                lowY =y
        
        writer = csv.writer(f,delimiter=",")
        writer.writerow(values)
    except:
        print("erro na hora da gravação")

f.close()
print("Bias x: ", (maxX+ lowX)/2)
print("Bias y: ", (maxY+lowY)/2)
print("Fator de escala x: ", 1/((maxX+ lowX)/2))
print("Fator de escala y: ", 1/((maxY+ lowY)/2))



