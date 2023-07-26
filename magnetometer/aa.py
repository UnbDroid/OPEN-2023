import pandas as pd
import matplotlib.pyplot as plt
import math

# Carregar os dados do arquivo CSV
data = pd.read_csv('leituras.csv')

# Encontrar as coordenadas do centro do círculo
center_x = data['X'].mean()
center_y = data['Y'].mean()

# Calcular as coordenadas relativas ao centro
data['X_Corrigido'] = data['X'] - center_x
data['Y_Corrigido'] = data['Y'] - center_y

# Gráfico do círculo centrado na origem
plt.scatter(data['X_Corrigido'], data['Y_Corrigido'], color='b')
plt.title('Círculo Centrado na Origem')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
plt.axhline(0, color='black', lw=0.5)
plt.axvline(0, color='black', lw=0.5)
plt.gca().set_aspect('equal', adjustable='box')
plt.show()
