import pandas as pd
import matplotlib.pyplot as plt
import math

data = pd.read_csv("data.csv")

S_true = 0.25 * math.pi + 1.25 * math.asin(0.8) - 1.0

# S_est_wide(N)
plt.figure(figsize=(8,5))
plt.plot(data["N"], data["S_est_wide"], color="blue", label="S_est_wide")
plt.axhline(S_true, color='red', linestyle='--', label='S_true')
plt.xlabel("N (число точек)")
plt.ylabel("Оценка площади S̃ (wide)")
plt.title("Приближённая оценка площади (широкая область)")
plt.legend()
plt.grid(True)
plt.savefig("plot_area_wide.png", dpi=200)
plt.close()

# S_est_narrow(N)
plt.figure(figsize=(8,5))
plt.plot(data["N"], data["S_est_narrow"], color="green", label="S_est_narrow")
plt.axhline(S_true, color='red', linestyle='--', label='S_true')
plt.xlabel("N (число точек)")
plt.ylabel("Оценка площади S̃ (narrow)")
plt.title("Приближённая оценка площади (узкая область)")
plt.legend()
plt.grid(True)
plt.savefig("plot_area_narrow.png", dpi=200)
plt.close()

# rel_err_wide(N)
plt.figure(figsize=(8,5))
plt.plot(data["N"], data["rel_err_wide"], color="orange", label="rel_err_wide")
plt.xlabel("N (число точек)")
plt.ylabel("Относительная ошибка |S̃ - S_true| / S_true")
plt.title("Относительная ошибка (широкая область)")
plt.legend()
plt.grid(True)
plt.savefig("plot_error_wide.png", dpi=200)
plt.close()

# rel_err_narrow(N)
plt.figure(figsize=(8,5))
plt.plot(data["N"], data["rel_err_narrow"], color="purple", label="rel_err_narrow")
plt.xlabel("N (число точек)")
plt.ylabel("Относительная ошибка |S̃ - S_true| / S_true")
plt.title("Относительная ошибка (узкая область)")
plt.legend()
plt.grid(True)
plt.savefig("plot_error_narrow.png", dpi=200)
plt.close()
