import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("hll_results.csv")

plt.figure(figsize=(10, 6))
plt.plot(df["step"], df["true"], label="True F0")
plt.plot(df["step"], df["mean_estimate"], label="HyperLogLog estimate")

plt.xlabel("Processed stream size")
plt.ylabel("Number of unique elements")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
