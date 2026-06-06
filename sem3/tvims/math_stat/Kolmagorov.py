import numpy as np
import matplotlib.pyplot as plt

# 1. Ваша выборка (100 значений)
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

# 2. Подготовка данных
data_sorted = np.sort(data)
n = len(data)

# 3. Параметры гипотезы (Равномерное распределение)
# Используем границы, указанные в вашем задании
a_star = -4.92
b_star = 3.67

# Функция теоретического распределения F0(x) = (x - a) / (b - a)
def f0_uniform(x, a, b):
    val = (x - a) / (b - a)
    return np.clip(val, 0, 1) # Ограничиваем от 0 до 1

# 4. Расчет статистики Колмогорова
# Вычисляем теоретические значения в точках выборки
y_theo = f0_uniform(data_sorted, a_star, b_star)

# Индексы от 1 до n
range_i = np.arange(1, n + 1)

# Отклонение "плюс" (верх ступеньки - теория)
d_plus = (range_i / n) - y_theo

# Отклонение "минус" (теория - низ ступеньки)
d_minus = y_theo - ((range_i - 1) / n)

# Максимальное отклонение D
d_max = np.max(np.maximum(d_plus, d_minus))

# Значение критерия лямбда
lambda_calc = np.sqrt(n) * d_max
lambda_crit = 1.36 # Для alpha = 0.05

# Вывод результатов в консоль
print(f"--- Результаты проверки (Равномерное распределение) ---")
print(f"Параметры: a*={a_star}, b*={b_star}")
print(f"Максимальное расхождение D: {d_max:.4f}")
print(f"Значение критерия лямбда: {lambda_calc:.4f}")
print(f"Критическое значение (alpha=0.05): {lambda_crit}")

if lambda_calc < lambda_crit:
    print("ВЫВОД: Гипотеза ПРИНИМАЕТСЯ (расхождения случайны)")
else:
    print("ВЫВОД: Гипотеза ОТВЕРГАЕТСЯ")

# 5. Поиск координат для рисования линии отклонения
# (Нужно найти, где именно достигается максимум, чтобы нарисовать зеленую линию)
if np.max(d_plus) > np.max(d_minus):
    idx_max = np.argmax(d_plus)
    x_plot = data_sorted[idx_max]
    y_emp_plot = (idx_max + 1) / n  # Верхняя точка ступеньки
    y_theo_plot = y_theo[idx_max]
else:
    idx_max = np.argmax(d_minus)
    x_plot = data_sorted[idx_max]
    y_emp_plot = idx_max / n        # Нижняя точка ступеньки
    y_theo_plot = y_theo[idx_max]

# 6. Построение графика
plt.figure(figsize=(10, 6))

# Эмпирическая функция F*(x)
plt.step(data_sorted, range_i/n, where='post', label='Эмпирическая F*(x)', color='blue')

# Теоретическая функция F0(x) (Прямая линия для равномерного)
x_lin = np.linspace(a_star, b_star, 200)
y_lin = f0_uniform(x_lin, a_star, b_star)
plt.plot(x_lin, y_lin, label='Теоретическая F0(x)', color='red', linewidth=2)

# Линия максимального отклонения
plt.plot([x_plot, x_plot], [y_emp_plot, y_theo_plot], 
         color='green', linewidth=3, linestyle='--', label=f'Макс. откл. Z={d_max:.3f}')
# Точки на концах линии отклонения
plt.scatter([x_plot, x_plot], [y_emp_plot, y_theo_plot], color='green', zorder=5)

plt.xlabel('X')
plt.ylabel('F(x)')
plt.legend()
plt.grid(True, alpha=0.3)
plt.show()