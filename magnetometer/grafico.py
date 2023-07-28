import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from math import pi
u = 0
v = 0
a = 2
b = 1.5
t = np.linspace(0,2*pi, 100)
plt.plot( u+a*np.cos(t) , v+b*np.sin(t) )
plt.grid(color='lightgray',linestyle='--')
plt.show()