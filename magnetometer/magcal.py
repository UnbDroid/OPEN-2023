import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from matplotlib.patches import Ellipse

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
x_scale = 2 / (x_max - x_min)
x_bias = (x_max + x_min) / 2

# Calculate the scale and bias factors for the X column
y_min = data['Y'].min()
y_max = data['Y'].max()
y_scale = 2 / (y_max - y_min)
y_bias = (y_max + y_min) / 2

# Apply the scale and bias factors to the X and Y columns
x = x_scale * (data['X'] - x_bias)
y = y_scale * (data['Y'] - y_bias)

# Create a new figure and plot the corrected data points
plt.figure()
plt.scatter(x, y)

# Set the axis labels and title
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Corrected Scatter Plot of X vs Y')

print(f'BiasX:{x_bias}')
print(f'BiasY:{y_bias}')
print(f'ScaleX:{x_scale}')
print(f'ScaleY:{y_scale}')

# Show the plot
plt.show()

