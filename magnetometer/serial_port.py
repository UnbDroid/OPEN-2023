import serial
from serial.tools import list_ports
import csv
import time
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from matplotlib.patches import Ellipse
import statistics

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
        #
        s_bytes = serialCon.readline()
        decoded_bytes = s_bytes.decode("utf-8").strip('\r\n')
        # Parse the line    
        print(decoded_bytes)
        if k == 0:
            values = decoded_bytes.split(" ")
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
        print("erro na hora da gravação", values)

f.close()
# print("Bias x SERIAL: ", (maxX+ lowX)/2)
# print("Bias y: ", (maxY+lowY)/2)
# print("Fator de escala x: ", (2/(maxX- lowX)))
# print("Fator de escala y: ", (2/(maxY- lowY)))

# Read the csv file
data = pd.read_csv("leituras.csv")
# Extract the X and Y columns
x = data['X']
y = data['Y']
# Plot the original data points
plt.scatter(x, y)

# Set the axis labels and title
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Scatter Plot of X vs Y')

# Calculate the scale and bias factors for the X column
x_min = data['X'].min()
x_max = data['X'].max()
x_scale = 2/(x_max - x_min)
x_bias = (x_max + x_min) / 2

xBias = sum(data['X'])/len(data['X'])
xScale = statistics.stdev(data['X'])

yBias = sum(data['Y'])/len(data['Y'])
yScale = statistics.stdev(data['Y'])
# Calculate the scale and bias factors for the X column
y_min = data['Y'].min()
y_max = data['Y'].max()
y_scale = 2/(y_max - y_min)
y_bias = (y_max + y_min) / 2

# Apply the scale and bias factors to the X and Y columns
x = (data['X'] - xBias)/xScale
y = (data['Y'] - yBias)/yScale

# Create a new figure and plot the corrected data points
plt.figure()
plt.scatter(x, y)

# Set the axis labels and title
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Corrected Scatter Plot of X vs Y')

print(f'BiasX:{xBias}')
print(f'BiasY:{yBias}')
print(f'ScaleX:{xScale}')
print(f'ScaleY:{yScale}')

# Show the plot
plt.show()

