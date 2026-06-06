import matplotlib.pyplot as plt
import numpy as np

data = [
    0.24, -4.59, 2.27, 0.67, -3.33, 2.22, 0.74, -2.80, -4.00, -1.33, 
    -1.51, -4.56, -3.96, 1.02, -2.26, -0.64, -3.26, -3.66, 1.39, -4.92, 
    -2.47, -4.79, 2.97, -2.35, -2.44, 1.35, -3.63, 1.38, 2.10, 2.97, 
    -3.72, 1.76, -3.99, -4.92, 0.46, 1.61, -1.45, -0.11, -4.13, -3.56, 
    -3.74, 1.40, -2.80, -1.77, -3.22, -3.45, 2.47, -0.81, -3.98, 3.58, 
    0.87, 1.47, -0.56, 3.51, 1.58, 0.98, 0.69, -2.73, 1.41, 2.48, 
    0.86, -0.99, -2.48, 2.92, 2.53, 1.67, 3.09, -1.96, -4.68, -2.87, 
    -0.95, -2.02, -4.11, 2.71, -2.82, -4.07, 3.67, 3.35, 1.26, -4.51, 
    1.89, -3.61, 1.72, 0.78, 2.84, -0.56, -1.06, -0.49, -3.99, -0.38, 
    -0.19, -1.64, -2.02, 2.21, -3.84, 3.38, -4.01, 1.49, -1.77, 0.26
]

n = len(data)
x_min = np.min(data)
x_max = np.max(data)

M = int(np.sqrt(n))  # M = 10

h = (x_max - x_min) / M

bins = [x_min + i * h for i in range(M + 1)]


counts, _ = np.histogram(data, bins=bins)

f_star = counts / (n * h)

plt.figure(figsize=(10, 6))

centers = [(bins[i] + bins[i+1])/2 for i in range(M)]

plt.bar(centers, f_star, width=h, edgecolor='black', alpha=0.7, label='Гистограмма f*(x)')

plt.title('Равноинтервальная гистограмма', fontsize=14)
plt.xlabel('X', fontsize=12)
plt.ylabel('Плотность вероятности f*(x)', fontsize=12)

plt.xticks(np.round(bins, 2), rotation=45) 

plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.grid(axis='x', linestyle=':', alpha=0.4)

plt.tight_layout()
plt.show()